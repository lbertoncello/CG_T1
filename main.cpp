#include <stdlib.h>
#include <stdio.h> 
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#include "draw.h"

using namespace std;

int x_window_size = 250;
int y_window_size = 250;
int x_window_initial_position = 100;
int y_window_initial_position = 100;

Color defaultColor(0.5,1.0,0.6);
Color overlapColor(1.0,1.0,0.6);

bool isLeftMouseButtonPressed = false;
bool isRightMouseButtonPressed = false;

Draw draw;

void display (void) {
     /* Limpar todos os pixels */
    glClear(GL_COLOR_BUFFER_BIT);

   if(draw.thereIsCircleMoving() == false) {
       Circle circle(draw.getCurrentCenter(), draw.getRadius());

       if(draw.checkIntersection(circle)) {
            draw.drawCircle(overlapColor);
       } else {
            draw.drawCircle(defaultColor);
       }
   } else {
       draw.updateCurrentCircleMoving();
   }

    draw.drawAllCircles(defaultColor);

    /* Não esperar */
    glFlush();
}

void idle(void) {
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON) {
        if(state == GLUT_UP) {
            isLeftMouseButtonPressed = false;
            draw.updateCurrentCenter(x, y, x_window_size, y_window_size);

            Circle circle(draw.getCurrentCenter().getX(), draw.getCurrentCenter().getY(), draw.getRadius());

            if(draw.checkIntersection(circle) == false) {
                draw.addCircle(circle);
            }
        } else {
            isLeftMouseButtonPressed = true;
        }
    }

    if(button == GLUT_RIGHT_BUTTON) {
        if(state == GLUT_UP) {
            isRightMouseButtonPressed = false;
            draw.setCurrentCircleMoving(NULL);
        } else {
            draw.chooseCircleToMove();

            isRightMouseButtonPressed = true;
        }
    }
}

void motion(int x, int y) {
    if(isLeftMouseButtonPressed) {
        draw.updateCurrentCenter(x, y, x_window_size, y_window_size);
    }

    if(isRightMouseButtonPressed) {
        draw.updateCurrentCenter(x, y, x_window_size, y_window_size);
    }
}

void passiveMotion(int x, int y) {
    draw.updateCurrentCenter(x, y, x_window_size, y_window_size);
}

void init(void) 
{
    /* selecionar cor de fundo (preto) */
    glClearColor(0.0, 0.0, 0.0, 0.0);

    /* Inicializa sistema de viz */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(x_window_size, y_window_size);
    glutInitWindowPosition(x_window_initial_position, y_window_initial_position);
    glutCreateWindow("Hello");
    init();
    glutDisplayFunc(display);

    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutPassiveMotionFunc(passiveMotion);

    glutIdleFunc(idle);
    glutMainLoop();

    return 0;
}