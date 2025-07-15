#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "Score.h"


    Score::Score() = default;
    Score::Score(const sf::Font &font, const int& scoreCount) : scoreCount(scoreCount), font(font) {
        scoreText = sf::Text("Score: " + std::to_string(scoreCount), font);
        scoreText.setCharacterSize(30);
    }

    sf::Text Score::getScoreText() const { return scoreText; }

    void Score::increase() {
        scoreCount++;
        updateScoreText();
    };

    void Score::setPosition(const sf::Vector2f position) {
        scoreText.setPosition(position);
    }

    sf::FloatRect Score::getGlobalBounds() const {
        return scoreText.getGlobalBounds();
    }


    void Score::updateScoreText() {
        sf::Text newScoreText = sf::Text("Score: " + std::to_string(scoreCount), font);
        newScoreText.setCharacterSize(30);
        newScoreText.setPosition(scoreText.getPosition());

        scoreText = newScoreText;
    }






