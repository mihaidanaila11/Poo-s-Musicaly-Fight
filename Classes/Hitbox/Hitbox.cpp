#include "Hitbox.h"

Hitbox::Hitbox(const sf::Sprite &sprite, const unsigned int &frameCount, const unsigned int &frameSize,
               const sf::Vector2f &hitboxOffset) {

    rect.setSize(sf::Vector2f{(((float)sprite.getTexture()->getSize().x * sprite.getScale().x +(2 * hitboxOffset.x)) / (float)frameCount),
                              (float) sprite.getTexture()->getSize().y * sprite.getScale().y +(2*hitboxOffset.y)});

    rect.setPosition(sf::Vector2f{sprite.getPosition().x + (float)frameSize / 2 * sprite.getScale().x - rect.getSize().x / 2,
                                  sprite.getPosition().y + (float)sprite.getTexture()->getSize().y / 2 * sprite.getScale().y - rect.getSize().y / 2});
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color::Red);
    rect.setOutlineThickness(3.f);
}

Hitbox::Hitbox(const sf::Sprite &sprite) {
    rect.setSize(sf::Vector2f{(float) sprite.getTexture()->getSize().x * sprite.getScale().x,
                              (float) sprite.getTexture()->getSize().y * sprite.getScale().y});

    rect.setPosition(sprite.getPosition());
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color::Red);
    rect.setOutlineThickness(3.f);
}

bool Hitbox::intersects(const Hitbox &other) {
    float x1 = rect.getPosition().x;
    float y1 = rect.getPosition().y;
    float x2 = x1 + ((float) rect.getSize().x);
    float y2 = y1 + ((float) rect.getSize().y);

    float x3 = other.getRect().getPosition().x;
    float y3 = other.getRect().getPosition().y;
    float x4 = x3 + ((float) other.rect.getSize().x);
    float y4 = y3 + ((float) other.rect.getSize().y);;

    if (x1 > x4 || x3 > x2) {
        return false;

    }

    if (y2 < y3 || y4 < y1) {
        return false;
    }

    return true;
}

sf::RectangleShape Hitbox::getRect() const { return rect; }

void Hitbox::setPosition(const float& x, const float& y){
    rect.setPosition(x, y);
}

void Hitbox::move(sf::Vector2f vector){
    rect.move(vector);
}