#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <utility>
#include <SFML/Audio.hpp>
#include <unordered_map>

const std::string GAME_TITLE = "Poo's Musicaly Fight";

sf::Vector2f normalize(const sf::Vector2f &source) {
    float length = sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0)
        return {source.x / length, source.y / length};
    else
        return source;
}


class Hitbox {
private:
    sf::RectangleShape rect;

public:

    Hitbox() : rect() {}

    Hitbox(const sf::Sprite& sprite, const unsigned int& frameCount, const unsigned int& frameSize, const sf::Vector2f & hitboxOffset) {

        rect.setSize(sf::Vector2f{(((float)sprite.getTexture()->getSize().x * sprite.getScale().x +(2 * hitboxOffset.x)) / (float)frameCount),
                                    (float) sprite.getTexture()->getSize().y * sprite.getScale().y +(2*hitboxOffset.y)});

        rect.setPosition(sf::Vector2f{sprite.getPosition().x + (float)frameSize / 2 * sprite.getScale().x - rect.getSize().x / 2,
                                      sprite.getPosition().y + (float)sprite.getTexture()->getSize().y / 2 * sprite.getScale().y - rect.getSize().y / 2});
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineColor(sf::Color::Red);
        rect.setOutlineThickness(3.f);
    }

    explicit Hitbox(const sf::Sprite& sprite){
        rect.setSize(sf::Vector2f{(float) sprite.getTexture()->getSize().x * sprite.getScale().x,
                                    (float) sprite.getTexture()->getSize().y * sprite.getScale().y});

        rect.setPosition(sprite.getPosition());
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineColor(sf::Color::Red);
        rect.setOutlineThickness(3.f);
    }

    bool intersects(const Hitbox& other){
        float x1 = rect.getPosition().x;
        float y1 = rect.getPosition().y;
        float x2 = x1 + ((float) rect.getSize().x);
        float y2 = y1 + ((float) rect.getSize().y);

        float x3 = other.getRect().getPosition().x;
        float y3 = other.getRect().getPosition().y;
        float x4 = x3 + ((float) other.rect.getSize().x);
        float y4 = y3 + ((float) other.rect.getSize().y);;

        if (x1 > x4 || x3 > x2) {
            return false;

        }

        if (y2 < y3 || y4 < y1) {
            return false;
        }

        return true;
    }

    sf::RectangleShape getRect() const { return rect; }

    void setPosition(float& x, float& y){
        rect.setPosition(x, y);
    }

    void move(sf::Vector2f vector){
        rect.move(vector);
    }
};

class Entity {
public:
    enum direction {
        LEFT, RIGHT, UP, DOWN
    };

private:
    sf::IntRect textureRect;
    sf::Texture& texture;
    sf::Sprite sprite;

    unsigned int frameSize;
    unsigned int frameCount;

    Hitbox hitbox;

    direction facing;
    float speed;

public:
    //Constructor de copiere


    //TODO comentarii mai explicite
    //TODO AFISAT SCORE LA FINAL
    //TODO operator afisare clase

    //Ignor warning pt constructor de copiere pt ca face parte din cerinta
    //NOLINTNEXTLINE
    Entity(const Entity &other) : textureRect(other.textureRect), texture(other.texture),
    frameSize(other.frameSize), frameCount(other.frameCount), hitbox(other.hitbox),
                                  facing(other.facing), speed(other.speed) {
        std::cout << "copiere\n";
            sprite.setTexture(texture);
            sprite.setTextureRect(textureRect);
            sprite.setScale(other.sprite.getScale().x, other.sprite.getScale().y);
            sprite.setPosition(static_cast<float>(other.sprite.getPosition().x),
                               static_cast<float>(other.sprite.getPosition().y));
    }

    // Constructor operator= de copiere
    //Ignor warning pt operator= pt ca face parte din cerinta
    //NOLINTNEXTLINE
    Entity &operator=(const Entity &other) {
        textureRect = other.textureRect;
        texture = other.texture;
        sprite = other.sprite;
        hitbox = other.hitbox;
        frameSize = other.frameSize;
        frameCount = other.frameCount;
        facing = other.facing;
        speed = other.speed;

        return *this;
    }

    // Destructor
    ~Entity() {
        std::cout << "Destructorul a fost apelat!\n";
    }

    Entity(sf::Texture& texture_, const float &scaleX,
           const float &scaleY, const double &posX, const double &posY) :
            textureRect(), texture(texture_), frameCount(1), facing(RIGHT), speed(0) {

        frameSize = texture.getSize().x;
            textureRect.width = (int)texture.getSize().x;
            textureRect.height = (int)texture.getSize().y;

            sprite.setTexture(texture);
            sprite.setTextureRect(textureRect);
            sprite.setScale(scaleX, scaleY);
            sprite.setPosition(static_cast<float>(posX), static_cast<float>(posY));

            hitbox = Hitbox{sprite};

    }

