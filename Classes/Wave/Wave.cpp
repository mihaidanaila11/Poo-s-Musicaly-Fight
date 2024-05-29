#include "Wave.h"

#include <utility>
#include <set>
#include "cmath"
#include "../Scene/Scene.hpp"


double Wave::waveFunction(double x) {
    return -(cos(3.14 * x) - 1) / 2;
}

int Wave::numberOfEnemies(int wave) const {
    double normalize_wave = std::min(static_cast<double>(wave)/10, static_cast<double>(1));

    int result = static_cast<int>(maxEnmeies * waveFunction(normalize_wave));

    if(result == 0)
        return 1;

    return result;
}



void Wave::initWave(const sf::Vector2f& playerPosition) {
    for(const auto& enemy : enemies){
        delete enemy;
    }
    enemies.clear();
    std::cout << "AICI\n";
    switch (currentWave) {
        case 1:
            enemies = init_wave1();

            for(const auto& enemy : enemies){
                enemy->setPosition(spawnRange.x, spawnRange.y);
            }

            break;

        default:
            break;
    }

    float x = rand() % (int)spawnRange.x + 1;
    float y = rand() % (int)spawnRange.y + 1;
    for(const auto& enemy : enemies){

        while(playerPosition.x == x && playerPosition.y == y){
            x = rand() % (int)spawnRange.x + 1;
            y = rand() % (int)spawnRange.y + 1;
        }

        enemy->setPosition(x,y);
    }
}

std::vector<Enemy*> Wave::init_wave1(){
    std::vector<Enemy*> result;

    for(int i=0; i < numberOfEnemies(currentWave); i++){
        result.push_back(availableEnemies[Enemy::BASIC]->clone());
    }

    return result;
}

bool Wave::isCleared() const{
    return enemies.empty();
}

void Wave::next(sf::Vector2f playerPosition) {
    //currentWave++;
    initWave(playerPosition);
}

Wave::Wave(const int &maxEnemies_, const std::vector<Enemy *>& availableEnemies_, const sf::Vector2u &spawnRange_):
currentWave(1), maxEnmeies(maxEnemies_), spawnRange(spawnRange_),
           cleared(false){
    std::cout << "constructor wave";
    for(const auto& enemy : availableEnemies_){
        availableEnemies[enemy->getType()] = enemy;
        std::cout << "X";
    }

}

std::vector<Enemy *> &Wave::getEnemies() {
    return enemies;
}

void Wave::deleteEnemy(const int &index) {
    delete enemies[index];
    enemies.erase(enemies.begin() + index);
}
