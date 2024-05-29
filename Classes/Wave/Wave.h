//
// Created by danai on 5/29/2024.
//

#ifndef OOP_WAVE_H
#define OOP_WAVE_H


#include <vector>
#include <unordered_map>
#include "../Enemy/Enemy.h"

class Wave {
    int currentWave;
    int maxEnmeies;

    sf::Vector2u spawnRange;

    std::unordered_map<Enemy::EnemyType,Enemy*> availableEnemies;
    std::vector<Enemy*> enemies;

public:
    friend void swap(Wave& wave, Wave& wave1){
        using std::swap;
        swap(wave.currentWave, wave1.currentWave);
        swap(wave.maxEnmeies, wave1.maxEnmeies);
        swap(wave.spawnRange, wave1.spawnRange);
        swap(wave.availableEnemies, wave1.availableEnemies);
        swap(wave.enemies, wave1.enemies);
    }

    Wave& operator=(Wave other){
        swap(*this, other);
        return *this;
    }

    Wave(const Wave& other) : currentWave(other.currentWave),
    maxEnmeies(other.maxEnmeies), spawnRange(other.spawnRange){
        for(const auto enemy : other.enemies){
            enemies.emplace_back(enemy->clone());
        }
        enemies.clear();

        for(const auto& pair : other.availableEnemies){
            availableEnemies[std::get<0>(pair)] = std::get<1>(pair)->clone();
        }
    }

    ~Wave(){
        for(const auto enemy : enemies){
            delete enemy;
        }
        enemies.clear();

        for(const auto& pair : availableEnemies){
            delete std::get<1>(pair);
        }
    }

    Wave(const int &maxEnemies_, const std::vector<Enemy*>& availableEnemies_, const sf::Vector2u& spawnRange_);
    [[nodiscard]] bool isCleared() const;
    void next(sf::Vector2f playerPosition);

    std::vector<Enemy*>& getEnemies();
    void initWave(const sf::Vector2f& playerPosition);

    void deleteEnemy(const int& index);

    int getWaveNumber() const;
private:
    static double waveFunction(double x);
    [[nodiscard]] int numberOfEnemies(int wave) const;


    std::vector<Enemy*> init_wave1();


    std::vector<Enemy *> init_wave2();

    std::vector<Enemy *> init_wave3();

    std::vector<Enemy *> init_waveDefault();
};


#endif //OOP_WAVE_H
