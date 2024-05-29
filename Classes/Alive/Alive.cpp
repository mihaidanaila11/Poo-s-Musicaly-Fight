#include "Alive.h"

Alive::Alive(const int &health_, sf::Texture &texture, const int& frameCount, const sf::Vector2f &hitboxOffset,
             const float &scaleX, const float &scaleY, const float &posX, const float &posY, const float &speed_):
        Entity( texture, frameCount, hitboxOffset,
              scaleX, scaleY, posX, posY, speed_), health(health_), alive(true){}

void Alive::damage(const int &damageValue) {
    health -= damageValue;
    if(health <= 0)
        alive = false;
}

Alive::Alive(const int &health_, sf::Texture &texture, const float &scaleX, const float &scaleY,
             const float &posX, const float &posY, const float &speed_):
        Entity( texture, scaleX, scaleY, posX, posY, speed_), health(health_), alive(true){

}

bool Alive::isAlive() const {
    return alive;
}
