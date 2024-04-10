#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <utility>
#include <SFML/Audio.hpp>

const std::string GAME_TITLE = "Poo's Musicaly Fight";

sf::Vector2f normalize(const sf::Vector2f &source) {
    float length = sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0)
        return {source.x / length, source.y / length};
    else
        return source;
}

static bool intersect(sf::Sprite &sprite1, sf::Sprite &sprite2, bool offseted) {
    float offset;
    if(offseted){
         offset = 30.f;
    }
    else{
        offset = -20.f;
    }

    float x1 = sprite1.getPosition().x - offset;
    float y1 = sprite1.getPosition().y - offset;
    float x2 = x1 + ((float) sprite1.getTexture()->getSize().x * sprite1.getScale().x) + offset;
    float y2 = y1 + ((float) sprite1.getTexture()->getSize().y * sprite1.getScale().y) + offset;

    float x3 = sprite2.getPosition().x;
    float y3 = sprite2.getPosition().y;
    float x4 = x3 + ((float) sprite2.getTexture()->getSize().x * sprite2.getScale().x);
    float y4 = y3 + ((float) sprite2.getTexture()->getSize().y * sprite2.getScale().y);

    if (x1 > x4 || x3 > x2) {
        return false;
    }

    if (y2 < y3 || y4 < y1) {
        return false;
    }

    return true;
}

class Entity {
public:
    enum direction {
        LEFT, RIGHT, UP, DOWN
    };

private:
    sf::Image image;
    sf::IntRect textureRect;
    sf::Texture texture;
    sf::Sprite sprite;

    unsigned int frameSize;
    unsigned int frameCount;


    direction facing;
    float speed;

public:
    //Constructor de copiere


    //TODO comentarii mai explicite
    //TODO AFISAT SCORE LA FINAL
    //TODO operator afisare clase

    //Ignor warning pt constructor de copiere pt ca face parte din cerinta
    //NOLINTNEXTLINE
    Entity(const Entity &other) : image(other.image), textureRect(other.textureRect), texture(other.texture),
                                  sprite(other.sprite), frameSize(other.frameSize), frameCount(other.frameCount),
                                  facing(other.facing), speed(other.speed) {}

    // Constructor operator= de copiere
    //Ignor warning pt operator= pt ca face parte din cerinta
    //NOLINTNEXTLINE
    Entity &operator=(const Entity &other) {
        image = other.image;
        textureRect = other.textureRect;
        texture = other.texture;
        sprite = other.sprite;
        frameSize = other.frameSize;
        frameCount = other.frameCount;
        facing = other.facing;
        speed = other.speed;

        return *this;
    }

    // Destructor
    ~Entity() {
        //std::cout << "Destructorul a fost apelat!\n";
    }

    Entity(const sf::Image &image_, const float &scaleX, const float &scaleY,
           const double &posX, const double &posY) : image(image_), textureRect(0, 0, 0, 0),
                                                     frameSize(image_.getSize().x),
                                                     frameCount(0), facing(RIGHT), speed(0) {
        if (!texture.loadFromImage(image)) {
            std::cout << "Trouble loading texture image!\n";
        } else {
            sprite.setTexture(texture);
            sprite.setScale(scaleX, scaleY);
            sprite.setPosition(static_cast<float>(posX), static_cast<float>(posY));
        }
    }

    Entity(const std::string &texture_path, const float &scaleX,
           const float &scaleY, const double &posX, const double &posY) :
            textureRect(0, 0, 0, 0), frameCount(0), facing(RIGHT), speed(0) {

        if (!image.loadFromFile(texture_path)) {
            std::cout << "Trouble loading image!\n";
        }
        frameSize = image.getSize().x;
        if (!texture.loadFromImage(image)) {
            std::cout << "Trouble loading texture!\n";
        } else {
            sprite.setTexture(texture);
            sprite.setScale(scaleX, scaleY);
            sprite.setPosition(static_cast<float>(posX), static_cast<float>(posY));
        }
    }

