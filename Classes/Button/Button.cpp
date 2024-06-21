#include <iostream>
#include "Button.h"
#include "../Texture Manager/TextureManager.h"

Button::Button(const std::string& textureKey, const sf::Font &font, const std::string &text_){
    TextureManager::useTexture(textureKey, sprite);

    text.setFont(font);
    text.setCharacterSize(32);
    text.setOutlineThickness(1);
    text.setOutlineColor(sf::Color::Black);
    text.setString(text_);

    sf::FloatRect spriteBounds = sprite.getLocalBounds();
    sf::FloatRect textBounds = text.getLocalBounds();

    text.setPosition(sprite.getPosition().x + spriteBounds.width/2 - textBounds.width/2,
                     sprite.getPosition().y + spriteBounds.height/2 - textBounds.height/2);
}


std::ostream &operator<<(std::ostream &os, const Button &button_) {
    os << "Position: " << button_.sprite.getPosition().x << "," << button_.sprite.getPosition().y <<
       " Text: " << static_cast<std::string>(button_.text.getString()) << "\n";

    return os;
}

const sf::Sprite& Button::getSprite() const { return sprite; }
const sf::Text& Button::getText() const { return text; }

void Button::setPosition(sf::Vector2f vector) {
    sprite.setPosition(vector);
    sf::FloatRect spriteBounds = sprite.getLocalBounds();
    sf::FloatRect textBounds = text.getLocalBounds();

    text.setPosition(sprite.getPosition().x + spriteBounds.width/2 - textBounds.width/2,
                     sprite.getPosition().y + spriteBounds.height/2 - textBounds.height/2 - 10);
}

bool Button::clicked(sf::Event::MouseButtonEvent mouse) {
    sf::IntRect checkRect{static_cast<int>(sprite.getPosition().x),
                          static_cast<int>(sprite.getPosition().y),
                          static_cast<int>(sprite.getTexture()->getSize().x),
                          static_cast<int>(sprite.getTexture()->getSize().y)};

    return checkRect.contains(mouse.x, mouse.y);
}

sf::FloatRect Button::getLocalBounds() const { return sprite.getLocalBounds(); }