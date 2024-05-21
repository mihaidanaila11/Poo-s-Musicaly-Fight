#include "Button.h"

Button::Button(const std::string &image_path, const std::string &font_path, const std::string &text_) {
    sf::Image image;
    image.loadFromFile(image_path);
    texture.loadFromImage(image);

    sprite.setTexture(texture);

    font.loadFromFile(font_path);
    text.setFont(font);
    text.setString(text_);

    text.setPosition(sprite.getPosition());
}

std::ostream &operator<<(std::ostream &os, const Button &button_) {
    os << "Position: " << button_.sprite.getPosition().x << "," << button_.sprite.getPosition().y <<
       " Text: " << static_cast<std::string>(button_.text.getString()) << "\n";

    return os;
}

std::pair<sf::Sprite, sf::Text> Button::getButton() const {
    return std::pair<sf::Sprite, sf::Text>{sprite, text};
}

void Button::setPosition(sf::Vector2f vector) {
    sprite.setPosition(vector);
    text.setPosition(vector);
}

bool Button::clicked(sf::Event::MouseButtonEvent mouse) {
    sf::IntRect checkRect{static_cast<int>(sprite.getPosition().x),
                          static_cast<int>(sprite.getPosition().y),
                          static_cast<int>(sprite.getTexture()->getSize().x),
                          static_cast<int>(sprite.getTexture()->getSize().y)};

    return checkRect.contains(mouse.x, mouse.y);
}