    Entity(sf::Texture& texture_, const int& frameCount_, const direction& facing_, const sf::Vector2f& hitboxOffset, const float& scaleX,
           const float& scaleY, const float& posX, const float& posY, const float& speed_) : texture(texture_),
            frameCount(frameCount_), facing(facing_), speed(speed_) {

        textureRect = sf::IntRect(0, 0, texture.getSize().x / frameCount, texture.getSize().y);
        frameSize = texture.getSize().x / frameCount;
            sprite.setTexture(texture);
            sprite.setTextureRect(textureRect);
            sprite.setScale(scaleX, scaleY);
            sprite.setPosition(posX, posY);

            hitbox = Hitbox{sprite, frameCount, frameSize, hitboxOffset};

    }

    // Operator <<
    friend std::ostream &operator<<(std::ostream &os, const Entity &entity) {
        os << "Texture Size: " << entity.texture.getSize().x << "/" << entity.texture.getSize().y << ", Frame Count: "
           << entity.frameCount << ", Facing Direction: " << entity.facing << "\n";

        return os;
    }

    void setTextureFrame(const int& frame){

        if(frame*(int)frameSize == textureRect.left){
            return;
        }

        textureRect.left = (int)frameSize*frame;
        sprite.setTextureRect(textureRect);

        std::cout << sprite.getTextureRect().left<< "\n";
    }

    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
        hitbox.setPosition(x, y);
    }


    void move(sf::Vector2f vector) {
        sprite.move(vector);
        hitbox.move(vector);
    }


    const sf::Sprite& getSprite() const { return sprite; }
    unsigned int getFrameCount() const {return frameCount; }
    unsigned int getFrameSize() const { return frameSize; }

    sf::Texture &getTexture() { return texture; }
    Hitbox getHitbox() const { return hitbox; }

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
    Entity entity;

    int damage;

public:
    Weapon(weapon_types weapon_type_, sf::Texture &texture, const float &scaleX, const float &scaleY,
           const double &posX, const double &posY) :
            weapon_type(weapon_type_), entity(texture, scaleX, scaleY, posX, posY) {
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

    void move(sf::Vector2f vector){
        entity.move(vector);
    }

     sf::Sprite getSprite() const { return entity.getSprite(); }
     Hitbox getHitbox() const { return entity.getHitbox(); }

};

class Enemy {
    Entity entity;
    float speed;

    int health;

public:
    Enemy(sf::Texture& texture, const float &scaleX, const float &scaleY,
          const float &posX, const float &posY, const int &health_, const float &speed_) :
            entity(texture, scaleX, scaleY, posX, posY), speed(speed_), health(health_) {}

    friend std::ostream &operator<<(std::ostream &os, const Enemy &enemy_) {
        os << "Health: " << enemy_.health << ", Speed: " << enemy_.speed << "\n";

        return os;
    }

    const sf::Sprite& getSprite() const { return entity.getSprite(); }

    sf::Vector2f getPosition() const { return entity.getPosition(); }

    void move(sf::Vector2f vector){
        entity.move(vector);
    }

    float getSpeed() const { return speed; }
    Hitbox getHitbox() const { return entity.getHitbox(); }

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

    Entity entity;
    Weapon weapon;

    Hitbox attackRange;


public:

    Player(const int &health_, sf::Texture& texture, const int frameCount, const Entity::direction &facing,
           const float &scaleX, const float &scaleY,
           const float &posX, const float &posY, const sf::Vector2f& hitboxOffset, const sf::Vector2f& attackRadius, const Weapon::weapon_types weapon_type_,
           sf::Texture &weapon_texture, const float &speed_) :
            health(health_), entity(texture, frameCount, facing, hitboxOffset,
                                    3.f, 3.f, posX, posY, speed_),
            weapon(weapon_type_, weapon_texture,
                   2.3f, 2.3f,
                   posX + 0.50 * entity.getSprite().getTexture()->getSize().x * scaleX,
                   posY + 0.40 * entity.getSprite().getTexture()->getSize().y * scaleY),
                   attackRange(entity.getSprite(), entity.getFrameCount(),
                               entity.getFrameSize(), attackRadius){
    }


    friend std::ostream &operator<<(std::ostream &os, const Player &player_) {
        os << "Health: " << player_.health << ", Alive?: " << player_.alive << "\n";

        return os;
    }

    sf::Vector2f getPosition() const { return entity.getPosition(); }


    void moveSprites(Entity::direction dir, float delta) {
        sf::Vector2f offset{0,0};

        if (dir == Entity::RIGHT) {
            if(entity.getPosition().x +
            floor(entity.getTexture().getSize().x) * entity.getSprite().getScale().x >= 800){
                return;
            }
            entity.setTextureFrame(0);
            offset.x = entity.getSpeed() * delta;

        } else if (dir == Entity::LEFT) {
            if(entity.getPosition().x <= 0){
                return;
            }
            entity.setTextureFrame(1);
            offset.x = -entity.getSpeed() * delta;
        } else if (dir == Entity::UP) {
            if(entity.getPosition().y <= 0){
                return;
            }
            offset.y = -entity.getSpeed() * delta;
        } else if (dir == Entity::DOWN) {
            if(entity.getPosition().y +
               floor(entity.getTexture().getSize().y) * entity.getSprite().getScale().y >= 600){
                return;
            }
            offset.y = entity.getSpeed() * delta;
        }

        entity.move(offset);
        attackRange.move(offset);
        weapon.move(offset);
    }