    Entity(const std::string &texture_path, const float &scaleX,
           const float &scaleY, const float &posX, const float &posY, const float &speed_) :
            textureRect(0, 0, 0, 0), frameCount(0), facing(RIGHT), speed(speed_) {

        if (!image.loadFromFile(texture_path)) {
            std::cout << "Trouble loading image!\n";
        }
        frameSize = image.getSize().x;
        if (!texture.loadFromImage(image)) {
            std::cout << "Trouble loading texture!\n";
        } else {
            sprite.setTexture(texture);
            sprite.setScale(scaleX, scaleY);
            sprite.setPosition(posX, posY);
        }
    }

    Entity(const std::string &texture_path, const int frameCount_, const direction &facing_, const float &scaleX,
           const float &scaleY, const float &posX, const float &posY, const float &speed_) :
            frameCount(frameCount_), facing(facing_), speed(speed_) {
        if (!image.loadFromFile(texture_path)) {
            std::cout << "Trouble loading image!\n";
        }
        textureRect = sf::IntRect(0, 0, image.getSize().x / frameCount, image.getSize().y);
        frameSize = image.getSize().x / frameCount;
        if (!texture.loadFromImage(image, textureRect)) {
            std::cout << "Trouble loading texture image!\n";
        } else {
            sprite.setTexture(texture);
            sprite.setScale(scaleX, scaleY);
            sprite.setPosition(posX, posY);
        }

    }

    // Operator <<
    friend std::ostream &operator<<(std::ostream &os, const Entity &entity) {
        os << "Texture Size: " << entity.texture.getSize().x << "/" << entity.texture.getSize().y << ", Frame Count: "
           << entity.frameCount << ", Facing Direction: " << entity.facing << "\n";

        return os;
    }

    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }


    void move(sf::Vector2f vector) {
        sprite.move(vector);
    }


    sf::Sprite &getSprite() { return sprite; }

    sf::Texture &getTexture() { return texture; }

    float getSpeed() const { return speed; }

    sf::Vector2f getPosition() const { return sprite.getPosition(); };


};

class Weapon {
public:
    enum weapon_types {
        TRUMPET, KEYS, FLUTE
    };
private:
    weapon_types weapon_type;
    Entity weapon;

    int damage;

public:
    Weapon(weapon_types weapon_type_, const std::string &texture_path, const float &scaleX, const float &scaleY,
           const double &posX, const double &posY) :
            weapon_type(weapon_type_), weapon(texture_path, scaleX, scaleY, posX, posY) {
        switch (weapon_type) {
            case TRUMPET:
                damage = 25;
                break;
            case KEYS:
                damage = 40;
                break;
            case FLUTE:
                damage = 50;
                break;
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Weapon &weapon_) {
        os << "Weapon Type: " << weapon_.weapon_type << ", Weapon Damange: " << weapon_.damage << "\n";

        return os;
    }

    Entity getEntity() { return weapon; }


};

class Enemy {
    Entity enemy;
    float speed;

    int health;

public:
    Enemy(const sf::Image &image, const float &scaleX, const float &scaleY,
          const float &posX, const float &posY, const int &health_, const float &speed_) :
            enemy(image, scaleX, scaleY, posX, posY), speed(speed_), health(health_) {}

    Enemy(const std::string &texture_path, const float &scaleX, const float &scaleY,
          const float &posX, const float &posY, const int &health_, const float &speed_) :
            enemy(texture_path, scaleX, scaleY, posX, posY), speed(speed_), health(health_) {}

    Entity &getEntity() { return enemy; }

    float getSpeed() const { return speed; }

    void damage(int damage, std::vector<Enemy> &enemies, int index) {
        health -= damage;
        if (health <= 0) {
            enemies.erase(enemies.begin() + index);
        }
    }
};

class Player {
private:
    int health = 100;
    bool alive = true;

    Entity player;
    Weapon weapon;

    std::vector<sf::Sprite> sprites;


public:

    Player(const int &health_, const std::string &texture_path, const int frameCount, const Entity::direction &facing,
           const float &scaleX, const float &scaleY,
           const float &posX, const float &posY, const Weapon::weapon_types weapon_type_,
           const std::string &weapon_texture_path, const float &speed_) :
            health(health_), player(texture_path, frameCount, facing,
                                    3.f, 3.f, posX, posY, speed_),
            weapon(weapon_type_, weapon_texture_path,
                   2.3f, 2.3f,
                   posX + 0.75 * player.getSprite().getTexture()->getSize().x * scaleX,
                   posY + 0.40 * player.getSprite().getTexture()->getSize().y * scaleY) {
        sprites.push_back(player.getSprite());
        sprites.push_back(weapon.getEntity().getSprite());

    }


