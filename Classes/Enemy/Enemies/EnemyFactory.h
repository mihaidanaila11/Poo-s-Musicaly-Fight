#ifndef OOP_ENEMYFACTORY_H
#define OOP_ENEMYFACTORY_H


#include "../Enemy.h"

class EnemyFactory {

    static Enemy* basicEnemy();
    static Enemy* ghostEnemy();
    static Enemy* giantEnemy();
public:
    static Enemy* buildEnemy(Enemy::EnemyType enemyType);
    static std::vector<Enemy*> getAvailableEnemies();
};


#endif //OOP_ENEMYFACTORY_H
