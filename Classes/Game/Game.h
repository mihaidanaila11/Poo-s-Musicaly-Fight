#ifndef OOP_GAME_H
#define OOP_GAME_H

#pragma once
#include "../Scene/Scene.hpp"
#include "../Player/Player.h"
#include "../Enemy/Enemy.h"
#include "../Button/Button.h"

class Game : Scene{
    Player player;
    std::vector<Enemy> enemies;
    sf::Clock attackCooldown;


    bool paused;


    sf::Sprite background;

public:
    explicit Game(sf::RenderWindow*& renderWindow, const std::vector<std::string> &image_paths, const std::string& fontPath) :
    Scene(renderWindow, image_paths, fontPath),
    player(100, Scene::getTexture("Player_SpriteSheet"), 2, Entity::RIGHT, 2.3f, 2.3f,
           0, 0, sf::Vector2f{-20.f, -10.f}, sf::Vector2f{40.f, 20.f}, Weapon::weapon_types::TRUMPET,
           Scene::getTexture("Trumpet"), 7.5f),
    attackCooldown(), paused(false){
        sf::Texture texture;
        sf::IntRect rect{0, 0, (int) Scene::getWindowSize().x,
                         (int) Scene::getWindowSize().y};

        Scene::getTexture("Grass").setRepeated(true);

        background.setTexture(Scene::getTexture("Grass"));
        background.setTextureRect(rect);
        gameProc();
    }

    friend std::ostream &operator<<(std::ostream &os, const Game &game_) {
        os << "Paused?: " << game_.paused <<  "\n";

        return os;
    }

    void start() { gameProc(); }

private:
    static sf::Vector2f normalize(const sf::Vector2f &source);

    void handleEvents(const sf::Event &handeledEvent);

    void addEnemy(float x, float y);

    void renderSprites();

    void pause();

    void gameProc();

    void end();
};


#endif //OOP_GAME_H
