//
// Created by danai on 7/15/2025.
//

#ifndef SCORE_H
#define SCORE_H
#pragma once
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Text.hpp"

class Score {
    sf::Text scoreText;
    int scoreCount;
    sf::Font font;
public:
    Score();
    explicit Score(const sf::Font &font, const int& scoreCount);

    sf::Text getScoreText() const;

    void increase();

    void setPosition(const sf::Vector2f position);

    sf::FloatRect getGlobalBounds() const;

private:
    void updateScoreText();
};

#endif //SCORE_H
