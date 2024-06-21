#include "Wave.h"

#include "cmath"
#include "../Scene/Scene.hpp"
#include "../../Math/VectorMath.h"
#include "../Enemy/Enemies/EnemyFactory.h"

double Wave::waveFunction(double x) {
    //return -(cos(3.14 * x) - 1) / 2;
    return x*x;
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
    switch (currentWave) {
        case 0:
            enemies.push_back(availableEnemies[Enemy::GIANT]->clone());
            enemies[0]->setPosition(spawnRange.x/2, spawnRange.y/2);
            break;

        case 1:
            enemies = init_wave1();
            for(const auto& enemy : enemies){
                enemy->setPosition(spawnRange.x, spawnRange.y);
            }

            break;

        case 2:
            enemies = init_wave2();
            for(const auto& enemy : enemies){
                float x = rand() % spawnRange.x + 1;
                float y = rand() % spawnRange.y + 1;

                while(VectorMath::vectorDistance(playerPosition, sf::Vector2f{x,y}) < 50){
                    x = rand() % spawnRange.x + 1;
                    y = rand() % spawnRange.y + 1;
                }
                enemy->setPosition(x, y);
            }

            break;

        case 3:
            enemies = init_wave3();
            for(const auto& enemy : enemies){
                float x = rand() % spawnRange.x + 1;
                float y = rand() % spawnRange.y + 1;

                while(VectorMath::vectorDistance(playerPosition, sf::Vector2f{x,y}) < 50){
                    x = rand() % spawnRange.x + 1;
                    y = rand() % spawnRange.y + 1;
                }
                enemy->setPosition(x, y);
            }

            break;
        default:
            enemies = init_waveDefault();
            for(const auto& enemy : enemies){
                float x = rand() % spawnRange.x + 1;
                float y = rand() % spawnRange.y + 1;

                while(VectorMath::vectorDistance(playerPosition, sf::Vector2f{x,y}) < 300){
                    x = rand() % spawnRange.x + 1;
                    y = rand() % spawnRange.y + 1;
                }
                enemy->setPosition(x, y);
            }
            break;
    }



}



bool Wave::isCleared() const{
    return enemies.empty();
}

void Wave::next(sf::Vector2f playerPosition) {
    currentWave++;
    initWave(playerPosition);
}

Wave::Wave(const int &maxEnemies_, const sf::Vector2u &spawnRange_):
currentWave(0), maxEnmeies(maxEnemies_), spawnRange(spawnRange_){
    std::cout << "constructor wave";
    for(int i=0; i < Enemy::ENUM_END; i++){
        auto enemyType = static_cast<Enemy::EnemyType>(i);
        availableEnemies[enemyType] = EnemyFactory::buildEnemy(enemyType);
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
int Wave::getWaveNumber() const{
    return currentWave;
}

void swap(Wave &wave, Wave &wave1) {
    using std::swap;
    swap(wave.currentWave, wave1.currentWave);
    swap(wave.maxEnmeies, wave1.maxEnmeies);
    swap(wave.spawnRange, wave1.spawnRange);
    swap(wave.availableEnemies, wave1.availableEnemies);
    swap(wave.enemies, wave1.enemies);
}

Wave &Wave::operator=(Wave other) {
    swap(*this, other);
    return *this;
}

Wave::Wave(const Wave &other) : currentWave(other.currentWave),
                                maxEnmeies(other.maxEnmeies), spawnRange(other.spawnRange){
    for(const auto enemy : other.enemies){
        enemies.emplace_back(enemy->clone());
    }

    for(const auto& pair : other.availableEnemies){
        availableEnemies[std::get<0>(pair)] = std::get<1>(pair)->clone();
    }
}

Wave::~Wave(){
    for(const auto enemy : enemies){
        delete enemy;
    }

    for(const auto& pair : availableEnemies){
        delete std::get<1>(pair);
    }
}
