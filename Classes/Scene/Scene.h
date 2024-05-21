#ifndef OOP_SCENE_H
#define OOP_SCENE_H

#pragma once
#include "SFML/Graphics.hpp"
#include "unordered_map"
#include "iostream"

const std::string GAME_TITLE = "Poo's Musicaly Fight";

class Scene {
    sf::RenderWindow window;
    sf::Event event;

    std::unordered_map<std::string, sf::Texture> textures;

public:
    Scene(unsigned int windowWidth, unsigned int windowHeight, const std::vector<std::string> &image_paths);

    Scene& operator=(const Scene& other);

    ~Scene();

    Scene(const Scene &other);

    friend std::ostream &operator<<(std::ostream &os, const Scene &scene_);

    sf::Texture& getTexture(std::string key);

    sf::Event getEvent() const;

    bool isOpen();

    void clear();

    template<typename T>
    void draw(const T &sprite) { window.draw(sprite); }

    void display();

    void close();

    bool pollEvent();

    sf::Event &getEvent();

    sf::Vector2u getWindowSize() const;


};


#endif //OOP_SCENE_H
