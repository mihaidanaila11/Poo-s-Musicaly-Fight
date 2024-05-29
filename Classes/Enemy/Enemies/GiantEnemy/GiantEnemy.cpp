#include "GiantEnemy.h"

GiantEnemy::GiantEnemy(sf::Texture &texture, const float &scaleX, const float &scaleY, const float &posX,
                       const float &posY, const int &health_, const float &speed_, const int &attackDamage_):
        Enemy(EnemyType::GIANT, texture, scaleX*2.f, scaleY*2.f, posX, posY, health_, speed_, attackDamage_){

}

Enemy *GiantEnemy::clone() {
    return new GiantEnemy(*this);
}

void GiantEnemy::attack(Alive &target) {
    if(hitbox.intersects(target.getHitbox())){
        target.damage(attackDamage);
    }
}
