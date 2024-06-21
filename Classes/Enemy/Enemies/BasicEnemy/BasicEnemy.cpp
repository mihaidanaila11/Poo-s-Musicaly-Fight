#include "BasicEnemy.h"

void BasicEnemy::attack(Alive& target) {
    if(!hitbox.intersects(target.getHitbox()))
        return;

    target.damage(attackDamage);
}

Enemy* BasicEnemy::clone() {
    std::cout << "Clonez inamic\n";
    return new BasicEnemy(*this);
}

BasicEnemy::BasicEnemy(const std::string& textureKey, const float &scaleX, const float &scaleY,
                       const float &posX, const float &posY, const int &health_, const float &speed_, const int& attackDamage_):
        Enemy(textureKey, scaleX, scaleY, posX, posY, health_, speed_, attackDamage_){

}
