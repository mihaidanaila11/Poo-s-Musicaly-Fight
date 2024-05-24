#include "Hud.h"

Hud::Hud() = default;

Hud::Hud(const sf::Texture& healthBottomTexture, const sf::Texture& healthBarTexture, const sf::Vector2u& windowSize,
         const int maxHealth) :
healthBar(healthBottomTexture, healthBarTexture, maxHealth){
    healthBar.setPosition(0, (float)windowSize.y - healthBar.getGlobalBounds().height);
}

void Hud::updateHealth(int healthValue) {
    healthBar.updateHealthBar(healthValue);
}