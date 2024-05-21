#ifndef OOP_MAINMENU_H
#define OOP_MAINMENU_H

#pragma once

#include "../../Classes/Scene/Scene.hpp"

class MainMenu : Scene{
    sf::Sprite background;

public:
    MainMenu(sf::RenderWindow*& renderWindow, const std::vector<std::string> &image_paths, const std::string& fontPath);

    int start();
};



#endif //OOP_MAINMENU_H
