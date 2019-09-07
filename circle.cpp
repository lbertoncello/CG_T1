#include <cmath>

#include "circle.h"

bool Circle::isPointInCircle(float x, float y) {
    int d = sqrt( pow((x - center_x), 2) - pow((x - center_y), 2));

    if(d > radius) {
        false;
    } 

    return true;
}