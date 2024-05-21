#include "Enemy.h"

Enemy::Enemy(sf::Texture& texture, const float &scaleX, const float &scaleY,
const float &posX, const float &posY, const int &health_, const float &speed_) :
entity(texture, scaleX, scaleY, posX, posY), speed(speed_), health(health_) {}

std::ostream &operator<<(std::ostream &os, const Enemy &enemy_) {
    os << "Health: " << enemy_.health << ", Speed: " << enemy_.speed << "\n";

    return os;
}

const sf::Sprite& Enemy::getSprite() const { return entity.getSprite(); }

sf::Vector2f Enemy::getPosition() const { return entity.getPosition(); }

void Enemy::move(sf::Vector2f vector){
    entity.move(vector);
}

float Enemy::getSpeed() const { return speed; }
Hitbox Enemy::getHitbox() const { return entity.getHitbox(); }

void Enemy::damage(int damage, std::vector<Enemy> &enemies, int index) {
    health -= damage;
    if (health <= 0) {
        enemies.erase(enemies.begin() + index);
    }
}