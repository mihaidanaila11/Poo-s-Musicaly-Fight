#ifndef OOP_HUD_H
#define OOP_HUD_H

#pragma once
#include "SFML/Graphics.hpp"
#include "HealthBar/HealthBar.h"

class Hud {
    HealthBar healthBar;

public:
    Hud();
    Hud(const sf::Texture& healthBottomTexture, const sf::Texture& healthBarTexture, const sf::Vector2u& windowSize,
        int maxHealth);

    std::vector<sf::Sprite> getSprites() const {
        std::vector<sf::Sprite> sprites;
        for(const auto& sprite : healthBar.getSprites()){
            sprites.push_back(sprite);
        }

        return sprites;
    };

    void updateHealth(int healthValue);
};


#endif //OOP_HUD_H
