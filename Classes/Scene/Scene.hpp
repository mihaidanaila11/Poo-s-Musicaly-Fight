#ifndef OOP_SCENE_HPP
#define OOP_SCENE_HPP

#pragma once
#include "SFML/Graphics.hpp"
#include "unordered_map"
#include "iostream"

const std::string GAME_TITLE = "Poo's Musicaly Fight";

class Scene {

    sf::RenderWindow* window;
    sf::Event event;

    std::unordered_map<std::string, sf::Texture> textures;
    sf::Font font;


public:
    Scene(sf::RenderWindow*& renderWindow, const std::vector<std::string> &image_paths, const std::string& fontPath);

    Scene& operator=(const Scene& other);

    virtual ~Scene();

    Scene(const Scene &other);

    friend std::ostream &operator<<(std::ostream &os, const Scene &scene_);

    sf::Texture& getTexture(const std::string& key);
    const sf::Font& getFont() const;

    sf::Event getEvent() const;

    bool isOpen();

    void clear();

    template<typename T>
    void draw(const T &sprite) { window->draw(sprite); }

    void display();

    void close();

    bool pollEvent();

    sf::Event &getEvent();

    sf::Vector2u getWindowSize() const;

    virtual void handleEvents() = 0;
};


#endif //OOP_SCENE_HPP
