#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#include "draw.h"
#include "tinyxml.h"

using namespace std;

string window_title;
int window_size_x = 250;
int window_size_y = 250;
int window_initial_x_position = 100;
int window_initial_y_position = 100;

Color circleDefaultColor;
Color circleModelDefaultColor;
Color circleModelOverlapColor;
Color backgroundColor;

bool isLeftMouseButtonPressed = false;
bool isRightMouseButtonPressed = false;

Draw draw;


void circleInit(TiXmlElement *application)
{
    TiXmlElement *circle = application->FirstChildElement("circulo");
    TiXmlAttribute *circleAttribute = circle->FirstAttribute();

    while (circleAttribute)
    {
        if (strcmp(circleAttribute->Name(), "raio") == 0)
        {
            draw.setRadius(stof(circleAttribute->Value()));
        }
        else if (strcmp(circleAttribute->Name(), "corR") == 0)
        {
            circleDefaultColor.setR(stof(circleAttribute->Value()));
        }
        else if (strcmp(circleAttribute->Name(), "corG") == 0)
        {
            circleDefaultColor.setG(stof(circleAttribute->Value()));
        }
        else if (strcmp(circleAttribute->Name(), "corB") == 0)
        {
            circleDefaultColor.setB(stof(circleAttribute->Value()));
        }

        circleAttribute = circleAttribute->Next();
    }
}

void circleModelInit(TiXmlElement *application)
{
    TiXmlElement *circle = application->FirstChildElement("circuloModelo");
    TiXmlAttribute *circleAttribute = circle->FirstAttribute();

    while (circleAttribute)
    {
        if (strcmp(circleAttribute->Name(), "raio") == 0)
        {
            draw.setRadius(stof(circleAttribute->Value()));
        }
        else if (strcmp(circleAttribute->Name(), "corR") == 0)
        {
            circleModelDefaultColor.setR(stof(circleAttribute->Value()));
        }
        else if (strcmp(circleAttribute->Name(), "corG") == 0)
        {
            circleModelDefaultColor.setG(stof(circleAttribute->Value()));
        }
        else if (strcmp(circleAttribute->Name(), "corB") == 0)
        {
            circleModelDefaultColor.setB(stof(circleAttribute->Value()));
        }
        else if (strcmp(circleAttribute->Name(), "corSobreposicaoR") == 0)
        {
            circleModelOverlapColor.setB(stof(circleAttribute->Value()));
        }
        else if (strcmp(circleAttribute->Name(), "corSobreposicaoG") == 0)
        {
            circleModelOverlapColor.setB(stof(circleAttribute->Value()));
        }
        else if (strcmp(circleAttribute->Name(), "corSobreposicaoB") == 0)
        {
            circleModelOverlapColor.setB(stof(circleAttribute->Value()));
        }

        circleAttribute = circleAttribute->Next();
    }
}

void dimensionInit(TiXmlElement *window) {
    TiXmlElement *dimension = window->FirstChildElement("dimensao");
    TiXmlAttribute *dimensionAttribute = dimension->FirstAttribute();

    while (dimensionAttribute)
    {
        if (strcmp(dimensionAttribute->Name(), "largura") == 0)
        {
            window_size_x = stof(dimensionAttribute->Value());
        }
        else if (strcmp(dimensionAttribute->Name(), "altura") == 0)
        {
            window_size_y = stof(dimensionAttribute->Value());
        }

        dimensionAttribute = dimensionAttribute->Next();
    }
}

void backgroundInit(TiXmlElement *window) {
    TiXmlElement *background = window->FirstChildElement("fundo");
    TiXmlAttribute *backgroundAttribute = background->FirstAttribute();

    while (backgroundAttribute)
    {
        if (strcmp(backgroundAttribute->Name(), "corR") == 0)
        {
            backgroundColor.setR(stof(backgroundAttribute->Value()));
        }
        else if (strcmp(backgroundAttribute->Name(), "corG") == 0)
        {
            backgroundColor.setG(stof(backgroundAttribute->Value()));
        }
        else if (strcmp(backgroundAttribute->Name(), "corB") == 0)
        {
            backgroundColor.setB(stof(backgroundAttribute->Value()));
        }

        backgroundAttribute = backgroundAttribute->Next();
    }
}

void titleInit(TiXmlElement *window) {
    TiXmlElement *title = window->FirstChildElement("titulo");

    window_title = title->GetText();
}

void windowInit(TiXmlElement *application)
{
    TiXmlElement *window = application->FirstChildElement("janela");
    
    dimensionInit(window);
    backgroundInit(window);
    titleInit(window);
}

void parametersInit(const char *filename)
{
    TiXmlDocument doc(filename);
    bool loadOkay = doc.LoadFile();

    if (loadOkay)
    {
        TiXmlElement *application = doc.RootElement();

        circleInit(application);
        circleModelInit(application);
        windowInit(application);
    }
    else
    {
        puts("Failed to load file");
    }
}

void display(void)
{
    /* Limpar todos os pixels */
    glClear(GL_COLOR_BUFFER_BIT);

    if (draw.thereIsCircleMoving() == false)
    {
        Circle circle(draw.getCurrentCenter(), draw.getRadius());

        if (draw.checkIntersection(circle))
        {
            draw.drawCircle(circleModelOverlapColor);
        }
        else
        {
            draw.drawCircle(circleModelDefaultColor);
        }
    }
    else
    {
        draw.updateCurrentCircleMoving();
    }

    draw.drawAllCircles(circleDefaultColor);

    /* Não esperar */
    glFlush();
}

void idle(void)
{
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_UP)
        {
            isLeftMouseButtonPressed = false;
            draw.updateCurrentCenter(x, y, window_size_x, window_size_y);

            Circle circle(draw.getCurrentCenter().getX(), draw.getCurrentCenter().getY(), draw.getRadius());

            if (draw.checkIntersection(circle) == false)
            {
                draw.addCircle(circle);
            }
        }
        else
        {
            isLeftMouseButtonPressed = true;
        }
    }

    if (button == GLUT_RIGHT_BUTTON)
    {
        if (state == GLUT_UP)
        {
            isRightMouseButtonPressed = false;
            draw.setCurrentCircleMoving(NULL);
        }
        else
        {
            draw.chooseCircleToMove();

            isRightMouseButtonPressed = true;
        }
    }
}

void motion(int x, int y)
{
    if (isLeftMouseButtonPressed)
    {
        draw.updateCurrentCenter(x, y, window_size_x, window_size_y);
    }

    if (isRightMouseButtonPressed)
    {
        draw.updateCurrentCenter(x, y, window_size_x, window_size_y);
    }
}

void passiveMotion(int x, int y)
{
    draw.updateCurrentCenter(x, y, window_size_x, window_size_y);
}

void init(void)
{
    /* selecionar cor de fundo (preto) */
    glClearColor(backgroundColor.getR(), backgroundColor.getG(), backgroundColor.getB(), 0.0);

    /* Inicializa sistema de viz */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1, 0.0, 1, -1.0, 1.0);
    //glOrtho(0.0f, window_size_x, window_size_y, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char **argv)
{
    string filename = "Test_1/config.xml";
    parametersInit(filename.c_str());

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(window_size_x, window_size_y);
    glutInitWindowPosition(window_initial_x_position, window_initial_y_position);
    glutCreateWindow(window_title.c_str());
    init();
    glutDisplayFunc(display);

    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutPassiveMotionFunc(passiveMotion);

    glutIdleFunc(idle);
    glutMainLoop();

    return 0;
}