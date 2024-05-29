#ifndef OOP_GHOSTENEMY_H
#define OOP_GHOSTENEMY_H


#include "../../Enemy.h"

class GhostEnemy : public Enemy{
    sf::Clock ghostClock;
    static bool ghosted;
    static float ghostDuration;
    float originalSpeed;
public:
    GhostEnemy(sf::Texture& texture, const float &scaleX, const float &scaleY,
               const float &posX, const float &posY, const int &health_, const float &speed_, const int& attackDamage_);

    void move(sf::Vector2f vector) override;

    void attack(Alive &target) override;

    Enemy * clone() override;
};


#endif //OOP_GHOSTENEMY_H
