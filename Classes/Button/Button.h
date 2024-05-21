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
    Button(const std::string &image_path, const std::string &font_path, const std::string &text_);

    friend std::ostream &operator<<(std::ostream &os, const Button &button_);

    std::pair<sf::Sprite, sf::Text> getButton() const;

    void setPosition(sf::Vector2f vector);

    bool clicked(sf::Event::MouseButtonEvent mouse);
};


#endif //OOP_BUTTON_H
