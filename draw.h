#include <stdlib.h>
#include <stdio.h> 
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#include "circle.h"
#include "color.h"

using namespace std;

class Draw {
    private:
        const float PI = 3.14159;
        int num_segments = 100;
        float radius = 0.1;

        Point currentCenter;
        vector<Circle> circles;
        vector<Circle>::iterator circle_it;
        Circle* currentCircleMoving = NULL;

        void drawCircle(float cx, float cy, float r, int num_segments, Color color);
        void drawFilledCircle(float x1, float y1, double radius, Color color);

    public:
        Draw() {}

        float getRadius() {
            return radius;
        }

        Point& getCurrentCenter() {
            return currentCenter;
        }

        Circle* getCurrentCircleMoving() {
            currentCircleMoving;
        }

        void setRadius(float radius) {
            this->radius = radius;
        }

        void setCurrentCircleMoving(Circle* circle) {
            this->currentCircleMoving = circle;
        }

        void addCircle(Circle circle) {
            circles.push_back(circle);
        }

        void addCircleAtCurrentCenter();
        bool thereIsCircleMoving();
        void updateCurrentCircleMoving();
        void updateCurrentCenter(float x, float y, float x_window_size, float y_window_size);
        bool checkIntersection(Circle circle);
        void drawCircle(Color color);
        void drawFilledCircle(Color color);
        void drawAllCircles(Color color);
        void chooseCircleToMove();
};