#include "Player.h"

Player::Player(const int &health_, sf::Texture& texture, const int frameCount,
       const float &scaleX, const float &scaleY,
       const float &posX, const float &posY, const sf::Vector2f& hitboxOffset, const sf::Vector2f& attackRadius, const Weapon::weapon_types weapon_type_,
       sf::Texture &weapon_texture, const float &speed_, const float& damageCooldown_) :Alive(health_, texture, frameCount, hitboxOffset,
                                                                 3.f, 3.f, posX, posY, speed_),
        weapon(weapon_type_, weapon_texture,
               2.3f, 2.3f,
               posX + 0.50 * sprite.getTexture()->getSize().x * scaleX,
               posY + 0.40 * sprite.getTexture()->getSize().y * scaleY),
        attackRange(sprite, Entity::getFrameCount(),
                    Entity::getFrameSize(), attackRadius),
                    damageCooldown(damageCooldown_){
}

std::ostream &operator<<(std::ostream &os, const Player &player_) {
    os << "Health: " << player_.health << ", Alive?: " << player_.alive << "\n";

    return os;
}

void Player::move(sf::Vector2f vector){
    sprite.move(vector);
    hitbox.move(vector);
    attackRange.move(vector);
    weapon.move(vector);
}

void Player::moveSprites(Entity::direction dir, float delta) {
    sf::Vector2f offset{0,0};

    if (dir == Entity::RIGHT) {
        if(sprite.getPosition().x +
           floor(sprite.getTexture()->getSize().x) * sprite.getScale().x >= 800){
            return;
        }
        Entity::setTextureFrame(0);
        offset.x = Entity::getSpeed() * delta;

    } else if (dir == Entity::LEFT) {
        if(sprite.getPosition().x <= 0){
            return;
        }
        Entity::setTextureFrame(1);
        offset.x = -Entity::getSpeed() * delta;
    } else if (dir == Entity::UP) {
        if(sprite.getPosition().y <= 0){
            return;
        }
        offset.y = -Entity::getSpeed() * delta;
    } else if (dir == Entity::DOWN) {
        if(sprite.getPosition().y +
           floor(sprite.getTexture()->getSize().y) * sprite.getScale().y >= 600){
            return;
        }
        offset.y = Entity::getSpeed() * delta;
    }

    Entity::move(offset);
    attackRange.move(offset);
    weapon.move(offset);
}

void Player::attack(Enemy* &target) {
            target->damage(weapon.getDamage());
            return;

}

void Player::damage(const int& damageValue) {
    health -= damageValue;
    std::cout << "Health: " << health << "\n";
    if (health <= 0) {
        alive = false;
    }
    damageCooldownClock.restart();
}

bool Player::isAlive() const { return alive; }

const Weapon& Player::getWeapon() const { return weapon; }

int Player::getHealth() const { return health; }

Hitbox Player::getAttackRange() const {
    return attackRange;
}

bool Player::isDamageable() {
    return damageCooldownClock.getElapsedTime().asSeconds() >= damageCooldown;
}
