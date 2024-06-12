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
    friend void swap(Wave& wave, Wave& wave1);

    Wave& operator=(Wave other);

    Wave(const Wave& other);

    ~Wave();

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
