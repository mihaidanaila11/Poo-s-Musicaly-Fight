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
