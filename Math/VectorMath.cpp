#include "VectorMath.h"
#include <cmath>

float VectorMath::vectorDistance(sf::Vector2f vector1, sf::Vector2f vector2) {
    return sqrtf((vector1.x-vector2.x)*(vector1.x-vector2.x) + (vector1.y-vector2.y)*(vector1.y-vector2.y));
}