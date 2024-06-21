#ifndef OOP_ENTITY_H
#define OOP_ENTITY_H

#pragma once

#include "SFML/Graphics.hpp"
#include "../Hitbox/Hitbox.h"
#include "iostream"

class Entity {
public:
    enum direction {
        LEFT, RIGHT, UP, DOWN
    };

protected:
    sf::Sprite sprite;
    Hitbox hitbox;

    void setSpeed(const float& speed_);

    //Constructor de copiere
    //Ignor warning pt constructor de copiere pt ca face parte din cerinta
    //NOLINTNEXTLINE
    Entity(const Entity &other);

    // Constructor operator= de copiere
    //Ignor warning pt operator= pt ca face parte din cerinta
    //NOLINTNEXTLINE
    Entity &operator=(const Entity &other);

private:
    sf::IntRect textureRect;

    unsigned int frameSize;
    unsigned int frameCount;

    float speed;

public:


    // Destructor
    virtual ~Entity();

    Entity(const std::string& textureKey, const float &scaleX,
           const float &scaleY, const double &posX, const double &posY);

    Entity(const std::string& textureKey, const float &scaleX,
           const float &scaleY, const double &posX, const double &posY, const float& speed_);

    Entity(const std::string& textureKey, const int& frameCount_, const sf::Vector2f& hitboxOffset, const float& scaleX,
           const float& scaleY, const float& posX, const float& posY, const float& speed_);

    // Operator <<
    friend std::ostream &operator<<(std::ostream &os, const Entity &entity);

    void setTextureFrame(const int& frame);

    virtual void move(sf::Vector2f vector);

    void setPosition(const float& x, const float& y);

    const sf::Sprite& getSprite() const;
    unsigned int getFrameCount() const;
    unsigned int getFrameSize() const;

    Hitbox getHitbox() const;

    float getSpeed() const;

    sf::Vector2f getPosition() const;

    void setOpacity(const sf::Uint8& opacity);

};


#endif //OOP_ENTITY_H


