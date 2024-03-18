#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

#define GAME_TITLE      "Poo's Musicaly Fight"

class Entity {
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;

public:
    Entity(const sf::Image &image_, const float& scaleX, const float& scaleY) : image(image_) {
        if (!texture.loadFromImage(image)) {
            std::cout << "Trouble loading texture image!\n";
        } else {
            sprite.setTexture(texture);
            sprite.setScale(scaleX, scaleY);
        }
    }

    Entity(const sf::Image &image_, const float& scaleX, const float& scaleY, const float& posX, const float& posY) : image(image_) {
        if (!texture.loadFromImage(image)) {
            std::cout << "Trouble loading texture image!\n";
        } else {
            sprite.setTexture(texture);
            sprite.setScale(scaleX, scaleY);
            sprite.setPosition(posX, posY);
        }
    }


    void move(sf::Vector2f vector) {
        sprite.move(vector);
}

     sf::Sprite getSprite() const { return sprite; }
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
            case KEYS:
                damage = 40;
            case FLUTE:
                damage = 50;
        }
    }

    Entity getEntity() const { return weapon; }

};

class Player{
    int health = 100;
    float speed;
    Entity player;
    Weapon weapon;

    std::vector<sf::Sprite> sprites;

public:
    Player(const int& health_, const sf::Image& player_image_, const float& scaleX, const float& scaleY,
           const float& posX, const float& posY, const Weapon::weapon_types weapon_type_,
           const sf::Image& weapon_image_, const float& speed_) :
    health(health_), speed(speed_), player(player_image_,
                                           3.f, 3.f, posX, posY), weapon(weapon_type_, weapon_image_,
                                                                            2.3, 2.3,
                                                                            posX + 0.75 * player_image_.getSize().x * scaleX,
                                                                            posY + 0.40 * player_image_.getSize().y * scaleY){
        sprites.push_back(player.getSprite());
        sprites.push_back(weapon.getEntity().getSprite());
    }

    std::vector<sf::Sprite> getSprites() const{ return sprites; }
    float getSpeed() const { return speed; }

    void moveSprites(float offsetX, float offsetY) {
        for (auto &sprite: sprites) {
            sprite.move(offsetX, offsetY);
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

    sf::RenderWindow window{sf::VideoMode{800,600}, GAME_TITLE, sf::Style::Default};
    window.setVerticalSyncEnabled(true);

    // #    Loading Images for textures
    sf::Image trumpet;
    loadImage(trumpet, "Textures/Weapons/Trumpet.png");

    sf::Image dummy;
    loadImage(dummy, "Textures/Dummy.png");

    // #    ---


    Player player(100, dummy, 2.3f, 2.3f, 0,0, Weapon::weapon_types::TRUMPET, trumpet, 2.3f);

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
        std::cout << player.getSprites()[0].getPosition().x << " " << player.getSprites()[0].getPosition().y << "\n";
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
        player.getSprites()[0].getPosition().y > 0){
            player.moveSprites(0.f, -player.getSpeed());

        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
        player.getSprites()[0].getPosition().y + floor(player.getSprites()[0].getTexture()->getSize().y) * player.getSprites()[0].getScale().y < 600){
            player.moveSprites(0.f,player.getSpeed());
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
        player.getSprites()[0].getPosition().x > 0){
            player.moveSprites(-player.getSpeed(),0.f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
        player.getSprites()[0].getPosition().x + floor(player.getSprites()[0].getTexture()->getSize().x) * player.getSprites()[0].getScale().x < 800){
            player.moveSprites(player.getSpeed(),0.f);
        }

        window.clear(sf::Color(143, 143, 143));
        drawSprites(window, player.getSprites());
        window.display();

    }

    return 0;
}