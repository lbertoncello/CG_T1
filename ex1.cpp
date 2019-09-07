#include <stdlib.h>
#include <stdio.h> 
#include <GL/glut.h>
#include <iostream>
#include <string>

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

int x_window_size = 250;
int y_windows_size = 250;
int x_windows_initial_position = 100;
int y_windows_initial_position = 100;

float offset_value = 0.01;
float x_offset = 0;
float y_offset = 0;
float x_origin = 0.5;
float y_origin = 0.5;

bool* keyStates = new bool[256];
bool isLeftMouseButtonPressed = false;

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

void display (void) {
    keyOperations();
     /* Limpar todos os pixels */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Desenhar um polígono branco (retângulo) */
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex3f(x_origin - 0.25 + x_offset, y_origin - 0.25 + y_offset, 0.0);
        glVertex3f(x_origin + 0.25 + x_offset, y_origin - 0.25 + y_offset, 0.0);
        glVertex3f(x_origin + 0.25 + x_offset, y_origin + 0.25 + y_offset, 0.0);
        glVertex3f(x_origin - 0.25 + x_offset, y_origin + 0.25 + y_offset, 0.0);
    glEnd();

    /* Não esperar */
    glFlush();
}

void idle(void) {
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON) {
        if(state == GLUT_UP) {
            x_origin = x / float(x_window_size);
            y_origin = 1.0 - (y / float(y_windows_size));
            //puts(std::to_string(x_origin).c_str());
            //puts(std::to_string(y_origin).c_str());
        } else {
            isLeftMouseButtonPressed = true;
        }
    }
}

void motion(int x, int y) {
    if(isLeftMouseButtonPressed) {
        x_origin = x / float(x_window_size);
        y_origin = 1.0 - (y / float(y_windows_size));
    }
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

    glutIdleFunc(idle);
    glutMainLoop();

    return 0;
}

//PRÓXIMO PASSO: DESENHAR O QUADRADO ONDE O USUÁRIO CLICAR