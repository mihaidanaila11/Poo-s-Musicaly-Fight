#include "GhostEnemy.h"

bool GhostEnemy::ghosted = false;
float GhostEnemy::ghostDuration = 3.f;

void GhostEnemy::move(sf::Vector2f vector) {
    if (ghostClock.getElapsedTime().asSeconds() < ghostDuration){
        Entity::setOpacity(225);
        ghosted = false;

    }
    else if(ghostClock.getElapsedTime().asSeconds() > ghostDuration && ghostClock.getElapsedTime().asSeconds() < 2 * ghostDuration){
        Entity::setOpacity(0);

        ghosted = true;
    }
    else{
        ghostClock.restart();
    }

    sprite.move(vector);
    hitbox.move(vector);
}

Enemy *GhostEnemy::clone() {
    return new GhostEnemy(*this);
}

void GhostEnemy::attack(Alive &target) {
    if(ghosted)
        return;

    if(hitbox.intersects(target.getHitbox())){
        target.damage(attackDamage);
    }
}

GhostEnemy::GhostEnemy(sf::Texture &texture, const float &scaleX, const float &scaleY, const float &posX,
                       const float &posY, const int &health_, const float &speed_, const int &attackDamage_):
        Enemy(EnemyType::GHOST, texture, scaleX, scaleY, posX, posY, health_, speed_, attackDamage_){

}
