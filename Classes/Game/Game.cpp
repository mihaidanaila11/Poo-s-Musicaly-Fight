#include "Game.h"
#include "../Enemy/Enemies/BasicEnemy/BasicEnemy.h"
#include "../Enemy/Enemies/GhostEnemy/GhostEnemy.h"
#include "../Wave/Wave.h"
#include "../Alert/Alert.h"
#include "../../Math/VectorMath.h"

sf::Clock Game::deltaTime;

using std::swap;

Game::Game(sf::RenderWindow*& renderWindow,
           const std::vector<std::string> &image_paths,
           const std::string& fontPath) :
Scene(renderWindow, image_paths, fontPath),


player(100,
       Scene::getTexture("Player_SpriteSheet"),
       2,
       2.3f, 2.3f,
       0, 0,
       sf::Vector2f{-20.f, -10.f},
       sf::Vector2f{60.f, 30.f},
       Weapon::weapon_types::TRUMPET,
       Scene::getTexture("Trumpet"),
       7.5f, 2.f),
wave{30, std::vector<Enemy*>{
        BasicEnemy{Scene::getTexture("Dummy"), 2.3f, 2.3f, 0, 0, 50, 2.f, 25}.clone(),
        GhostEnemy{Scene::getTexture("Ghost"), 2.3f, 2.3f, 0, 0, 50, 0.5f, 25}.clone()
}, Scene::getWindowSize()},
attackCooldown(),
paused(false){
    std::cout << "game const";
    sf::Texture texture;
    sf::IntRect rect{0, 0, (int) Scene::getWindowSize().x,
                     (int) Scene::getWindowSize().y};

    Scene::getTexture("Grass").setRepeated(true);

    background.setTexture(Scene::getTexture("Grass"));
    background.setTextureRect(rect);

    hud = Hud{Scene::getTexture("HealthBottom"), Scene::getTexture("HealthBar"), Scene::getWindowSize(), 100};
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

void Game::handleEvents() {
    std::vector<Enemy*> enemies = wave.getEnemies();


    while(Scene::pollEvent()) {
        sf::Event handledEvent = Scene::getEvent();
        switch (handledEvent.type) {
            case sf::Event::Closed:
                Scene::close();
                break;
            case sf::Event::KeyPressed:
                //37 is the key code for ESC
                if (handledEvent.key.scancode == 37) {
                    paused = true;
                    break;
                }
                if (handledEvent.key.scancode == sf::Keyboard::Scan::Space) {
                    if (attackCooldown.getElapsedTime().asSeconds() > 1.f) {
                        for(unsigned int i=0; i < enemies.size(); i++){
                            if (player.getAttackRange().intersects(enemies[i]->getHitbox())) {
                                player.attack(enemies[i]);
                                if(!enemies[i]->isAlive()){
                                    wave.deleteEnemy(i);
                                }
                                break;
                            }
                        }
                        attackCooldown.restart();

                        break;
                    }

                }
                break;
            default:
                break;
        }
    }
}

void Game::renderSprites() {
    std::vector<Enemy*> enemies = wave.getEnemies();

    Scene::draw(player.getSprite());
    Scene::draw(player.getWeapon().getSprite());
    Scene::draw(player.getAttackRange().getRect());
    Scene::draw(player.getHitbox().getRect());

    for (auto &enemy: enemies) {
        Scene::draw(enemy->getSprite());
        Scene::draw(enemy->getHitbox().getRect());
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


    sf::Clock enemySpawnClock;
    float delta = deltaTime.restart().asSeconds() * 60;
    renderAlert("WAVE " + std::to_string(wave.getWaveNumber()));
    wave.initWave(player.getPosition());
    while (Scene::isOpen()) {
        delta = deltaTime.restart().asSeconds() * 60;
        if (!player.isAlive()) {
            end();
            return;
        }

        if (paused) {
            pause();
            deltaTime.restart();
            delta = deltaTime.getElapsedTime().asSeconds() * 60;
        }

        handleEvents();

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

        if(wave.isCleared()){
            nextWave();
        }

        for (auto& enemy : wave.getEnemies()) {
            sf::Vector2f direction = normalize(
                    enemy->getPosition() - player.getPosition());
            direction.x *= -enemy->getSpeed() * delta;
            direction.y *= -enemy->getSpeed() * delta;


            for(auto& enemy_ : wave.getEnemies()){
                if(enemy_==enemy)
                    continue;
                if(enemy->getSprite().getGlobalBounds().intersects(enemy_->getSprite().getGlobalBounds())){
                    std::cout << "coliziune\n";
                    sf::Vector2f pos1 = enemy->getPosition();
                    sf::Vector2f pos2 = enemy_->getPosition();
                    sf::Vector2f deltaPosition = pos2 - pos1;
                    float distance = VectorMath::vectorDistance(enemy->getPosition(), enemy_->getPosition());
                    direction.x -= deltaPosition.x / distance;
                    direction.y -= deltaPosition.y / distance;
                }
            }


            enemy->move(direction);


            if (player.isDamageable()) {
                if(enemy->getHitbox().intersects(player.getHitbox())){
                    enemy->attack(player);
                    hud.updateHealth(player.getHealth());
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

void Game::wait(float secounds){
    sf::Clock clock_;
    while(clock_.getElapsedTime().asSeconds() < secounds){
        deltaTime.restart();
        alertHandleEvents();
    }
}

void Game::renderAlert(const std::string& message){
    Alert alert{message,
                Scene::getTexture("BigAlert"), Scene::getFont(), Scene::getWindowSize()};

    float delta;
    float velocity = 7.f;

    while(alert.getPosition().y < (float)Scene::getWindowSize().y/2 - alert.getSprite().getGlobalBounds().height/2){
        delta = deltaTime.restart().asSeconds() * 60;
        alertHandleEvents();
        alert.move(sf::Vector2f{0.f, velocity * delta});

        Scene::clear();
        Scene::draw(background);
        renderSprites();
        renderHud();
        Scene::draw(alert);
        Scene::display();
    }

    wait(2);
}

void Game::nextWave() {
    renderAlert("WAVE " + std::to_string(wave.getWaveNumber()));

    wave.next(player.getPosition());
}

void Game::alertHandleEvents(){
        while (Scene::pollEvent()) {
            switch (Scene::getEvent().type) {
                case sf::Event::Closed:
                    Scene::close();
                    return;

                default:
                    break;
            }
        }
}


