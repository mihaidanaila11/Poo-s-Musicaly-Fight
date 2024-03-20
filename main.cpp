#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <SFML/Audio.hpp>

#define GAME_TITLE      "Poo's Musicaly Fight"

class Entity {
public:
    enum direction{LEFT, RIGHT};

private:
    sf::Image image;
    sf::IntRect textureRect;
    sf::Texture texture;
    sf::Sprite sprite;

    int frameSize;
    int frameCount;


    direction facing;
    float speed;

public:
    //Constructor de copiere
    Entity(const Entity& other) : image(other.image), textureRect(other.textureRect), texture(other.texture),
        sprite(other.sprite), frameSize(other.frameSize), frameCount(other.frameCount), facing(other.facing), speed(other.speed){}

    // Constructor operator= de copiere
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

    Entity(const sf::Image &image_, const float& scaleX, const float& scaleY, const float& posX, const float& posY) : image(image_), textureRect(0,0,0,0),
    frameSize(image_.getSize().x), frameCount(0), facing(RIGHT) {
        if (!texture.loadFromImage(image)) {
            std::cout << "Trouble loading texture image!\n";
        } else {
            sprite.setTexture(texture);
            sprite.setScale(scaleX, scaleY);
            sprite.setPosition(posX, posY);
        }
    }

    Entity(const sf::Image &image_, const int frameCount_ , const direction& facing_, const float& scaleX,
           const float& scaleY, const float& posX, const float& posY, const float& speed_) :
           image(image_), frameCount(frameCount_), facing(facing_), speed(speed_) {
        textureRect = sf::IntRect(0,0,image_.getSize().x / frameCount, image.getSize().y);
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


    void move(sf::Vector2f vector) {
        sprite.move(vector);
    }

    sf::Sprite getSprite() const { return sprite; }
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
    Weapon(weapon_types weapon_type_, const sf::Image& image_, const float& scaleX, const float& scaleY, const float& posX, const float& posY) :
        weapon_type(weapon_type_), weapon(image_, scaleX, scaleY, posX, posY){
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

    friend std::ostream& operator<<(std::ostream& os, const Weapon weapon_){
        os << "Weapon Type: " << weapon_.weapon_type << ", Weapon Damange: " << weapon_.damage << "\n";

        return os;
    }

    void attack(sf::SoundBuffer& soundBuffer){
        if(!soundBuffer.loadFromFile("Sound/Weapons/Trumpet.oog")){
            std::cout << "Error loading Trumpet Sound File!";
            return;
        }

        sf::Sound sound;
        sound.setBuffer(soundBuffer);
        sound.play();
    }

    Entity getEntity() const { return weapon; }

};

class Player{
private:
    int health = 100;

    Entity player;
    Weapon weapon;

    std::vector<sf::Sprite> sprites;

public:
    Player(const int& health_, const sf::Image& player_image_, const float& scaleX, const float& scaleY,
           const float& posX, const float& posY, const Weapon::weapon_types weapon_type_,
           const sf::Image& weapon_image_, const float& speed_) :
    health(health_), player(player_image_,
                                           3.f, 3.f, posX, posY), weapon(weapon_type_, weapon_image_,
                                                                            2.3, 2.3,
                                                                            posX + 0.75 * player_image_.getSize().x * scaleX,
                                                                            posY + 0.40 * player_image_.getSize().y * scaleY){
        sprites.push_back(player.getSprite());
        sprites.push_back(weapon.getEntity().getSprite());

    }

    Player(const int& health_, const sf::Image& player_image_, const int frameCount, const Entity::direction& facing, const float& scaleX, const float& scaleY,
           const float& posX, const float& posY, const Weapon::weapon_types weapon_type_,
           const sf::Image& weapon_image_, const float& speed_) :
            health(health_), player(player_image_,frameCount, facing,
                                                   3.f, 3.f, posX, posY, speed_), weapon(weapon_type_, weapon_image_,
                                                                                 2.3, 2.3,
                                                                                 posX + 0.75 * player.getSprite().getTexture()->getSize().x * scaleX,
                                                                                 posY + 0.40 * player.getSprite().getTexture()->getSize().y * scaleY){
        sprites.push_back(player.getSprite());
        sprites.push_back(weapon.getEntity().getSprite());

    }

    friend std::ostream& operator<<(std::ostream& os, const Player player_){
        os << "Health: " << player_.health << "\n";

        return os;
    }

    std::vector<sf::Sprite> getSprites() const{ return sprites; }

    Entity getEntity() const { return player; }

    void moveSprites(float offsetX, float offsetY) {
        for (auto &sprite: sprites) {
            sprite.move(offsetX, offsetY);
        }
    }

    void attack(sf::SoundBuffer& soundBuffer){ weapon.attack(soundBuffer); }

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
    std::cout << sizeof(int*);

    sf::RenderWindow window{sf::VideoMode{800,600}, GAME_TITLE, sf::Style::Default};
    window.setVerticalSyncEnabled(true);

    // #    Loading Images for textures
    sf::Image trumpet;
    loadImage(trumpet, "Textures/Weapons/Trumpet.png");

    sf::Image dummy;
    loadImage(dummy, "Textures/Dummy.png");

    sf::Image player_1;
    loadImage(dummy, "Textures/Player.png");

    sf::Image player_spriteSheet;
    loadImage(player_spriteSheet, "Textures/Player_SpriteSheet.png");

    // #    ---

    // #    Loading Sounds

    sf::SoundBuffer buffer;
    //#     ---
    Player player(100, player_spriteSheet, 2, Entity::RIGHT, 2.3f, 2.3f, 0,0, Weapon::weapon_types::TRUMPET, trumpet, 2.3f);

    while(window.isOpen()){

        sf::Event event{};
        while (window.pollEvent(event)){
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();

                default:
                    continue;
            }
        }
        //std::cout << player.getSprites()[0].getPosition().x << " " << player.getSprites()[0].getPosition().y << "\n";
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
        player.getSprites()[0].getPosition().y > 0){
            player.moveSprites(0.f, -player.getEntity().getSpeed());

        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
        player.getSprites()[0].getPosition().y + floor(player.getSprites()[0].getTexture()->getSize().y) * player.getSprites()[0].getScale().y < 600){
            player.moveSprites(0.f,player.getEntity().getSpeed());
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
        player.getSprites()[0].getPosition().x > 0){
            player.moveSprites(-player.getEntity().getSpeed(),0.f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
        player.getSprites()[0].getPosition().x + floor(player.getSprites()[0].getTexture()->getSize().x) * player.getSprites()[0].getScale().x < 800){
            player.moveSprites(player.getEntity().getSpeed(),0.f);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            player.attack(buffer);
        }

        window.clear(sf::Color(143, 143, 143));
        drawSprites(window, player.getSprites());

        window.display();

    }

    return 0;
}