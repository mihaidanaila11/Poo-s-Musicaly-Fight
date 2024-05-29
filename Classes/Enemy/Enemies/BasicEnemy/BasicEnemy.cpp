//
// Created by danai on 5/28/2024.
//

#include "BasicEnemy.h"

void BasicEnemy::attack(Alive& target) {
    if(!hitbox.intersects(target.getHitbox()))
        return;

    target.damage(attackDamage);
}

Enemy* BasicEnemy::clone() {
    return new BasicEnemy(*this);
}

BasicEnemy::BasicEnemy(sf::Texture& texture, const float &scaleX, const float &scaleY,
                       const float &posX, const float &posY, const int &health_, const float &speed_, const int& attackDamage_):
        Enemy(EnemyType::BASIC, texture, scaleX, scaleY, posX, posY, health_, speed_, attackDamage_){

}
