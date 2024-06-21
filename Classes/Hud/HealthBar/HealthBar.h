#ifndef OOP_HEALTHBAR_H
#define OOP_HEALTHBAR_H

#pragma once
#include "SFML/Graphics.hpp"
#include "../../Player/Player.h"

class HealthBar {
    sf::Sprite healthBottom;
    sf::Sprite health;

    int maxHealth;

public:
    HealthBar();
    HealthBar(const std::string& healthBottomTextureKey, const std::string& healthTextureKey, int maxHealth_);

    std::vector<sf::Sprite> getSprites() const;

    void setPosition(const float x, const float y);

    sf::FloatRect getGlobalBounds() const;

    void updateHealthBar(int healthValue);
};

#endif //OOP_HEALTHBAR_H
