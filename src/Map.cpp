#include <GL/gl.h>
#include <GL/glu.h>

#include "../include/Map.h"

Map::Map()
{
    //ctor
}

Map::~Map()
{
    //dtor
}

void Map::Draw(double minX, double maxX, double minY, double maxY)
{
    // Sauvegarde du repère
    glPushMatrix();

    double chunk = (maxX - minX) / 48;

    glColor3ub(0, 130, 0);

    // Dessin de l'herbe
    glBegin(GL_QUADS);
        glVertex2d(minX, maxY);
        glVertex2d(minX, minY);
        glVertex2d(maxX, minY);
        glVertex2d(maxX, maxY);
    glEnd();

    // Dessin des trottoirs
    glColor3ub(127, 127, 127);

    glBegin(GL_QUADS);
        glVertex2d(chunk * 12, maxY);
        glVertex2d(chunk * 36, maxY);
        glVertex2d(chunk * 36, minY);
        glVertex2d(chunk * 12, minY);
    glEnd();

    // Dessin de la route
    glColor3ub(30, 30, 30);

    glBegin(GL_QUADS);
        glVertex2d(chunk * 18, maxY);
        glVertex2d(chunk * 30, maxY);
        glVertex2d(chunk * 30, minY);
        glVertex2d(chunk * 18, minY);
    glEnd();

    // Dessin des marquages
    glColor3ub(255, 255, 255);

    glBegin(GL_QUADS);
        glVertex2d(chunk * 23.8, maxY);
        glVertex2d(chunk * 24.2, maxY);
        glVertex2d(chunk * 24.2, minY);
        glVertex2d(chunk * 23.8, minY);
    glEnd();

    // Remise en état du repère
    glPopMatrix();
}
