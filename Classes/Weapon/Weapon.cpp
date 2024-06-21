#include "Weapon.h"

Weapon::Weapon(weapon_types weapon_type_, const std::string &textureKey, const float &scaleX, const float &scaleY,
const double &posX, const double &posY) :
Entity(textureKey, scaleX, scaleY, posX, posY), weapon_type(weapon_type_) {
    switch (weapon_type) {
        case TRUMPET:
            damage = 50;
            break;
        case KEYS:
            damage = 40;
            break;
        case FLUTE:
            damage = 50;
            break;
    }
}

std::ostream &operator<<(std::ostream &os, const Weapon &weapon_) {
    os << "Weapon Type: " << weapon_.weapon_type << ", Weapon Damange: " << weapon_.damage << "\n";

    return os;
}

int Weapon::getDamage() const {
    return damage;
}