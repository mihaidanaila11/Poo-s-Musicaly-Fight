#include "Entity.h"
#include "../Texture Manager/TextureManager.h"

//Constructor de copiere
//Ignor warning pt constructor de copiere pt ca face parte din cerinta
//NOLINTNEXTLINE
Entity::Entity(const Entity &other) : hitbox(other.hitbox), textureRect(other.textureRect),
frameSize(other.frameSize), frameCount(other.frameCount), speed(other.speed) {
    std::cout << "copiere\n";

    TextureManager::useTexture(other.sprite, sprite);
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
    sprite = other.sprite;
    hitbox = other.hitbox;
    frameSize = other.frameSize;
    frameCount = other.frameCount;
    speed = other.speed;

    return *this;
}

// Destructor
Entity::~Entity() {
    TextureManager::removeTexture(sprite);
    std::cout << "Destructorul a fost apelat!\n";
}

Entity::Entity(const std::string& textureKey, const float &scaleX,
const float &scaleY, const double &posX, const double &posY) :
textureRect(), frameCount(1), speed(0) {

    TextureManager::useTexture(textureKey, sprite);

    frameSize = sprite.getTexture()->getSize().x;
    textureRect.width = (int)sprite.getTexture()->getSize().x;
    textureRect.height = (int)sprite.getTexture()->getSize().y;

    sprite.setTextureRect(textureRect);
    sprite.setScale(scaleX, scaleY);
    sprite.setPosition(static_cast<float>(posX), static_cast<float>(posY));

    hitbox = Hitbox{sprite};

}

Entity::Entity(const std::string& textureKey, const float &scaleX,
       const float &scaleY, const double &posX, const double &posY, const float& speed_) :
        textureRect(), frameCount(1), speed(speed_){

    TextureManager::useTexture(textureKey, sprite);

    frameSize = sprite.getTexture()->getSize().x;
    textureRect.width = (int)sprite.getTexture()->getSize().x;
    textureRect.height = (int)sprite.getTexture()->getSize().y;

    sprite.setTextureRect(textureRect);
    sprite.setScale(scaleX, scaleY);
    sprite.setPosition(static_cast<float>(posX), static_cast<float>(posY));

    hitbox = Hitbox{sprite};
}

Entity::Entity(const std::string& textureKey, const int& frameCount_, const sf::Vector2f& hitboxOffset, const float& scaleX,
const float& scaleY, const float& posX, const float& posY, const float& speed_) :frameCount(frameCount_),
speed(speed_) {


    TextureManager::useTexture(textureKey, sprite);

    textureRect = sf::IntRect(0, 0, sprite.getTexture()->getSize().x / frameCount,
                              sprite.getTexture()->getSize().y);
    frameSize = sprite.getTexture()->getSize().x / frameCount;

    sprite.setTextureRect(textureRect);
    sprite.setScale(scaleX, scaleY);
    sprite.setPosition(posX, posY);

    hitbox = Hitbox{sprite, frameCount, frameSize, hitboxOffset};

}

std::ostream &operator<<(std::ostream &os, const Entity &entity) {
    os << "Texture Size: " << entity.sprite.getTexture()->getSize().x << "/" << entity.sprite.getTexture()->getSize().y << ", Frame Count: "
       << entity.frameCount << "\n";

    return os;
}

void Entity::setTextureFrame(const int& frame){

    if(frame*(int)frameSize == textureRect.left){
        return;
    }

    textureRect.left = (int)frameSize*frame;
    sprite.setTextureRect(textureRect);
}

void Entity::move(sf::Vector2f vector) {
    sprite.move(vector);
    hitbox.move(vector);
}

const sf::Sprite& Entity::getSprite() const { return sprite; }
unsigned int Entity::getFrameCount() const {return frameCount; }
unsigned int Entity::getFrameSize() const { return frameSize; }

Hitbox Entity::getHitbox() const { return hitbox; }

float Entity::getSpeed() const { return speed; }

sf::Vector2f Entity::getPosition() const { return sprite.getPosition(); }

void Entity::setOpacity(const sf::Uint8 &opacity) {
    sf::Color color = sprite.getColor();
    sprite.setColor(sf::Color{color.r, color.g, color.b, opacity});
}

void Entity::setPosition(const float &x, const float &y) {
    sprite.setPosition(x,y);
    hitbox.setPosition(x,y);
}

void Entity::setSpeed(const float &speed_) { speed = speed_;}