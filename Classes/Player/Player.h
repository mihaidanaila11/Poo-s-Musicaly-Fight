#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#pragma once
#include "../Entity/Entity.h"
#include "../Weapon/Weapon.h"
#include "../Enemy/Enemy.h"
#include "cmath"

class Player {
private:
    int health = 100;
    bool alive = true;

    Entity entity;
    Weapon weapon;

    Hitbox attackRange;


public:

    Player(const int &health_, sf::Texture& texture, int frameCount, const Entity::direction &facing,
           const float &scaleX, const float &scaleY,
           const float &posX, const float &posY, const sf::Vector2f& hitboxOffset, const sf::Vector2f& attackRadius, Weapon::weapon_types weapon_type_,
           sf::Texture &weapon_texture, const float &speed_);


    friend std::ostream &operator<<(std::ostream &os, const Player &player_);

    sf::Vector2f getPosition() const;


    void moveSprites(Entity::direction dir, float delta);

    void attack(std::vector<Enemy> &targets);

    void damage(int damage);

    bool isAlive() const;

    const sf::Sprite& getSprite();
    const Weapon& getWeapon() const;

    Hitbox getHitbox() const;
};


#endif //OOP_PLAYER_H
