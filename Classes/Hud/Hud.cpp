#include "Hud.h"

Hud::Hud() = default;

Hud::Hud(const std::string& healthBottomTextureKey, const std::string& healthBarTextureKey, const sf::Vector2u& windowSize,
         const int maxHealth, const sf::Font& font) :
healthBar(healthBottomTextureKey, healthBarTextureKey, maxHealth),
score(font, 0){
    healthBar.setPosition(0, (float)windowSize.y - healthBar.getGlobalBounds().height);
    score.setPosition(sf::Vector2f((float)windowSize.x - score.getGlobalBounds().width * 1.2,
        score.getGlobalBounds().height * 0.5));
}

void Hud::updateHealth(int healthValue) {
    healthBar.updateHealthBar(healthValue);
}

Score& Hud::getScore() {
    return score;
}