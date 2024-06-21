//
// Created by danai on 5/29/2024.
//

#ifndef OOP_ALERT_H
#define OOP_ALERT_H

#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class Alert {
    sf::Text message;
    sf::Sprite frame;

public:
    Alert(const std::string& message_, const std::string &textureKey, const sf::Font& font, const sf::Vector2u& windowSize);

    sf::Vector2f getPosition() const;
    void move(sf::Vector2f vector);

    sf::Sprite getSprite() const;
    sf::Text getText() const;
};


#endif //OOP_ALERT_H
