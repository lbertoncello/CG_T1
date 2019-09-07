class Circle {
    private:
        float center_x;
        float center_y;
        float radius;
        bool moving;

    public:
        Circle(float center_x, float center_y, float radius) {
            this->center_x = center_x;
            this->center_y = center_y;
            this->radius = radius;
        }

        float getCenter_x() {
            return center_x;
        }

        float getCenter_y() {
            return center_y;
        }

        float getRadius(){
            return radius;           
        }

        bool isMoving() {
            return moving;
        }

        void setCenter_x(float center_x) {
            this->center_x = center_x;
        }

        void setCenter_y(float center_y) {
            this->center_y = center_y;
        }

        void setRadius(float radius) {
            this->radius = radius;
        }

        void setMoving(bool moving) {
            this->moving = moving;
        }

        bool isPointInCircle(float x, float y);
};