    friend std::ostream &operator<<(std::ostream &os, const Player &player_) {
        os << "Health: " << player_.health << "\n";

        return os;
    }

    std::vector<sf::Sprite> getSprites() const { return sprites; }

    sf::Vector2f getPosition() const { return sprites[0].getPosition(); }


    void moveSprites(Entity::direction dir, float delta) {
        float offsetX = 0, offsetY = 0;

        if (dir == Entity::RIGHT) {
            offsetX = player.getSpeed() * delta;

        } else if (dir == Entity::LEFT) {
            offsetX = -player.getSpeed() * delta;
        } else if (dir == Entity::UP) {
            offsetY = -player.getSpeed() * delta;
        } else if (dir == Entity::DOWN) {
            offsetY = player.getSpeed() * delta;
        }

        for (auto &sprite: sprites) {
            sprite.move(offsetX, offsetY);
        }
    }

    void attack(std::vector<Enemy> &targets) {
        for (unsigned int i = 0; i < targets.size(); i++) {
            if (intersect(sprites[0], targets[i].getEntity().getSprite(), true)) {
                targets[i].damage(50, targets, i);
                return;
            }
        }
    }

    void damage(int damage) {
        health -= damage;
        std::cout << "Health: " << health << "\n";
        if (health <= 0) {
            alive = false;
        }
    }

    bool isAlive() const { return alive; }
};

class Scene {
    sf::RenderWindow window;
    sf::Event event;
    std::vector<sf::Image> images;

public:
    Scene(const unsigned int windowWidth, const unsigned int windowHeight, const std::vector<std::string> &image_paths)
            :
            window(sf::VideoMode{windowWidth, windowHeight}, GAME_TITLE, sf::Style::Default),
            event() {
        window.setVerticalSyncEnabled(true);
        for (const auto &path: image_paths) {
            sf::Image image;
            if (!image.loadFromFile(path)) {
                std::cout << "Trouble at loading Image File\n";
                continue;
            }
            images.push_back(image);
        }
    }

    Scene(const Scene &other) : window(sf::VideoMode{other.window.getSize().x,
                                                     other.window.getSize().y},
                                       GAME_TITLE, sf::Style::Default),
                                event(other.event), images(other.images) {}

    sf::Event getEvent() const { return event; }

    bool isOpen() { return window.isOpen(); }

    void clear() { window.clear(); }

    template<typename T>
    void draw(const T &sprite) { window.draw(sprite); }

    void display() { window.display(); }

    void close() { window.close(); }

    bool pollEvent() { return window.pollEvent(event); }

    sf::Event &getEvent() { return event; }

    sf::Vector2u getWindowSize() const { return window.getSize(); }

    std::vector<sf::Image> &getImages() { return images; }

};

class Button {
    sf::Texture texture;
    sf::Sprite button;
    sf::Font font;
    sf::Text text;

public:
    Button(const std::string &image_path, const std::string &font_path, const std::string &text_) {
        sf::Image image;
        image.loadFromFile(image_path);
        texture.loadFromImage(image);

        button.setTexture(texture);

        font.loadFromFile(font_path);
        text.setFont(font);
        text.setString(text_);

        text.setPosition(button.getPosition());
    }

    std::pair<sf::Sprite, sf::Text> getButton() const {
        return std::pair<sf::Sprite, sf::Text>{button, text};
    }

    void setPosition(sf::Vector2f vector) {
        button.setPosition(vector);
        text.setPosition(vector);
    }

    bool clicked(sf::Event::MouseButtonEvent mouse) {
        sf::IntRect checkRect{static_cast<int>(button.getPosition().x),
                              static_cast<int>(button.getPosition().y),
                              static_cast<int>(button.getTexture()->getSize().x),
                              static_cast<int>(button.getTexture()->getSize().y)};

        return checkRect.contains(mouse.x, mouse.y);
    }
};

class Game {
    Scene scene;
    Player player;
    std::vector<Enemy> enemies;
    sf::Clock attackCooldown;

    bool paused;


