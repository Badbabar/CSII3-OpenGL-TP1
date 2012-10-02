#include <GL/gl.h>
#include <GL/glu.h>
#include "../include/Car.h"

Car::Car()
{
    //ctor
}

Car::~Car()
{
    //dtor
}

Car::Car(double x, double y):
    Ship(x, y)
{

}

void Car::Draw()
{
    // Sauvegarde du repère
    glPushMatrix();

    // Changement de repère
    glTranslated(x,y,0);

    // Rotation du plan
    glRotated(angle, 0, 0, 1);

    // Couleur de la carrosserie
    glColor3ub(200, 40, 40);

    // Carlingue
    glBegin(GL_QUADS);
        glVertex2d(-60, 30);
        glVertex2d(60, 30);
        glVertex2d(60, -30);
        glVertex2d(-60, -30);
    glEnd();

    // Couleur des roues
    glColor3ub(20, 20, 20);

    // Route arrière gauche
    glBegin(GL_QUADS);
        glVertex2d(-50, 30);
        glVertex2d(-50, 40);
        glVertex2d(-30, 40);
        glVertex2d(-30, 30);
    glEnd();

    // Route arrière droite
    glBegin(GL_QUADS);
        glVertex2d(-50, -30);
        glVertex2d(-50, -40);
        glVertex2d(-30, -40);
        glVertex2d(-30, -30);
    glEnd();

    // Route avant gauche
    glBegin(GL_QUADS);
        glVertex2d(50, 30);
        glVertex2d(50, 40);
        glVertex2d(30, 40);
        glVertex2d(30, 30);
    glEnd();

    // Route avant droite
    glBegin(GL_QUADS);
        glVertex2d(50, -30);
        glVertex2d(50, -40);
        glVertex2d(30, -40);
        glVertex2d(30, -30);
    glEnd();

    // Couleur des vitres
    glColor3ub(100, 100, 160);

    // Vitre avant
    glBegin(GL_QUADS);
        glVertex2d(20, 27);
        glVertex2d(40, 27);
        glVertex2d(40, -27);
        glVertex2d(20, -27);
    glEnd();

    // Remise en état du repère
    glPopMatrix();
}
