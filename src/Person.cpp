#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#include "../include/Person.h"

Person::Person()
{
    //ctor
}

Person::Person(double x, double y, double angle):
    x(x), y(y), angle(angle)
{

}

Person::~Person()
{
    //dtor
}

void Person::Draw()
{
    // Sauvegarde du repère
    glPushMatrix();

    // Changement de repère
    glTranslated(x,y,0);

    // Rotation du plan;
    glRotated(angle, 0, 0, 1);

    // Dessin du tir ici
    glColor3ub(255, 255, 0);

    glBegin(GL_QUADS);
        glVertex2d(0, 2);
        glVertex2d(0, -2);
        glVertex2d(10, -2);
        glVertex2d(10, 2);
    glEnd();

    // Remise en état du repère
    glPopMatrix();
}
