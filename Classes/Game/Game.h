#ifndef OOP_GAME_H
#define OOP_GAME_H

#pragma once
#include "../Scene/Scene.hpp"
#include "../Player/Player.h"
#include "../Enemy/Enemy.h"
#include "../Button/Button.h"
#include "../Hud/Hud.h"

class Game : Scene{
    Player player;
    std::vector<Enemy*> enemies;
    sf::Clock attackCooldown;

    Hud hud;
    bool paused;


    sf::Sprite background;

public:
    ~Game();
    Game(const Game& other);
    Game& operator=(Game& other);


    Game(sf::RenderWindow*& renderWindow, const std::vector<std::string> &image_paths, const std::string& fontPath);

    friend std::ostream &operator<<(std::ostream &os, const Game &game_);

    void start() { gameProc(); }

private:
    friend void swap(Game& game1, Game& game2);

    static sf::Vector2f normalize(const sf::Vector2f &source);

    void handleEvents() override;

    void addEnemy(float x, float y);

    void renderSprites();

    void renderHud();

    void pause();

    void gameProc();

    void end();

    static float vectorDistance(sf::Vector2f vector1, sf::Vector2f vector2);
};


#endif //OOP_GAME_H
