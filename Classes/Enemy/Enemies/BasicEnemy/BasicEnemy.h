//
// Created by danai on 5/28/2024.
//

#ifndef OOP_BASICENEMY_H
#define OOP_BASICENEMY_H


#include "../../Enemy.h"

class BasicEnemy : public Enemy{
    using Enemy::Enemy;

public:
    Enemy* clone() override;

    void attack(Alive& target) override;
};


#endif //OOP_BASICENEMY_H
