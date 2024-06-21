#include "EnemyFactory.h"
#include "BasicEnemy/BasicEnemy.h"
#include "GhostEnemy/GhostEnemy.h"
#include "GiantEnemy/GiantEnemy.h"

Enemy *EnemyFactory::basicEnemy() {
    return BasicEnemy{"Dummy",
                      2.3f, 2.3f,
                      0, 0,
                      50,
                      2.f,
                      5}.clone();
}

Enemy *EnemyFactory::ghostEnemy() {
    return GhostEnemy{"Ghost",
                      2.3f, 2.3f,
                      0, 0,
                      50,
                      0.5f,
                      10}.clone();
}

Enemy *EnemyFactory::giantEnemy() {
    return GiantEnemy{"Dummy",
                      2.3f, 2.3f,
                      0, 0,
                      150,
                      0.5f,
                      25}.clone();
}

Enemy *EnemyFactory::buildEnemy(Enemy::EnemyType enemyType) {
    switch (enemyType) {

        case Enemy::BASIC:
            return basicEnemy();

        case Enemy::GHOST:
            return ghostEnemy();

        case Enemy::GIANT:
            return giantEnemy();

        default:
            throw std::runtime_error("Invalid type");
    }
}