    sf::Sprite background;

public:
    Game(const Scene &scene_, Player player_) : scene(scene_), player(std::move(player_)), attackCooldown(), paused(false){
        sf::Texture texture;
        sf::IntRect rect{0, 0, (int) scene.getWindowSize().x, (int) scene.getWindowSize().y};
        texture.setRepeated(true);

        if (!texture.loadFromImage(scene.getImages()[3])) {
            std::cout << "Trouble loading Image!\n";
        }


        background.setTexture(texture);
        background.setTextureRect(rect);
        gameProc();
    }

    void start() { gameProc(); }

private:
    void handleEvents(const sf::Event &event) {
        switch (event.type) {
            case sf::Event::Closed:
                scene.close();
                break;
            case sf::Event::KeyPressed:
                //37 is the key code for ESC
                if (event.key.scancode == 37) {
                    paused = true;
                }
                if (event.key.scancode == sf::Keyboard::Scan::Space) {
                    std::cout << (attackCooldown.getElapsedTime().asSeconds() > 1.f) << "\n";
                    if(attackCooldown.getElapsedTime().asSeconds() > 1.f){
                        std::vector<Entity> entities;
                        for (auto &enemy: enemies) {
                            entities.push_back(enemy.getEntity());
                        }
                        player.attack(enemies);
                        attackCooldown.restart();
                    }

                }
                break;
            default:
                break;
        }
    }

    void addEnemy(const float x, const float y) {
        Enemy enemy = *new Enemy{"Textures/Dummy.png", 2.3f, 2.3f, x, y, 50, 2.5f};
        enemies.push_back(enemy);
    }

    void renderSprites() {

        for (auto &sprite: player.getSprites()) {
            scene.draw(sprite);
        }

        for (auto &enemy: enemies) {
            scene.draw(enemy.getEntity().getSprite());
        }
    }

    void pause() {
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

    void gameProc() {

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

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
                player.getSprites()[0].getPosition().y > 0) {
                player.moveSprites(Entity::UP, delta);

            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
                player.getSprites()[0].getPosition().y +
                floor(player.getSprites()[0].getTexture()->getSize().y) * player.getSprites()[0].getScale().y < 600) {
                player.moveSprites(Entity::DOWN, delta);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
                player.getSprites()[0].getPosition().x > 0) {
                player.moveSprites(Entity::LEFT, delta);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
                player.getSprites()[0].getPosition().x +
                floor(player.getSprites()[0].getTexture()->getSize().x) * player.getSprites()[0].getScale().x < 800) {
                player.moveSprites(Entity::RIGHT, delta);
            }

            if (enemySpawnClock.getElapsedTime().asSeconds() >= 2 && enemies.size() < 10) {
                int x = rand() % scene.getWindowSize().x + 1;
                int y = rand() % scene.getWindowSize().y + 1;
                while (x == player.getSprites()[0].getPosition().x &&
                       y == player.getSprites()[0].getPosition().y) {
                    x = rand() % scene.getWindowSize().x + 1;
                    y = rand() % scene.getWindowSize().y + 1;
                }
                addEnemy(x, y);
                enemySpawnClock.restart();
            }

            for (auto &enemy: enemies) {
                sf::Vector2f direction = normalize(
                        enemy.getEntity().getPosition() - player.getSprites()[0].getPosition());
                direction.x *= -enemy.getSpeed() * delta;
                direction.y *= -enemy.getSpeed() * delta;

                enemy.getEntity().move(direction);

                if (intersect(player.getSprites()[0], enemy.getEntity().getSprite(), false)) {

                    if (damageCooldown.getElapsedTime().asSeconds() > 2) {
                        std::cout << "damage\n";
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

    void end() {
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
};


int main() {

    Game game{Scene{800, 600, std::vector<std::string>{
            "Textures/Weapons/Trumpet.png",
            "Textures/Dummy.png",
            "Textures/Player.png",
            "Textures/Grass.jpg"
    }}, Player(100, "Textures/Player_SpriteSheet.png", 2, Entity::RIGHT, 2.3f, 2.3f,
               0, 0, Weapon::weapon_types::TRUMPET, "Textures/Weapons/Trumpet.png", 7.5f)};

    game.start();

    return 0;
}

//
