//
// Created by danai on 5/29/2024.
//

#ifndef OOP_ALIVE_H
#define OOP_ALIVE_H


#include "../Entity/Entity.h"

class Alive : public Entity{
protected:
    int health;
    bool alive;
public:
    Alive(const int &health_, sf::Texture& texture, const int& frameCount, const sf::Vector2f& hitboxOffset,
          const float &scaleX, const float &scaleY,
          const float &posX, const float &posY, const float &speed_);

    Alive(const int &health_, sf::Texture& texture,
          const float &scaleX, const float &scaleY,
          const float &posX, const float &posY, const float &speed_);

    virtual void damage(const int& damageValue);

    bool isAlive() const;
};


#endif //OOP_ALIVE_H
