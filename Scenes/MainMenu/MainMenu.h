#ifndef OOP_MAINMENU_H
#define OOP_MAINMENU_H

#pragma once

#include "../../Classes/Scene/Scene.hpp"
#include "../../Classes/Button/Button.h"

class MainMenu : Scene{
    sf::Sprite background;
    Button play;
    Button quit;

    int returnFlag;

    MainMenu(sf::RenderWindow* renderWindow, const std::vector<std::string> &image_paths, const std::string& fontPath);
public:
    MainMenu(const MainMenu&) = delete;
    MainMenu& operator=(const MainMenu&) = delete;

    static MainMenu& getMainMenu(sf::RenderWindow* renderWindow);

    int start();

    void handleEvents() override;
};



#endif //OOP_MAINMENU_H
