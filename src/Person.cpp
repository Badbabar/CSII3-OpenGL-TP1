#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "../include/Person.h"
#include "../include/Point.h"
#include "../include/Color.h"

#define PERSON_SPEED 2

Person::Person()
{
    //ctor
}

Person::Person(double minX, double maxX, double minY, double maxY)
{
    x = (double) (rand() % (int) maxX + (int) minX);
    y = (double) (rand() % (int) maxY + (int) minY);
    angle = (double) (rand() % 360 + 0);
    alive = true;
    InitColor();
}

Person::Person(double x, double y, double angle):
    x(x), y(y), angle(angle)
{
    alive = true;
    InitColor();
}

Person::~Person()
{
    //dtor
}

void Person::InitColor()
{
    color.r = rand() % 256;
    color.g = rand() % 256;
    color.b = rand() % 256;
}

void Person::InitBloods()
{
    Blood * blood;

    for (int i = 0; i < 5; i++)
    {
        blood = new Blood();
        blood->offset.x = rand() % 34 - 16;
        blood->offset.y = rand() % 34 - 16;
        blood->size = rand() % 11;

        bloods.push_back(blood);
    }
}

void Person::Draw()
{
    // Sauvegarde du repère
    glPushMatrix();

    // Changement de repère
    glTranslated(x, y, 0);

    // Rotation du plan;
    glRotated(angle, 0, 0, 1);


    if (alive) {
        // Couleur du passant
        glColor3ub(color.r, color.g, color.b);

        // Corps du passant
        glBegin(GL_QUADS);
            glVertex2d(-4, 12);
            glVertex2d(-4, -12);
            glVertex2d(4, -12);
            glVertex2d(4, 12);
        glEnd();

        // Tête du passant
        glColor3ub(0, 0, 0);

        GLUquadricObj* quadric = gluNewQuadric();
        gluQuadricDrawStyle(quadric, GLU_FILL);
        gluDisk(quadric, 0, 6, 16, 8);
    } else {
        // Couleur du sang
        glColor3ub(200, 20, 50);

        GLUquadricObj* quadric = gluNewQuadric();
        gluQuadricDrawStyle(quadric, GLU_FILL);

        if (bloods.size() == 0)
            InitBloods();

        for (int i = 0; i < bloods.size(); i++)
        {
            glPushMatrix();
            glTranslated(bloods[i]->offset.x, bloods[i]->offset.y, 0);
            gluDisk(quadric, 0, bloods[i]->size, 16, 8);
            glPopMatrix();
        }
    }

    // Remise en état du repère
    glPopMatrix();
}

void Person::UpdatePositions(double minX, double maxX, double minY, double maxY)
{
    if (alive) {
        x += cos(angle*M_PI/180) * PERSON_SPEED;
        y += sin(angle*M_PI/180) * PERSON_SPEED;

        if (x < minX) {
            angle = 180 - angle;
            x = minX;
        }

        if (x > maxX) {
            angle = 180 - angle;
            x = maxX;
        }

        if (y < minY) {
            angle = 360 - angle;
            y = minY;
        }

        if (y > maxY) {
            angle = 360 - angle;
            y = maxY;
        }
    }
}

void Person::SetAlive(bool alive)
{
    this->alive = alive;
}

bool Person::IsAlive()
{
    return alive;
}

double Person::GetX()
{
    return x;
}

double Person::GetY()
{
    return y;
}

bool Person::Collision(double x, double y)
{
    Point points[] = {
        Point(-4 + this->x, -12 + this->y),
        Point(4 + this->x, -12 + this->y),
        Point(4 + this->x, 12 + this->y),
        Point(-4 + this->x, 12 + this->y),
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
