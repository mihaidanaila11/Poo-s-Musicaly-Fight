#include <iostream>

#include <SFML/Window.hpp>
#include <cmath>

#include "Classes/Hitbox/Hitbox.h"
#include "Classes/Entity/Entity.h"
#include "Classes/Weapon/Weapon.h"
#include "Classes/Enemy/Enemy.h"
#include "Classes/Player/Player.h"
#include "Classes/Scene/Scene.hpp"
#include "Classes/Game/Game.h"

#include "Scenes/MainMenu/MainMenu.h"
int main() {

    auto* mainWindow = new sf::RenderWindow{sf::VideoMode{800, 600}, "POO'S MUSICALY FIGHT",
                                sf::Style::Default};

    int flag;
    {
        MainMenu mainMenu{mainWindow, std::vector<std::string>{
                "Textures/Grass_blured.png",
                "Textures/Buton.png"
        }, "daydream_3/Daydream.ttf"};

        flag = mainMenu.start();
    }


    if(flag == 1){
        Game game{mainWindow, std::vector<std::string>{
                "Textures/Weapons/Trumpet.png",
                "Textures/Dummy.png",
                "Textures/Player_SpriteSheet.png",
                "Textures/Grass.jpg",
                "Textures/Buton.png"
        }, "daydream_3/Daydream.ttf"};
        game.start();
    }



    return 0;
}

//
//socoban

