#include "draw.h"

bool Draw::thereIsCircleMoving()
{
    if (currentCircleMoving == NULL)
    {
        return false;
    }

    return true;
}

void Draw::updateCurrentCircleMoving()
{
    currentCircleMoving->updateCenter(currentCenter);
}

void Draw::drawCircle(float cx, float cy, float r, int num_segments, Color color)
{
    glColor3f(color.getR(), color.getG(), color.getB());
    glBegin(GL_LINE_LOOP);

    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments); //get the current angle

        float x = r * cosf(theta); //calculate the x component
        float y = r * sinf(theta); //calculate the y component

        glVertex2f(x + cx, y + cy); //output vertex
    }
    glEnd();
}

void Draw::drawFilledCircle(float x1, float y1, double radius, Color color)
{
    //filled circle
    float x2, y2;
    float angle;

    //x1 = 0.5,y1=0.6;
    glColor3f(color.getR(), color.getG(), color.getB());

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x1, y1);

    for (angle = 1.0f; angle < 361.0f; angle += 0.2)
    {
        x2 = x1 + sin(angle) * radius;
        y2 = y1 + cos(angle) * radius;
        glVertex2f(x2, y2);
    }

    glEnd();
}

void Draw::updateCurrentCenter(float x, float y, float x_window_size, float y_window_size)
{
    //float center_x = x / float(x_window_size);
    //float center_y = 1.0 - (y / float(y_window_size));

    float center_x = x;
    float center_y = y_window_size - y;

    currentCenter.update(center_x, center_y);
}

bool Draw::checkIntersection(Circle circle)
{
    for (circle_it = circles.begin(); circle_it != circles.end(); circle_it++)
    {
        if (circle.checkIntersection(*circle_it, num_segments))
        {
            return true;
        }
    }

    return false;
}

void Draw::drawCircle(Color color)
{
    drawCircle(currentCenter.getX(), currentCenter.getY(), radius, num_segments, color);
}

void Draw::drawFilledCircle(Color color)
{
    drawFilledCircle(currentCenter.getX(), currentCenter.getY(), radius, color);
}

void Draw::drawAllCircles(Color color)
{
    for (circle_it = circles.begin(); circle_it != circles.end(); circle_it++)
    {
        drawFilledCircle(circle_it->getCenter_x(), circle_it->getCenter_y(), circle_it->getRadius(), color);
    }
}

void Draw::chooseCircleToMove()
{
    for (circle_it = circles.begin(); circle_it != circles.end(); circle_it++)
    {
        if (circle_it->isPointInCircle(currentCenter.getX(), currentCenter.getY()))
        {
            circle_it->setMoving(true);
            currentCircleMoving = &(*circle_it);
            break;
        }
    }
}