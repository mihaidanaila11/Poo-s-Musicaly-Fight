//
// Created by danai on 5/29/2024.
//
#include "Wave.h"

std::vector<Enemy*> Wave::init_wave1(){
    std::vector<Enemy*> result{};

    for(int i=0; i < numberOfEnemies(currentWave); i++){
        result.push_back(availableEnemies[Enemy::BASIC]->clone());
    }

    return result;
}

std::vector<Enemy*> Wave::init_wave2(){
    std::vector<Enemy*> result;

    for(int i=0; i < numberOfEnemies(currentWave); i++){
        result.push_back(availableEnemies[Enemy::BASIC]->clone());
    }

    return result;
}

std::vector<Enemy*> Wave::init_wave3(){
    std::vector<Enemy*> result;

    int enemyNumber = numberOfEnemies(currentWave);


    for(int i=0; i<enemyNumber/2; i++){
        result.push_back(availableEnemies[Enemy::BASIC]->clone());
    }

    int remaining = enemyNumber - result.size();
    std::cout << "current: " << remaining << result.size();

    for(int i=0; i< remaining; i++){
        result.push_back(availableEnemies[Enemy::GHOST]->clone());
    }

    return result;
}

std::vector<Enemy*> Wave::init_waveDefault(){
    std::vector<Enemy*> result;

    int enemyNumber = numberOfEnemies(currentWave);

    for(int i=0; i<enemyNumber * (2.0/3.0); i++){
        result.push_back(availableEnemies[Enemy::BASIC]->clone());
    }

    int remaining = enemyNumber - result.size();


    for(int i=0; i< remaining; i++){
        result.push_back(availableEnemies[Enemy::GHOST]->clone());
    }

    return result;
}