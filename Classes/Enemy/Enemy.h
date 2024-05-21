//
// Created by danai on 5/21/2024.
//

#ifndef OOP_ENEMY_H
#define OOP_ENEMY_H

#include "../Entity/Entity.h"

class Enemy {
    Entity entity;
    float speed;

    int health;

public:
    Enemy(sf::Texture& texture, const float &scaleX, const float &scaleY,
          const float &posX, const float &posY, const int &health_, const float &speed_);

    friend std::ostream &operator<<(std::ostream &os, const Enemy &enemy_);

    const sf::Sprite& getSprite() const;

    sf::Vector2f getPosition() const;

    void move(sf::Vector2f vector);

    float getSpeed() const;
    Hitbox getHitbox() const;

    void damage(int damage, std::vector<Enemy> &enemies, int index);
};


#endif //OOP_ENEMY_H
