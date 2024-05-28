#ifndef OOP_ENEMY_H
#define OOP_ENEMY_H

#include "../Entity/Entity.h"

class Enemy : public Entity{
    int health;

public:
    Enemy(sf::Texture& texture, const float &scaleX, const float &scaleY,
          const float &posX, const float &posY, const int &health_, const float &speed_);

    friend std::ostream &operator<<(std::ostream &os, const Enemy &enemy_);

    void damage(int damage, std::vector<Enemy> &enemies, int index);
};


#endif //OOP_ENEMY_H
