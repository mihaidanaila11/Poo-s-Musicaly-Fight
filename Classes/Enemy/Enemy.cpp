#include "Enemy.h"

Enemy::Enemy(EnemyType type_, const std::string& textureKey, const float &scaleX, const float &scaleY,
const float &posX, const float &posY, const int &health_, const float &speed_, const int& attackDamage_) : Alive(health_, textureKey, scaleX, scaleY, posX, posY, speed_),
type(type_), attackDamage(attackDamage_) {
    std::cout << "Am creat inamic la adresa: " << &sprite << "\n";
}

std::ostream &operator<<(std::ostream &os, const Enemy &enemy_) {
    os << "Health: " << enemy_.health << ", Speed: " << enemy_.getSpeed() << "\n";

    return os;
}