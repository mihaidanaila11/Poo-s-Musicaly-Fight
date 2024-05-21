#include "Game.h"



sf::Vector2f Game::normalize(const sf::Vector2f &source) {
    float length = sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0)
        return {source.x / length, source.y / length};
    else
        return source;
}

void Game::handleEvents(const sf::Event &event) {
    switch (event.type) {
        case sf::Event::Closed:
            scene.close();
            break;
        case sf::Event::KeyPressed:
            //37 is the key code for ESC
            if (event.key.scancode == 37) {
                paused = true;
                break;
            }
            if (event.key.scancode == sf::Keyboard::Scan::Space) {
                if(attackCooldown.getElapsedTime().asSeconds() > 1.f){
                    player.attack(enemies);
                    attackCooldown.restart();
                    break;
                }

            }
            break;
        default:
            break;
    }
}

void Game::addEnemy(const float x, const float y) {
    enemies.emplace_back(scene.getTexture("Dummy"), 2.3f, 2.3f, x, y, 50, 2.5f);
}

void Game::renderSprites() {

    scene.draw(player.getSprite());
    scene.draw(player.getWeapon().getSprite());

    for (auto &enemy: enemies) {
        scene.draw(enemy.getSprite());
    }
}

void Game::pause() {
    Button resume("Textures/Buton.png", "daydream_3/Daydream.ttf", "Resume");
    resume.setPosition(sf::Vector2f{250, 100});

    Button quit("Textures/Buton.png", "daydream_3/Daydream.ttf", "Quit");
    quit.setPosition(sf::Vector2f{250, 400});

    while (paused) {
        while (scene.pollEvent()) {
            switch (scene.getEvent().type) {
                case sf::Event::Closed:
                    scene.close();
                    break;

                case sf::Event::KeyPressed:
                    //37 is the key code for ESC
                    if (scene.getEvent().key.scancode == 37) {
                        paused = false;
                        return;
                    }
                    break;

                case sf::Event::MouseButtonPressed:
                    if (scene.getEvent().mouseButton.button == sf::Mouse::Left) {

                        if (resume.clicked(scene.getEvent().mouseButton)) {
                            paused = false;
                            return;
                        } else if (quit.clicked(scene.getEvent().mouseButton)) {
                            scene.close();
                            return;
                        }
                    }
                    break;

                default:
                    break;
            }
        }
        scene.clear();

        scene.draw(background);
        renderSprites();
        scene.draw(std::get<0>(resume.getButton()));
        scene.draw(std::get<1>(resume.getButton()));

        scene.draw(std::get<0>(quit.getButton()));
        scene.draw(std::get<1>(quit.getButton()));

        scene.display();
    }
}

void Game::gameProc() {

    sf::Clock clock;
    sf::Clock enemySpawnClock;
    sf::Clock damageCooldown;


    while (scene.isOpen()) {
        float delta = clock.restart().asSeconds() * 60;

        if (!player.isAlive()) {
            end();
            return;
        }

        if (paused) {
            pause();
            clock.restart();
            delta = clock.getElapsedTime().asSeconds() * 60;
        }

        while (scene.pollEvent()) {
            handleEvents(scene.getEvent());
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player.moveSprites(Entity::UP, delta);

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player.moveSprites(Entity::DOWN, delta);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            player.moveSprites(Entity::LEFT, delta);

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            player.moveSprites(Entity::RIGHT, delta);

        }

        if (enemySpawnClock.getElapsedTime().asSeconds() >= 2 && enemies.size() < 10) {
            int x = rand() % scene.getWindowSize().x + 1;
            int y = rand() % scene.getWindowSize().y + 1;
            while (x == player.getPosition().x &&
                   y == player.getPosition().y) {
                x = rand() % scene.getWindowSize().x + 1;
                y = rand() % scene.getWindowSize().y + 1;
            }
            addEnemy(x, y);
            enemySpawnClock.restart();
        }

        for (auto &enemy: enemies) {
            sf::Vector2f direction = normalize(
                    enemy.getPosition() - player.getPosition());
            direction.x *= -enemy.getSpeed() * delta;
            direction.y *= -enemy.getSpeed() * delta;

            enemy.move(direction);

            if (player.getHitbox().intersects(enemy.getHitbox())) {

                if (damageCooldown.getElapsedTime().asSeconds() > 2) {
                    player.damage(25);
                    damageCooldown.restart();
                }

            }
        }

        scene.clear();
        scene.draw(background);
        renderSprites();
        scene.display();

    }


}

void Game::end() {
    sf::Font font;
    font.loadFromFile("daydream_3/Daydream.ttf");

    sf::Text gameover;
    gameover.setFont(font);
    gameover.setString("GameOver!");

    Button quit("Textures/Buton.png", "daydream_3/Daydream.ttf", "Quit");
    quit.setPosition(sf::Vector2f{250, 400});

    scene.draw(gameover);
    scene.draw(std::get<0>(quit.getButton()));
    scene.draw(std::get<1>(quit.getButton()));
    scene.display();



    while (scene.isOpen()) {
        while (scene.pollEvent()) {
            switch (scene.getEvent().type) {
                case sf::Event::Closed:
                    scene.close();
                    return;

                case sf::Event::MouseButtonPressed:
                    if (scene.getEvent().mouseButton.button == sf::Mouse::Left) {
                        if (quit.clicked(scene.getEvent().mouseButton)) {
                            scene.close();
                            return;
                        }
                    }

                default:
                    break;
            }
        }
    }
}