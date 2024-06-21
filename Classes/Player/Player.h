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
    sf::Clock damageCooldownClock;
    float damageCooldown;


public:

    Player(const int &health_, const std::string& textureKey, int frameCount,
           const float &scaleX, const float &scaleY,
           const float &posX, const float &posY, const sf::Vector2f& hitboxOffset, const sf::Vector2f& attackRadius, Weapon::weapon_types weapon_type_,
           const std::string &weapon_textureKey, const float &speed_, const float& damageCooldown_);

    Player(const Player& other) = default;
    Player& operator=(const Player& other) = default;


    friend std::ostream &operator<<(std::ostream &os, const Player &player_);


    void move(sf::Vector2f vector) override;
    void moveSprites(Entity::direction dir, float delta);

    void attack(Enemy* target);

    void damage(const int& damageValue) override;

    const Weapon& getWeapon() const;
    int getHealth() const;

    Hitbox getAttackRange() const;

    bool isDamageable();
};


#endif //OOP_PLAYER_H
