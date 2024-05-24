#include "HealthBar.h"

HealthBar::HealthBar() = default;

HealthBar::HealthBar(const sf::Texture &healthBottomTexture, const sf::Texture &healthTexture, const int maxHealth_)
: maxHealth(maxHealth_){
    healthBottom.setTexture(healthBottomTexture);
    health.setTexture(healthTexture);

    healthBottom.setScale(3.f,3.f);
    health.setScale(3.f,3.f);
}

std::vector<sf::Sprite> HealthBar::getSprites() const { return std::vector<sf::Sprite>{healthBottom,health}; }

void HealthBar::setPosition(const float x, const float y) {
    healthBottom.setPosition(x,y);
    health.setPosition(x,y);
}

void HealthBar::updateHealthBar(int healthValue){
    if(healthValue < 0)
        healthValue = 0;

    sf::IntRect rect = health.getTextureRect();
    rect.width = (healthValue * (int)health.getTexture()->getSize().x) / maxHealth;
    std::cout << "update :" << healthValue << '\n';
    health.setTextureRect(rect);
}

sf::FloatRect HealthBar::getGlobalBounds() const{ return healthBottom.getGlobalBounds(); }