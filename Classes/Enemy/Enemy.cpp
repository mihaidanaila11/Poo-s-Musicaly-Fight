#include "Enemy.h"

Enemy::Enemy(sf::Texture& texture, const float &scaleX, const float &scaleY,
const float &posX, const float &posY, const int &health_, const float &speed_, const int& attackDamage_) :
Alive(health_, texture, scaleX, scaleY, posX, posY, speed_), attackDamage(attackDamage_) {}

std::ostream &operator<<(std::ostream &os, const Enemy &enemy_) {
    os << "Health: " << enemy_.health << ", Speed: " << enemy_.getSpeed() << "\n";

    return os;
}
