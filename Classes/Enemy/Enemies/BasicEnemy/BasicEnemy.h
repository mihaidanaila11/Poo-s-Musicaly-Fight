//
// Created by danai on 5/28/2024.
//

#ifndef OOP_BASICENEMY_H
#define OOP_BASICENEMY_H


#include "../../Enemy.h"

class BasicEnemy : public Enemy{

public:
    BasicEnemy(sf::Texture& texture, const float &scaleX, const float &scaleY,
               const float &posX, const float &posY, const int &health_, const float &speed_, const int& attackDamage_);
    Enemy* clone() override;

    void attack(Alive& target) override;
};


#endif //OOP_BASICENEMY_H
