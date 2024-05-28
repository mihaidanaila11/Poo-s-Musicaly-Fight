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

private:
    sf::IntRect textureRect;
    sf::Texture& texture;

    unsigned int frameSize;
    unsigned int frameCount;



    float speed;

public:
    //Constructor de copiere
    //Ignor warning pt constructor de copiere pt ca face parte din cerinta
    //NOLINTNEXTLINE
    Entity(const Entity &other);

    // Constructor operator= de copiere
    //Ignor warning pt operator= pt ca face parte din cerinta
    //NOLINTNEXTLINE
    Entity &operator=(const Entity &other);

    // Destructor
    virtual ~Entity();

    Entity(sf::Texture& texture_, const float &scaleX,
           const float &scaleY, const double &posX, const double &posY);

    Entity(sf::Texture& texture_, const int& frameCount_, const direction& facing_, const sf::Vector2f& hitboxOffset, const float& scaleX,
           const float& scaleY, const float& posX, const float& posY, const float& speed_);

    // Operator <<
    friend std::ostream &operator<<(std::ostream &os, const Entity &entity);

    void setTextureFrame(const int& frame);

    virtual void move(sf::Vector2f vector);


    const sf::Sprite& getSprite() const;
    unsigned int getFrameCount() const;
    unsigned int getFrameSize() const;

    sf::Texture &getTexture();
    Hitbox getHitbox() const;

    float getSpeed() const;

    sf::Vector2f getPosition() const;


};


#endif //OOP_ENTITY_H
