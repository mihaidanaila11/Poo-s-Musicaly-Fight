#ifndef OOP_ENEMY_H
#define OOP_ENEMY_H

#include "../Entity/Entity.h"
#include "../Alive/Alive.h"

class Enemy : public Alive{
public:
    enum EnemyType{
        BASIC,
        GHOST,
        GIANT,

        ENUM_END
    };

protected:
int attackDamage;

Enemy(const Enemy& other) = default;
Enemy& operator=(const Enemy& other) = default;

public:


    Enemy(const std::string& textureKey, const float &scaleX, const float &scaleY,
          const float &posX, const float &posY, const int &health_, const float &speed_, const int& attackDamage_);

    friend std::ostream &operator<<(std::ostream &os, const Enemy &enemy_);

    virtual Enemy* clone() = 0;

    virtual void attack(Alive& target) = 0;

};


#endif //OOP_ENEMY_H
