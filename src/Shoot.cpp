#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#include "../include/Shoot.h"
#include "../include/Point.h"

Shoot::Shoot()
{
    //ctor
}

Shoot::Shoot(double x, double y, double angle):
    x(x), y(y), angle(angle)
{

}

Shoot::~Shoot()
{
    //dtor
}

void Shoot::Draw()
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

void Shoot::UpdatePositions()
{
    x += cos(angle*M_PI/180)*15;
    y += sin(angle*M_PI/180)*15;
}

bool Shoot::IsOut(double minX, double maxX, double minY, double maxY)
{
    return (x < minX || x > maxX || y < minY || y > maxY);
}

double Shoot::GetX()
{
    return x;
}

double Shoot::GetY()
{
    return y;
}

bool Shoot::Collision(double x, double y)
{
    Point points[] = {
        Point(0 + this->x, 2 + this->y),
        Point(0 + this->x, -2 + this->y),
        Point(10 + this->x, -2+ this->y),
        Point(10 + this->x, 2 + this->y),
    };

    int nbPoints = 4;

    Point A, B, D, T;
    double d;

    for(int i = 0; i < nbPoints; i++)
    {
        A = points[i];

        if (i == nbPoints - 1) // si c'est le dernier point, on relie au premier
            B = points[0];
        else // sinon on relie au suivant.
            B = points[i+1];

        D.x = B.x - A.x;
        D.y = B.y - A.y;
        T.x = x - A.x;
        T.y = y - A.y;

        d = D.x*T.y - D.y*T.x;

        if (d < 0)
            return false;  // un point à droite et on arrête tout.
    }

    return true;
}
