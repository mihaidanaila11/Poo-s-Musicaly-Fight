//
// Created by danai on 5/29/2024.
//

#include "Alert.h"

#include <utility>

Alert::Alert(const std::string& message_, const sf::Texture &texture, const sf::Font& font, const sf::Vector2u& windowSize){
    frame.setTexture(texture);

    message = sf::Text(message_, font, 60);

    frame.setPosition((float)windowSize.x/2 - frame.getGlobalBounds().width /2,
                      -frame.getGlobalBounds().height);

    message.setPosition(frame.getPosition().x + frame.getGlobalBounds().width/2 - message.getGlobalBounds().width/2,
                        frame.getPosition().y + frame.getGlobalBounds().height/2 - message.getGlobalBounds().height/2);


}

sf::Vector2f Alert::getPosition() const {
    return frame.getPosition();
}

void Alert::move(sf::Vector2f vector) {
    frame.move(vector);
    message.move(vector);
}

sf::Sprite Alert::getSprite() const {
    return frame;
}
sf::Text Alert::getText() const{
    return message;
};

