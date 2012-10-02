#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#include "../include/Ship.h"

Ship::Ship()
{
    //ctor
}

Ship::Ship(double x, double y):
    x(x), y(y)
{
    angle = 90;
    speed = 0;
}

Ship::~Ship()
{
    //dtor
}

void Ship::Draw()
{
    // Sauvegarde du repère
    glPushMatrix();

    // Changement de repère
    glTranslated(x,y,0);

    // Rotation du plan;
    glRotated(angle, 0, 0, 1);

    // Dessin du vaisseau ici
    glColor3ub(255, 255, 255);

    // Carlingue
    glBegin(GL_QUADS);
        glVertex2d(-10, 10);
        glVertex2d(10, 10);
        glVertex2d(10, -10);
        glVertex2d(-10, -10);
    glEnd();

    // Aile gauche
    glBegin(GL_TRIANGLES);
        glVertex2d(-8, 0);
        glVertex2d(30, 10);
        glVertex2d(-8, 20);
    glEnd();

    // Aile droite
    glBegin(GL_TRIANGLES);
        glVertex2d(-8, 0);
        glVertex2d(30, -10);
        glVertex2d(-8, -20);
    glEnd();

    // Queue
    glBegin(GL_TRIANGLES);
        glVertex2d(-15, 5);
        glVertex2d(-15, -5);
        glVertex2d(-5, 0);
    glEnd();

    // Remise en état du repère
    glPopMatrix();
}

void Ship::UpdatePositions(double minX, double maxX, double minY, double maxY)
{
    x += cos(angle*M_PI/180)*speed/15;
    y += sin(angle*M_PI/180)*speed/15;

    if (x < minX)
        x = maxX;

    if (x > maxX)
        x = minX;

    if (y < minY)
        y = maxY;

    if (y > maxY)
        y = minY;
}

double Ship::IncrementAngle()
{
    return ++angle;
}

double Ship::DecrementAngle()
{
    return --angle;
}

double Ship::IncrementSpeed()
{
    ++speed;

    if (speed > 10)
        speed = 100;

    return speed;
}

double Ship::DecrementSpeed()
{
    --speed;

    if (speed < 0)
        speed = 0;

    return speed;
}

double Ship::GetAngle()
{
    return angle;
}

double Ship::GetY()
{
    return y;
}

double Ship::GetX()
{
    return x;
}
