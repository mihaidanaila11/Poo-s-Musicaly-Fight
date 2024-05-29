#ifndef OOP_SCENE_HPP
#define OOP_SCENE_HPP

#pragma once
#include "SFML/Graphics.hpp"
#include "unordered_map"
#include "iostream"
#include "../Alert/Alert.h"
#include "../Button/Button.h"

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

    template<typename T>
    static bool isInVector(const std::vector<T>& vector, const T& object){
        for(const auto& item : vector){
            if(item == object)
                return true;
        }

        return false;
    }
    static bool exists(const std::string& path);
    static bool isImageSupported(const std::string& path);

    sf::Texture& getTexture(const std::string& key);
    const sf::Font& getFont() const;

    bool isOpen();

    void clear();

    template<typename T>
    void draw(const T &sprite) { window->draw(sprite); }

    void draw(const Alert &alert) { window->draw(alert.getSprite());
    window->draw(alert.getText());}

    void draw(const Button &button) { window->draw(button.getSprite());
        window->draw(button.getText());}

    void display();

    void close();

    bool pollEvent();

    sf::Event &getEvent();

    sf::Vector2u getWindowSize() const;

    virtual void handleEvents() = 0;
};


#endif //OOP_SCENE_HPP
