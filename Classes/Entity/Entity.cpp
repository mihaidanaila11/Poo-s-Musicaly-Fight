//
// Created by danai on 5/21/2024.
//

#include "Entity.h"

//Constructor de copiere
//Ignor warning pt constructor de copiere pt ca face parte din cerinta
//NOLINTNEXTLINE
Entity::Entity(const Entity &other) : textureRect(other.textureRect), texture(other.texture),
                                      frameSize(other.frameSize), frameCount(other.frameCount), hitbox(other.hitbox), speed(other.speed) {
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
Entity &Entity::operator=(const Entity &other) {
    textureRect = other.textureRect;
    texture = other.texture;
    sprite = other.sprite;
    hitbox = other.hitbox;
    frameSize = other.frameSize;
    frameCount = other.frameCount;
    speed = other.speed;

    return *this;
}

// Destructor
Entity::~Entity() {
    std::cout << "Destructorul a fost apelat!\n";
}

Entity::Entity(sf::Texture& texture_, const float &scaleX,
const float &scaleY, const double &posX, const double &posY) :
textureRect(), texture(texture_), frameCount(1), speed(0) {

    frameSize = texture.getSize().x;
    textureRect.width = (int)texture.getSize().x;
    textureRect.height = (int)texture.getSize().y;

    sprite.setTexture(texture);
    sprite.setTextureRect(textureRect);
    sprite.setScale(scaleX, scaleY);
    sprite.setPosition(static_cast<float>(posX), static_cast<float>(posY));

    hitbox = Hitbox{sprite};

}

Entity::Entity(sf::Texture& texture_, const int& frameCount_, const direction& facing_, const sf::Vector2f& hitboxOffset, const float& scaleX,
const float& scaleY, const float& posX, const float& posY, const float& speed_) : texture(texture_),
frameCount(frameCount_), speed(speed_) {

    textureRect = sf::IntRect(0, 0, texture.getSize().x / frameCount, texture.getSize().y);
    frameSize = texture.getSize().x / frameCount;
    sprite.setTexture(texture);
    sprite.setTextureRect(textureRect);
    sprite.setScale(scaleX, scaleY);
    sprite.setPosition(posX, posY);

    hitbox = Hitbox{sprite, frameCount, frameSize, hitboxOffset};

}

std::ostream &operator<<(std::ostream &os, const Entity &entity) {
    os << "Texture Size: " << entity.texture.getSize().x << "/" << entity.texture.getSize().y << ", Frame Count: "
       << entity.frameCount << "\n";

    return os;
}

void Entity::setTextureFrame(const int& frame){

    if(frame*(int)frameSize == textureRect.left){
        return;
    }

    textureRect.left = (int)frameSize*frame;
    sprite.setTextureRect(textureRect);

    std::cout << sprite.getTextureRect().left<< "\n";
}

void Entity::move(sf::Vector2f vector) {
    sprite.move(vector);
    hitbox.move(vector);
}

const sf::Sprite& Entity::getSprite() const { return sprite; }
unsigned int Entity::getFrameCount() const {return frameCount; }
unsigned int Entity::getFrameSize() const { return frameSize; }

sf::Texture& Entity::getTexture() { return texture; }
Hitbox Entity::getHitbox() const { return hitbox; }

float Entity::getSpeed() const { return speed; }

sf::Vector2f Entity::getPosition() const { return sprite.getPosition(); }