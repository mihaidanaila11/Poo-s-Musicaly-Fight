#ifndef OOP_BUTTON_H
#define OOP_BUTTON_H

#pragma once
#include "SFML/Graphics.hpp"

class Button {
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Font font;
    sf::Text text;

public:
    Button(const sf::Texture& texture_, const sf::Font &font, const std::string &text_);

    friend std::ostream &operator<<(std::ostream &os, const Button &button_);

    const sf::Sprite& getSprite() const;
    const sf::Text& getText() const;

    void setPosition(sf::Vector2f vector);

    bool clicked(sf::Event::MouseButtonEvent mouse);

    sf::FloatRect getLocalBounds() const;
};


#endif //OOP_BUTTON_H
