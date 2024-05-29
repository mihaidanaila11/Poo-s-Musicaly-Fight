#ifndef OOP_GAME_H
#define OOP_GAME_H

#pragma once
#include "../Scene/Scene.hpp"
#include "../Player/Player.h"
#include "../Enemy/Enemy.h"
#include "../Button/Button.h"
#include "../Hud/Hud.h"
#include "../Wave/Wave.h"

class Game : Scene{
    static sf::Clock deltaTime;
    Player player;
    Wave wave;
    sf::Clock attackCooldown;

    Hud hud;
    bool paused;


    sf::Sprite background;

public:

    Game(sf::RenderWindow*& renderWindow, const std::vector<std::string> &image_paths, const std::string& fontPath);

    friend std::ostream &operator<<(std::ostream &os, const Game &game_);

    void start() { gameProc(); }

private:

    static sf::Vector2f normalize(const sf::Vector2f &source);

    void handleEvents() override;

    void renderSprites();

    void renderHud();

    void pause();

    void gameProc();

    void end();

    void alertHandleEvents();
    void wait(float secounds);

    void nextWave();

    void renderAlert(const std::string& message);
};


#endif //OOP_GAME_H
