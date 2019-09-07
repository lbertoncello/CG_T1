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

bool Circle::checkIntersection(Circle circle, int num_segments) {
	for(int ii = 0; ii < num_segments; ii++) 
	{ 
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 

		float x = circle.getRadius() * cosf(theta) + circle.getCenter_x();//calculate the x component 
		float y = circle.getRadius() * sinf(theta) + circle.getCenter_y();//calculate the y component 

		if(isPointInCircle(x, y)) {
            return true;
        }
	} 

    return false;
}