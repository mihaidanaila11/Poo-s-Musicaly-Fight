#include "Enemy.h"

Enemy::Enemy(sf::Texture& texture, const float &scaleX, const float &scaleY,
const float &posX, const float &posY, const int &health_, const float &speed_, const int& attackDamage_) :
Alive(health_, texture, scaleX, scaleY, posX, posY, speed_), attackDamage(attackDamage_) {}

std::ostream &operator<<(std::ostream &os, const Enemy &enemy_) {
    os << "Health: " << enemy_.health << ", Speed: " << enemy_.getSpeed() << "\n";

    return os;
}


void Enemy::damage(int damage, std::vector<Enemy*> &enemies, int index) {
    health -= damage;
    if (health <= 0) {
        delete enemies[index];
        enemies.erase(enemies.begin() + index);
    }
}