    void attack(std::vector<Enemy> &targets) {
        for (unsigned int i = 0; i < targets.size(); i++) {
            if (attackRange.intersects(targets[i].getHitbox())) {
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

    const sf::Sprite& getSprite() { return entity.getSprite(); }
    const Weapon& getWeapon() const { return weapon; }

    Hitbox getAttackRange() const { return attackRange; }
    Hitbox getHitbox() const { return entity.getHitbox(); }
};

class Scene {
    sf::RenderWindow window;
    sf::Event event;

    std::unordered_map<std::string, sf::Texture> textures;

public:
    Scene(const unsigned int windowWidth, const unsigned int windowHeight, const std::vector<std::string> &image_paths):
            window(sf::VideoMode{windowWidth, windowHeight}, GAME_TITLE, sf::Style::Default),
            event() {
        window.setVerticalSyncEnabled(true);
        for (const auto &path: image_paths) {

            std::string name;
            for(int i = path.size() - 5; i>=0; i--){
                if(path[i] == '/'){
                    break;
                }
                    name += path[i];
            }
            std::reverse(name.begin(), name.end());

            sf::Image image;
            if (!image.loadFromFile(path)) {
                std::cout << "Trouble at loading Image File\n";
                continue;
            }

            sf::Texture texture;
            if(!texture.loadFromImage(image)){
                std::cout << "Trouble at loading Texture\n";
                continue;
            }

            textures[name] = texture;
        }
    }

    Scene& operator=(const Scene& other){
        event = other.event;
        textures = other.textures;

        return *this;
    }

    ~Scene() = default;



    Scene(const Scene &other) : window(sf::VideoMode{other.window.getSize().x,
                                                     other.window.getSize().y},
                                       GAME_TITLE, sf::Style::Default),
                                event(other.event), textures(other.textures) {}

    friend std::ostream &operator<<(std::ostream &os, const Scene &scene_) {
        os << "Window size: " << scene_.window.getSize().x << "x" << scene_.window.getSize().y<< "\n";

        return os;
    }

    sf::Texture& getTexture(std::string key) { return textures[key]; }

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


};

class Button {
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Font font;
    sf::Text text;

public:
    Button(const std::string &image_path, const std::string &font_path, const std::string &text_) {
        sf::Image image;
        image.loadFromFile(image_path);
        texture.loadFromImage(image);

        sprite.setTexture(texture);

        font.loadFromFile(font_path);
        text.setFont(font);
        text.setString(text_);

        text.setPosition(sprite.getPosition());
    }

    friend std::ostream &operator<<(std::ostream &os, const Button &button_) {
        os << "Position: " << button_.sprite.getPosition().x << "," << button_.sprite.getPosition().y <<
        " Text: " << static_cast<std::string>(button_.text.getString()) << "\n";

        return os;
    }

    std::pair<sf::Sprite, sf::Text> getButton() const {
        return std::pair<sf::Sprite, sf::Text>{sprite, text};
    }

    void setPosition(sf::Vector2f vector) {
        sprite.setPosition(vector);
        text.setPosition(vector);
    }

    bool clicked(sf::Event::MouseButtonEvent mouse) {
        sf::IntRect checkRect{static_cast<int>(sprite.getPosition().x),
                              static_cast<int>(sprite.getPosition().y),
                              static_cast<int>(sprite.getTexture()->getSize().x),
                              static_cast<int>(sprite.getTexture()->getSize().y)};

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
    explicit Game(const Scene &scene_) : scene(scene_),
    player(100, scene.getTexture("Player_SpriteSheet"), 2, Entity::RIGHT, 2.3f, 2.3f,
           0, 0, sf::Vector2f{-20.f, -10.f}, sf::Vector2f{40.f, 20.f}, Weapon::weapon_types::TRUMPET,
           scene.getTexture("Trumpet"), 7.5f),
           attackCooldown(), paused(false){
        sf::Texture texture;
        sf::IntRect rect{0, 0, (int) scene.getWindowSize().x, (int) scene.getWindowSize().y};

        scene.getTexture("Grass").setRepeated(true);

        background.setTexture(scene.getTexture("Grass"));
        background.setTextureRect(rect);
        gameProc();
    }

    friend std::ostream &operator<<(std::ostream &os, const Game &game_) {
        os << "Paused?: " << game_.paused <<  "\n";

        return os;
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

    void addEnemy(const float x, const float y) {
        enemies.emplace_back(scene.getTexture("Dummy"), 2.3f, 2.3f, x, y, 50, 2.5f);
    }

    void renderSprites() {

        scene.draw(player.getSprite());
        scene.draw(player.getWeapon().getSprite());
        scene.draw(player.getAttackRange().getRect());

        for (auto &enemy: enemies) {
            scene.draw(enemy.getSprite());
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
            "Textures/Player_SpriteSheet.png",
            "Textures/Grass.jpg"
    }}};

    game.start();

    return 0;
}

//
//socoban