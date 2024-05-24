#include "Game.h"

Game::Game(sf::RenderWindow*& renderWindow, const std::vector<std::string> &image_paths, const std::string& fontPath) :
Scene(renderWindow, image_paths, fontPath),
player(100, Scene::getTexture("Player_SpriteSheet"), 2, Entity::RIGHT, 2.3f, 2.3f,
0, 0, sf::Vector2f{-20.f, -10.f}, sf::Vector2f{40.f, 20.f}, Weapon::weapon_types::TRUMPET,
Scene::getTexture("Trumpet"), 7.5f),
attackCooldown(), paused(false){
    sf::Texture texture;
    sf::IntRect rect{0, 0, (int) Scene::getWindowSize().x,
                     (int) Scene::getWindowSize().y};

    Scene::getTexture("Grass").setRepeated(true);

    background.setTexture(Scene::getTexture("Grass"));
    background.setTextureRect(rect);

    hud = Hud{Scene::getTexture("HealthBottom"), Scene::getTexture("HealthBar"), Scene::getWindowSize(), 100};

    gameProc();
}

sf::Vector2f Game::normalize(const sf::Vector2f &source) {
    float length = sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0)
        return {source.x / length, source.y / length};
    else
        return source;
}

std::ostream &operator<<(std::ostream &os, const Game &game_) {
    os << "Paused?: " << game_.paused <<  "\n";

    return os;
}

void Game::handleEvents(const sf::Event &handeledEvent) {
    switch (handeledEvent.type) {
        case sf::Event::Closed:
            Scene::close();
            break;
        case sf::Event::KeyPressed:
            //37 is the key code for ESC
            if (handeledEvent.key.scancode == 37) {
                paused = true;
                break;
            }
            if (handeledEvent.key.scancode == sf::Keyboard::Scan::Space) {
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
    enemies.emplace_back(Scene::getTexture("Dummy"), 2.3f, 2.3f, x, y, 50, 2.5f);
}

void Game::renderSprites() {

    Scene::draw(player.getSprite());
    Scene::draw(player.getWeapon().getSprite());

    for (auto &enemy: enemies) {
        Scene::draw(enemy.getSprite());
    }
}

void Game::renderHud(){
    for (const auto& sprite : hud.getSprites()){
        Scene::draw(sprite);
    }
}

void Game::pause() {
    Button resume(Scene::getTexture("Buton"), Scene::getFont(), "Resume");
    resume.setPosition(sf::Vector2f{250, 100});

    Button quit(Scene::getTexture("Buton"), Scene::getFont(), "Quit");
    quit.setPosition(sf::Vector2f{250, 400});

    while (paused) {
        while (Scene::pollEvent()) {
            switch (Scene::getEvent().type) {
                case sf::Event::Closed:
                    Scene::close();
                    break;

                case sf::Event::KeyPressed:
                    //37 is the key code for ESC
                    if (Scene::getEvent().key.scancode == 37) {
                        paused = false;
                        return;
                    }
                    break;

                case sf::Event::MouseButtonPressed:
                    if (Scene::getEvent().mouseButton.button == sf::Mouse::Left) {

                        if (resume.clicked(Scene::getEvent().mouseButton)) {
                            paused = false;
                            return;
                        } else if (quit.clicked(Scene::getEvent().mouseButton)) {
                            Scene::close();
                            return;
                        }
                    }
                    break;

                default:
                    break;
            }
        }
        Scene::clear();

        Scene::draw(background);
        renderSprites();
        Scene::draw(resume.getSprite());
        Scene::draw(resume.getText());
        Scene::draw(quit.getSprite());
        Scene::draw(quit.getText());

        Scene::display();
    }
}

void Game::gameProc() {

    sf::Clock clock;
    sf::Clock enemySpawnClock;
    sf::Clock damageCooldown;

    while (Scene::isOpen()) {
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

        while (Scene::pollEvent()) {
            handleEvents(Scene::getEvent());
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
            int x = rand() % Scene::getWindowSize().x + 1;
            int y = rand() % Scene::getWindowSize().y + 1;
            while (x == player.getPosition().x &&
                   y == player.getPosition().y) {
                x = rand() % Scene::getWindowSize().x + 1;
                y = rand() % Scene::getWindowSize().y + 1;
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
                    hud.updateHealth(player.getHealth());
                    damageCooldown.restart();
                }

            }
        }

        Scene::clear();
        Scene::draw(background);
        renderSprites();
        renderHud();
        Scene::display();

    }


}

void Game::end() {

    sf::Text gameover;
    gameover.setFont(Scene::getFont());
    gameover.setString("GameOver!");

    Button quit(Scene::getTexture("Buton"), Scene::getFont(), "Quit");
    quit.setPosition(sf::Vector2f{250, 400});

    renderHud();
    Scene::draw(gameover);
    Scene::draw(quit.getSprite());
    Scene::draw(quit.getText());
    Scene::display();



    while (Scene::isOpen()) {
        while (Scene::pollEvent()) {
            switch (Scene::getEvent().type) {
                case sf::Event::Closed:
                    Scene::close();
                    return;

                case sf::Event::MouseButtonPressed:
                    if (Scene::getEvent().mouseButton.button == sf::Mouse::Left) {
                        if (quit.clicked(Scene::getEvent().mouseButton)) {
                            Scene::close();
                            return;
                        }
                    }

                default:
                    break;
            }
        }
    }
}
