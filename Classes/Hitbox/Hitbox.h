#ifndef OOP_HITBOX_H
#define OOP_HITBOX_H

#pragma once

#include "SFML/Graphics.hpp"

class Hitbox {
private:
    sf::RectangleShape rect;

public:

    Hitbox() : rect() {}

    Hitbox(const sf::Sprite& sprite, const unsigned int& frameCount, const unsigned int& frameSize, const sf::Vector2f & hitboxOffset);

    explicit Hitbox(const sf::Sprite& sprite);

    bool intersects(const Hitbox& other);

    sf::RectangleShape getRect() const;

    void setPosition(float& x, float& y);

    void move(sf::Vector2f vector);

};


#endif //OOP_HITBOX_H
