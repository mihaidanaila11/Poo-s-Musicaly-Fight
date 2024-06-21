#include "Hud.h"

Hud::Hud() = default;

Hud::Hud(const std::string& healthBottomTextureKey, const std::string& healthBarTextureKey, const sf::Vector2u& windowSize,
         const int maxHealth) :
healthBar(healthBottomTextureKey, healthBarTextureKey, maxHealth){
    healthBar.setPosition(0, (float)windowSize.y - healthBar.getGlobalBounds().height);
}

void Hud::updateHealth(int healthValue) {
    healthBar.updateHealthBar(healthValue);
}