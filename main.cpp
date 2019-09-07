#include <stdlib.h>
#include <stdio.h> 
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#include "circle.h"

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

float offset_value = 0.01;
float x_offset = 0;
float y_offset = 0;
float x_origin = 0.5;
float y_origin = 0.5;
float radius = 0.1;

bool* keyStates = new bool[256];
bool isLeftMouseButtonPressed = false;
bool isRightMouseButtonPressed = false;

vector<Circle> circles;
vector<Circle>::iterator circle_it;
Circle* currentCircleMoving = NULL;

void keyOperations (void) {  
    if (keyStates['w']) { // If the 'a' key has been pressed  
        y_offset += offset_value;
    }  
    if(keyStates['a']) {
        x_offset -= offset_value;
    }
    if(keyStates['s']) {
        y_offset -= offset_value;
    }
    if(keyStates['d']) {
        x_offset += offset_value;
    }
} 

void keyPress(unsigned char key, int x, int y) {
    if(key == 'w') {
        keyStates[key] = true;
        //glutPostRedisplay();
    }
    if(key == 'a') {
        keyStates[key] = true;
        //glutPostRedisplay();
    }
    if(key == 's') {
        keyStates[key] = true;
        //glutPostRedisplay();
    }
    if(key == 'd') {
        keyStates[key] = true;
        //glutPostRedisplay();
    }
}

void keyUp (unsigned char key, int x, int y) {  
    keyStates[key] = false; // Set the state of the current key to not pressed  
}  

void drawCircle(float cx, float cy, float r, int num_segments) 
{ 
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

void drawFilledCircle(float x1, float y1, double radius) {
    //filled circle
    float x2,y2;
    float angle;

    //x1 = 0.5,y1=0.6;
    glColor3f(1.0,1.0,0.6);

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
    keyOperations();
     /* Limpar todos os pixels */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Desenhar um polígono branco (retângulo) */
    glColor3f(1.0, 1.0, 1.0);

    /*
    glBegin(GL_POLYGON);
        glVertex3f(x_origin - 0.25 + x_offset, y_origin - 0.25 + y_offset, 0.0);
        glVertex3f(x_origin + 0.25 + x_offset, y_origin - 0.25 + y_offset, 0.0);
        glVertex3f(x_origin + 0.25 + x_offset, y_origin + 0.25 + y_offset, 0.0);
        glVertevector<Circle>::iterator circle_itx3f(x_origin - 0.25 + x_offset, y_origin + 0.25 + y_offset, 0.0);
    glEnd();
    */

   if(currentCircleMoving == NULL) {
        drawCircle(x_origin, y_origin, radius, 100);
   } else {
        currentCircleMoving->setCenter_x(x_origin);
        currentCircleMoving->setCenter_y(y_origin);
   }

    for(circle_it = circles.begin(); circle_it != circles.end(); circle_it++)    {
        drawFilledCircle(circle_it->getCenter_x(), circle_it->getCenter_y(), circle_it->getRadius());
    }
    //drawFilledCircle(x_origin, y_origin, radius);

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
            x_origin = x / float(x_window_size);
            y_origin = 1.0 - (y / float(y_windows_size));

            Circle circle(x_origin, y_origin, radius);
            circles.push_back(circle);
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
                if(circle_it->isPointInCircle(x_origin, y_origin)) {
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
        x_origin = x / float(x_window_size);
        y_origin = 1.0 - (y / float(y_windows_size));
    }

    if(isRightMouseButtonPressed) {
        x_origin = x / float(x_window_size);
        y_origin = 1.0 - (y / float(y_windows_size));
    }
}

void passiveMotion(int x, int y) {
    x_origin = x / float(x_window_size);
    y_origin = 1.0 - (y / float(y_windows_size));
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

    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyUp); 
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutPassiveMotionFunc(passiveMotion);

    glutIdleFunc(idle);
    glutMainLoop();

    return 0;
}

//PRÓXIMO PASSO: DESENHAR O QUADRADO ONDE O USUÁRIO CLICAR