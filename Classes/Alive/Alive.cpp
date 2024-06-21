#include "Alive.h"

Alive::Alive(const int &health_, const std::string& textureKey, const int& frameCount, const sf::Vector2f &hitboxOffset,
             const float &scaleX, const float &scaleY, const float &posX, const float &posY, const float &speed_):
        Entity(textureKey, frameCount, hitboxOffset,
              scaleX, scaleY, posX, posY, speed_), health(health_), alive(true){}

void Alive::damage(const int &damageValue) {
    health -= damageValue;
    if(health <= 0)
        alive = false;
}

Alive::Alive(const int &health_, const std::string& textureKey, const float &scaleX, const float &scaleY,
             const float &posX, const float &posY, const float &speed_):
        Entity(textureKey, scaleX, scaleY, posX, posY, speed_), health(health_), alive(true){

}

bool Alive::isAlive() const {
    return alive;
}
