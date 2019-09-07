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

/* 
glutPostRedisplay();

glutKeyboardUpFunc(keyup);

void idle(void)

glutIdleFunc(idle);

void mouse(int button, int state, int x, int y)

glutMouseFunc(mouse);

glutmotionfunc
*/

const float PI = 3.14159;

int x_window_size = 250;
int y_windows_size = 250;
int x_windows_initial_position = 100;
int y_windows_initial_position = 100;

Point currentCenter;
int num_segments = 100;

float radius = 0.1;
Color defaultColor(0.5,1.0,0.6);
Color overlapColor(1.0,1.0,0.6);

bool isLeftMouseButtonPressed = false;
bool isRightMouseButtonPressed = false;

vector<Circle> circles;
vector<Circle>::iterator circle_it;
Circle* currentCircleMoving = NULL;

void updateCurrentCenter(float x, float y) {
    float center_x = x / float(x_window_size);
    float center_y = 1.0 - (y / float(y_windows_size));

    currentCenter.update(center_x, center_y);
}

bool checkIntersection(Circle circle) {
    for(circle_it = circles.begin(); circle_it != circles.end(); circle_it++) {
        if(circle.checkIntersection(*circle_it, num_segments)) {
            return true;
        }
    }

    return false;
}

void drawCircle(float cx, float cy, float r, int num_segments, Color color) 
{ 
    glColor3f(color.getR(), color.getG(), color.getB());
	glBegin(GL_LINE_LOOP); 
	for(int ii = 0; ii < num_segments; ii++) 
	{ 
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 

		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 

		glVertex2f(x + cx, y + cy);//output vertex 

	} 
	glEnd(); 
}

void drawFilledCircle(float x1, float y1, double radius, Color color) {
    //filled circle
    float x2,y2;
    float angle;

    //x1 = 0.5,y1=0.6;
    glColor3f(color.getR(), color.getG(), color.getB());

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x1,y1);

    for (angle=1.0f;angle<361.0f;angle+=0.2)
    {
        x2 = x1+sin(angle)*radius;
        y2 = y1+cos(angle)*radius;
        glVertex2f(x2,y2);
    }

    glEnd();
}

void display (void) {
     /* Limpar todos os pixels */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Desenhar um polígono branco (retângulo) */
    glColor3f(1.0, 1.0, 1.0);

   if(currentCircleMoving == NULL) {
       Circle circle(currentCenter, radius);

       if(checkIntersection(circle)) {
            drawCircle(currentCenter.getX(), currentCenter.getY(), radius, num_segments, overlapColor);
       } else {
            drawCircle(currentCenter.getX(), currentCenter.getY(), radius, num_segments, defaultColor);
       }
   } else {
       currentCircleMoving->updateCenter(currentCenter);
   }

    for(circle_it = circles.begin(); circle_it != circles.end(); circle_it++)    {
        drawFilledCircle(circle_it->getCenter_x(), circle_it->getCenter_y(), circle_it->getRadius(), defaultColor);
    }

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
            updateCurrentCenter(x, y);

            Circle circle(currentCenter.getX(), currentCenter.getY(), radius);

            if(checkIntersection(circle) == false) {
                circles.push_back(circle);
            }
            
            //puts(std::to_string(x_origin).c_str());
            //puts(std::to_string(y_origin).c_str());
        } else {
            isLeftMouseButtonPressed = true;
        }
    }

    if(button == GLUT_RIGHT_BUTTON) {
        if(state == GLUT_UP) {
            isRightMouseButtonPressed = false;
            currentCircleMoving = NULL;
            //puts(std::to_string(x_origin).c_str());
            //puts(std::to_string(y_origin).c_str());
        } else {
            for(circle_it = circles.begin(); circle_it != circles.end(); circle_it++)    {
                if(circle_it->isPointInCircle(currentCenter.getX(), currentCenter.getY())) {
                    circle_it->setMoving(true);
                    currentCircleMoving = &(*circle_it);
                    break;
                }
            }

            isRightMouseButtonPressed = true;
        }
    }
}

void motion(int x, int y) {
    if(isLeftMouseButtonPressed) {
        updateCurrentCenter(x, y);
    }

    if(isRightMouseButtonPressed) {
        updateCurrentCenter(x, y);
    }
}

void passiveMotion(int x, int y) {
    updateCurrentCenter(x, y);
    Circle circle(currentCenter.getX(), currentCenter.getY(), radius);
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
    glutInitWindowSize(x_window_size, y_windows_size);
    glutInitWindowPosition(x_windows_initial_position, y_windows_initial_position);
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

//PRÓXIMO PASSO: DESENHAR O QUADRADO ONDE O USUÁRIO CLICAR