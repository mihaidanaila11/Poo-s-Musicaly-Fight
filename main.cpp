#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <utility>
//#include <SFML/Audio.hpp>

#define GAME_TITLE      "Poo's Musicaly Fight"

class Entity {
public:
    enum direction{LEFT, RIGHT, UP, DOWN};

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

    //Ignor warning pt constructor de copiere pt ca face parte din cerinta
    //NOLINTNEXTLINE
    Entity(const Entity& other) : image(other.image), textureRect(other.textureRect), texture(other.texture),
                                  sprite(other.sprite), frameSize(other.frameSize), frameCount(other.frameCount), facing(other.facing), speed(other.speed){}

    // Constructor operator= de copiere
    //Ignor warning pt operator= pt ca face parte din cerinta
    //NOLINTNEXTLINE
    Entity& operator= (const Entity& other){
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
        std::cout << "Destructorul a fost apelat!\n";
    }
    Entity(const sf::Image &image_, const float& scaleX, const float& scaleY) : image(image_), textureRect(0,0,0,0), frameSize(image_.getSize().x),
                                                                                frameCount(0), facing(RIGHT), speed(0){
        if (!texture.loadFromImage(image)) {
            std::cout << "Trouble loading texture image!\n";
        } else {
            sprite.setTexture(texture);
            sprite.setScale(scaleX, scaleY);
        }
    }

