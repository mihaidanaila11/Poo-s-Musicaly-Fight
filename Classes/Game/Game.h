#ifndef OOP_GAME_H
#define OOP_GAME_H

#pragma once
#include "../Scene/Scene.h"
#include "../Player/Player.h"
#include "../Enemy/Enemy.h"
#include "../Button/Button.h"

class Game {
    Scene scene;
    Player player;
    std::vector<Enemy> enemies;
    sf::Clock attackCooldown;


    bool paused;


    sf::Sprite background;

public:
    explicit Game(const Scene &scene_) : scene(scene_),
                                         player(100, scene.getTexture("Player_SpriteSheet"), 2, Entity::RIGHT, 2.3f, 2.3f,
                                                0, 0, sf::Vector2f{-20.f, -10.f}, sf::Vector2f{40.f, 20.f}, Weapon::weapon_types::TRUMPET,
                                                scene.getTexture("Trumpet"), 7.5f),
                                         attackCooldown(), paused(false){
        sf::Texture texture;
        sf::IntRect rect{0, 0, (int) scene.getWindowSize().x, (int) scene.getWindowSize().y};

        scene.getTexture("Grass").setRepeated(true);

        background.setTexture(scene.getTexture("Grass"));
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

    void handleEvents(const sf::Event &event);

    void addEnemy(float x, float y);

    void renderSprites();

    void pause();

    void gameProc();

    void end();
};


#endif //OOP_GAME_H
