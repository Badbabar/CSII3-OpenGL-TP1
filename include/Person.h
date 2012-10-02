#ifndef PERSON_H
#define PERSON_H

#include <vector>

#include "Color.h"
#include "Blood.h"

class Person
{
    public:
        Person();
        Person(double x, double y, double angle);
        Person(double minX, double maxX, double minY, double maxY);
        virtual ~Person();
        void Draw();
        void UpdatePositions(double minX, double maxX, double minY, double maxY);
        void SetAlive(bool alive);
        bool IsAlive();
        double GetX();
        double GetY();
        bool Collision(double x, double y);
        void InitColor();
        void InitBloods();
    protected:
        double x;
        double y;
        double angle;
        bool alive;
        Color color;
        std::vector<Blood *> bloods;
    private:
};

#endif // PERSON_H
