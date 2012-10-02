#ifndef SHIP_H
#define SHIP_H

#include "../include/Shoot.h"

class Ship
{
    public:
        Ship();
        Ship(double x, double y);
        virtual ~Ship();
        void Draw();
        void UpdatePositions(double minX, double maxX, double minY, double maxY);
        double IncrementAngle();
        double DecrementAngle();
        double IncrementSpeed();
        double DecrementSpeed();
        double GetX();
        double GetY();
        double GetAngle();
        Shoot * Fire();
        bool Collision(double x, double y);
    protected:
        double x;
        double y;
        double angle;
        double speed;
    private:
};

#endif // SHIP_H
