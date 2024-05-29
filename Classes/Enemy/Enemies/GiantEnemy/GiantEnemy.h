#ifndef OOP_GIANTENEMY_H
#define OOP_GIANTENEMY_H


#include "../../Enemy.h"

class GiantEnemy : public Enemy{
public:

    GiantEnemy(sf::Texture &texture, const float &scaleX, const float &scaleY, const float &posX, const float &posY,
               const int &health_, const float &speed_, const int &attackDamage_);

    Enemy * clone() override;
        void attack(Alive &target) override;
};


#endif //OOP_GIANTENEMY_H
