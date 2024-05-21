#include <iostream>

#include <SFML/Window.hpp>
#include <cmath>

#include "Classes/Hitbox/Hitbox.h"
#include "Classes/Entity/Entity.h"
#include "Classes/Weapon/Weapon.h"
#include "Classes/Enemy/Enemy.h"
#include "Classes/Player/Player.h"
#include "Classes/Scene/Scene.h"
#include "Classes/Game/Game.h"

int main() {

    Game game{Scene{800, 600, std::vector<std::string>{
            "Textures/Weapons/Trumpet.png",
            "Textures/Dummy.png",
            "Textures/Player_SpriteSheet.png",
            "Textures/Grass.jpg"
    }}};

    game.start();

    return 0;
}

//
//socoban

