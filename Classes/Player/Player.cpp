#include "Player.h"

Player::Player(const int &health_, sf::Texture& texture, const int frameCount, const Entity::direction &facing,
       const float &scaleX, const float &scaleY,
       const float &posX, const float &posY, const sf::Vector2f& hitboxOffset, const sf::Vector2f& attackRadius, const Weapon::weapon_types weapon_type_,
       sf::Texture &weapon_texture, const float &speed_) :
        health(health_), entity(texture, frameCount, facing, hitboxOffset,
                                3.f, 3.f, posX, posY, speed_),
        weapon(weapon_type_, weapon_texture,
               2.3f, 2.3f,
               posX + 0.50 * entity.getSprite().getTexture()->getSize().x * scaleX,
               posY + 0.40 * entity.getSprite().getTexture()->getSize().y * scaleY),
        attackRange(entity.getSprite(), entity.getFrameCount(),
                    entity.getFrameSize(), attackRadius){
}

std::ostream &operator<<(std::ostream &os, const Player &player_) {
    os << "Health: " << player_.health << ", Alive?: " << player_.alive << "\n";

    return os;
}

sf::Vector2f Player::getPosition() const { return entity.getPosition(); }

void Player::moveSprites(Entity::direction dir, float delta) {
    sf::Vector2f offset{0,0};

    if (dir == Entity::RIGHT) {
        if(entity.getPosition().x +
           floor(entity.getTexture().getSize().x) * entity.getSprite().getScale().x >= 800){
            return;
        }
        entity.setTextureFrame(0);
        offset.x = entity.getSpeed() * delta;

    } else if (dir == Entity::LEFT) {
        if(entity.getPosition().x <= 0){
            return;
        }
        entity.setTextureFrame(1);
        offset.x = -entity.getSpeed() * delta;
    } else if (dir == Entity::UP) {
        if(entity.getPosition().y <= 0){
            return;
        }
        offset.y = -entity.getSpeed() * delta;
    } else if (dir == Entity::DOWN) {
        if(entity.getPosition().y +
           floor(entity.getTexture().getSize().y) * entity.getSprite().getScale().y >= 600){
            return;
        }
        offset.y = entity.getSpeed() * delta;
    }

    entity.move(offset);
    attackRange.move(offset);
    weapon.move(offset);
}

void Player::attack(std::vector<Enemy> &targets) {
    for (unsigned int i = 0; i < targets.size(); i++) {
        if (attackRange.intersects(targets[i].getHitbox())) {
            targets[i].damage(50, targets, i);
            return;
        }
    }
}

void Player::damage(int damage) {
    health -= damage;
    std::cout << "Health: " << health << "\n";
    if (health <= 0) {
        alive = false;
    }
}

bool Player::isAlive() const { return alive; }

const sf::Sprite& Player::getSprite() { return entity.getSprite(); }
const Weapon& Player::getWeapon() const { return weapon; }

int Player::getHealth() const { return health; }

Hitbox Player::getHitbox() const { return entity.getHitbox(); }