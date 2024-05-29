#ifndef OOP_WEAPON_H
#define OOP_WEAPON_H

#pragma once
#include "../Entity/Entity.h"

class Weapon : public Entity{
public:
    enum weapon_types {
        TRUMPET, KEYS, FLUTE
    };
private:
    weapon_types weapon_type;
    int damage;

public:
    Weapon(weapon_types weapon_type_, sf::Texture &texture, const float &scaleX, const float &scaleY,
           const double &posX, const double &posY);

    Weapon(const Weapon& other) = default;
    Weapon& operator=(const Weapon& other) = default;

    friend std::ostream &operator<<(std::ostream &os, const Weapon &weapon_);

    int getDamage() const;

};


#endif //OOP_WEAPON_H
