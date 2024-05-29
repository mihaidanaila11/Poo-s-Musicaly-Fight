#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#pragma once
#include "../Entity/Entity.h"
#include "../Weapon/Weapon.h"
#include "../Enemy/Enemy.h"
#include "cmath"
#include "../Alive/Alive.h"

class Player : public Alive{
private:
    Weapon weapon;

    Hitbox attackRange;


public:

    Player(const int &health_, sf::Texture& texture, int frameCount,
           const float &scaleX, const float &scaleY,
           const float &posX, const float &posY, const sf::Vector2f& hitboxOffset, const sf::Vector2f& attackRadius, Weapon::weapon_types weapon_type_,
           sf::Texture &weapon_texture, const float &speed_);

    Player(const Player& other) = default;
    Player& operator=(const Player& other) = default;


    friend std::ostream &operator<<(std::ostream &os, const Player &player_);


    void move(sf::Vector2f vector) override;
    void moveSprites(Entity::direction dir, float delta);

    void attack(std::vector<Enemy*> &targets);

    void damage(int damage);

    bool isAlive() const;

    const Weapon& getWeapon() const;
    int getHealth() const;

    Hitbox getAttackRange() const;
};


#endif //OOP_PLAYER_H
