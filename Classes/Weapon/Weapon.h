#ifndef OOP_WEAPON_H
#define OOP_WEAPON_H

#pragma once
#include "../Entity/Entity.h"

class Weapon {
public:
    enum weapon_types {
        TRUMPET, KEYS, FLUTE
    };
private:
    weapon_types weapon_type;
    Entity entity;

    int damage;

public:
    Weapon(weapon_types weapon_type_, sf::Texture &texture, const float &scaleX, const float &scaleY,
           const double &posX, const double &posY);

    friend std::ostream &operator<<(std::ostream &os, const Weapon &weapon_);

    void move(sf::Vector2f vector);

    sf::Sprite getSprite() const;
    Hitbox getHitbox() const;

};


#endif //OOP_WEAPON_H