    Entity(const std::string& texture_path, const float& scaleX,
           const float& scaleY, const float& posX, const float& posY) :
            textureRect(0,0,0,0), frameCount(0), facing(RIGHT), speed(0) {

        if(!image.loadFromFile(texture_path)){
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

    Entity(const std::string& texture_path, const float& scaleX,
           const float& scaleY, const float& posX, const float& posY, const float& speed_) :
            textureRect(0,0,0,0), frameCount(0), facing(RIGHT), speed(speed_) {

        if(!image.loadFromFile(texture_path)){
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

    Entity(const std::string& texture_path, const int frameCount_ , const direction& facing_, const float& scaleX,
           const float& scaleY, const float& posX, const float& posY, const float& speed_) :
            frameCount(frameCount_), facing(facing_), speed(speed_) {
        if(!image.loadFromFile(texture_path)){
            std::cout << "Trouble loading image!\n";
        }
        textureRect = sf::IntRect(0,0,image.getSize().x / frameCount, image.getSize().y);
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
    friend std::ostream& operator<<(std::ostream& os, const Entity& entity){
        os << "Texture Size: " << entity.texture.getSize().x << "/" << entity.texture.getSize().y << ", Frame Count: "
           << entity.frameCount << ", Facing Direction: " << entity.facing << "\n";

        return os;
    }

    void setPosition(float x, float y){
        sprite.setPosition(x,y);
    }


    void move(sf::Vector2f vector) {
        sprite.move(vector);
    }


    sf::Sprite& getSprite() { return sprite; }
    sf::Texture& getTexture() { return texture; }
    float getSpeed() const { return speed; }



};

class Weapon{
public:
    enum weapon_types{TRUMPET, KEYS, FLUTE};
private:
    weapon_types weapon_type;
    Entity weapon;

    int damage;

public:
    Weapon(weapon_types weapon_type_, const std::string& texture_path, const float& scaleX, const float& scaleY, const float& posX, const float& posY) :
            weapon_type(weapon_type_), weapon(texture_path, scaleX, scaleY, posX, posY){
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

    friend std::ostream& operator<<(std::ostream& os, const Weapon& weapon_){
        os << "Weapon Type: " << weapon_.weapon_type << ", Weapon Damange: " << weapon_.damage << "\n";

        return os;
    }


/*
    void attack(sf::SoundBuffer& soundBuffer){
        if(!soundBuffer.loadFromFile("Sound/Weapons/Trumpet.oog")){
            std::cout << "Error loading Trumpet Sound File!";
            return;
        }

        sf::Sound sound;
        sound.setBuffer(soundBuffer);
        sound.play();
    }*/

    Entity getEntity() { return weapon; }


};

class Player{
private:
    int health = 100;

    Entity player;
    Weapon weapon;

    std::vector<sf::Sprite> sprites;


public:
    Player(const int& health_, const std::string& texture_path, const float& scaleX, const float& scaleY,
           const float& posX, const float& posY, const Weapon::weapon_types weapon_type_,
           const std::string& weapon_texture_path, const float& speed_) :
            health(health_), player(texture_path,
                                    3.f, 3.f, posX, posY, speed_), weapon(weapon_type_, weapon_texture_path,
                                                                          2.3, 2.3,
                                                                          posX, posY){
        //De optimizat/schimbat:
        sf::Image image;

        if(!image.loadFromFile(weapon_texture_path)){
            std::cout << "Trouble loading image!\n";
        }

        weapon.getEntity().setPosition(posX + 0.75 * image.getSize().x * scaleX,
                                       posY + 0.40 * image.getSize().y * scaleY);
        sprites.push_back(player.getSprite());
        sprites.push_back(weapon.getEntity().getSprite());

    }

    Player(const int& health_, const std::string& texture_path, const int frameCount, const Entity::direction& facing, const float& scaleX, const float& scaleY,
           const float& posX, const float& posY, const Weapon::weapon_types weapon_type_,
           const std::string& weapon_texture_path, const float& speed_) :
            health(health_), player(texture_path,frameCount, facing,
                                    3.f, 3.f, posX, posY, speed_),
            weapon(weapon_type_, weapon_texture_path,
                   2.3, 2.3,
                   posX + 0.75 * player.getSprite().getTexture()->getSize().x * scaleX,
                   posY + 0.40 * player.getSprite().getTexture()->getSize().y * scaleY){
        sprites.push_back(player.getSprite());
        sprites.push_back(weapon.getEntity().getSprite());

    }


    friend std::ostream& operator<<(std::ostream& os, const Player& player_){
        os << "Health: " << player_.health << "\n";

        return os;
    }

    std::vector<sf::Sprite> getSprites() const{ return sprites; }

    Entity& getEntity()  { return player; }


    void moveSprites(Entity::direction dir, float delta) {
        float offsetX=0, offsetY=0;

        if(dir == Entity::RIGHT){
            offsetX = player.getSpeed() * delta;

        }
        else if(dir == Entity::LEFT){
            offsetX = -player.getSpeed() * delta;
        }
        else if(dir == Entity::UP){
            offsetY = -player.getSpeed() * delta;
        }
        else if(dir == Entity::DOWN){
            offsetY = player.getSpeed() * delta;
        }

        std::cout << offsetX << " " << offsetY << "\n";

        for (auto &sprite: sprites) {
            sprite.move(offsetX, offsetY);
        }
    }

    //void attack(sf::SoundBuffer& soundBuffer){ weapon.attack(soundBuffer); }

};

class Enemy{
    Entity enemy;
    Entity& target;
    int health;

public:
    Enemy(const std::string& texture_path, const float& scaleX, const float& scaleY,
          const float& posX, const float& posY,const float& speed_, Entity& target_, const int health_) :
            enemy(texture_path, scaleX, scaleY, posX, posY), target(target_), health(health_){

        //TODO Thread de urmarire player!
    }

    Entity& getEntity() { return enemy; }
};


class Scene{
    sf::RenderWindow window;
    sf::Event event;
    std::vector<sf::Image> images;

public:
    Scene(const unsigned int windowWidth, const unsigned int windowHeight, const std::vector<std::string>& image_paths) :
            window(sf::VideoMode{windowWidth, windowHeight}, GAME_TITLE, sf::Style::Default),
            event(){
        window.setVerticalSyncEnabled(true);
        for(const auto& path : image_paths){
            sf::Image image;
            if(!image.loadFromFile(path)){
                std::cout << "Trouble at loading Image File\n";
                continue;
            }
            images.push_back(image);
        }
    }

    Scene(const Scene& other) : window(sf::VideoMode{other.window.getSize().x,
                                                     other.window.getSize().y},
                                       GAME_TITLE, sf::Style::Default),
                                event(other.event), images(other.images){}

    sf::Event getEvent() const { return event; }
    bool isOpen() { return window.isOpen(); }
    void clear(){ window.clear(); }
    void draw(const sf::Sprite& sprite) { window.draw(sprite); }
    void display() { window.display(); }
    void close() { window.close(); }
    bool pollEvent() { return window.pollEvent(event); }
    sf::Event& getEvent() { return event; }

};

class Game{
    Scene scene;
    Player player;
    std::vector<Enemy> enemies;

public:
    Game(const Scene& scene_, Player  player_) : scene(scene_), player(std::move(player_)){
        gameProc();
    }

private:
    void handleEvents(const sf::Event& event){
        switch (event.type) {
            case sf::Event::Closed:
                scene.close();
            default:
                break;
        }
    }

    void addEnemy(const float x, const float y){
        enemies.emplace_back("Textures/Dummy.png", 2.3f, 2.3f, x, y, 0, player.getEntity(), 25);
    }

    void gameProc(){
        addEnemy(300.f, 300.f);

        sf::Clock clock;
        float delta;

        while(scene.isOpen()){
            delta = clock.restart().asSeconds() * 60;

            while(scene.pollEvent()){
                handleEvents(scene.getEvent());
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
               player.getSprites()[0].getPosition().y > 0){
                player.moveSprites(Entity::UP, delta);

            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
               player.getSprites()[0].getPosition().y + floor(player.getSprites()[0].getTexture()->getSize().y) * player.getSprites()[0].getScale().y < 600){
                player.moveSprites(Entity::DOWN, delta);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
               player.getSprites()[0].getPosition().x > 0){
                player.moveSprites(Entity::LEFT, delta);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
               player.getSprites()[0].getPosition().x + floor(player.getSprites()[0].getTexture()->getSize().x) * player.getSprites()[0].getScale().x < 800){
                player.moveSprites(Entity::RIGHT, delta);
            }

            scene.clear();

            for(auto& sprite : player.getSprites()){
                scene.draw(sprite);
            }

            for(auto& enemy : enemies){
                scene.draw(enemy.getEntity().getSprite());
            }

            scene.display();

        }

    }
};

void loadImage(sf::Image& image, const std::string& file_path){
    if(!image.loadFromFile(file_path)){
        std::cout << "Trouble at loading Image File\n";
    }
}

void drawSprites(sf::RenderWindow& renderWindow, const std::vector<sf::Sprite>& sprites){
    for(const auto& i : sprites){
        renderWindow.draw(i);
    }
}


int main(){

    Game game{Scene{800, 600, std::vector<std::string>{
            "Textures/Weapons/Trumpet.png",
            "Textures/Dummy.png",
            "Textures/Player.png"
    }}, Player(100, "Textures/Player_SpriteSheet.png", 2, Entity::RIGHT, 2.3f, 2.3f,
               0,0, Weapon::weapon_types::TRUMPET, "Textures/Weapons/Trumpet.png", 7.5f)};

    return 0;
}