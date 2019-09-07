#include "point.h"

class Circle {
    private:
        Point center;
        float radius;
        bool moving = false;

    public:
        Circle(Point center, float radius) {
            this->center = center;
            this->radius = radius;
        }

        Circle(float center_x, float center_y, float radius) {
            this->center.setX(center_x);
            this->center.setY(center_y);
            this->radius = radius;
        }

        float getCenter_x() {
            return center.getX();
        }

        float getCenter_y() {
            return center.getY();
        }

        float getRadius(){
            return radius;           
        }

        bool isMoving() {
            return moving;
        }

        void setCenter_x(float center_x) {
            this->center.setX(center_x);
        }

        void setCenter_y(float center_y) {
            this->center.setY(center_y);
        }

        void setRadius(float radius) {
            this->radius = radius;
        }

        void setMoving(bool moving) {
            this->moving = moving;
        }

        void updateCenter(Point p) {
            this->center.setX(p.getX());
            this->center.setY(p.getY());
        }

        void updateCenter(float x, float y) {
            this->center.setX(x);
            this->center.setY(y);
        }

        bool isPointInCircle(Point p);
        bool isPointInCircle(float x, float y);
        bool checkIntersection(Circle circle, int num_segments);
};