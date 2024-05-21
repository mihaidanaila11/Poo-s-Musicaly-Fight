#include "Weapon.h"

Weapon::Weapon(weapon_types weapon_type_, sf::Texture &texture, const float &scaleX, const float &scaleY,
const double &posX, const double &posY) :
weapon_type(weapon_type_), entity(texture, scaleX, scaleY, posX, posY) {
    switch (weapon_type) {
        case TRUMPET:
            damage = 25;
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

void Weapon::move(sf::Vector2f vector) {
    entity.move(vector);
}

sf::Sprite Weapon::getSprite() const { return entity.getSprite(); }
Hitbox Weapon::getHitbox() const { return entity.getHitbox(); }