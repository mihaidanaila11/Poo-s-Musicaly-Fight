#ifndef OOP_GHOSTENEMY_H
#define OOP_GHOSTENEMY_H


#include "../../Enemy.h"

class GhostEnemy : public Enemy{
    using Enemy::Enemy;
    sf::Clock ghostClock;
    static bool ghosted;
    static float ghostDuration;
public:
    void move(sf::Vector2f vector) override;

    void attack(Alive &target) override;

    Enemy * clone() override;
};


#endif //OOP_GHOSTENEMY_H
