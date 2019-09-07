#include <stdio.h>
#include <cmath>
#include <iostream>
#include <string>

#include "circle.h"

using namespace std;

bool Circle::isPointInCircle(float x, float y) {
    float d = sqrt( pow((x - center_x), 2) + pow((y - center_y), 2) );

    if(d > radius) {
        return false;
    } 

    return true;
}