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
#include "Exceptions/GraphicExceptions.hpp"

int main() {

    auto* mainWindow = new sf::RenderWindow{sf::VideoMode{800, 600}, "POO'S MUSICALY FIGHT",
                                sf::Style::Default};

    try {
        int flag;
        auto& mainMenu = MainMenu::getMainMenu(mainWindow);

        flag = mainMenu.start();


        if (flag == 1) {
            auto& game = Game::getGame(mainWindow);
            game.start();
        }
    }
    catch (TextureNotFound& err) {
        std::cout << err.what() << "\n";
        delete mainWindow;
        return 0;
    }
    catch (inexistent_path& err){
        std::cout << err.what() << "\n";
        delete mainWindow;
        return 0;
    }

    delete mainWindow;
    return 0;
}

