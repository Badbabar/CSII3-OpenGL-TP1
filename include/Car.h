#ifndef CAR_H
#define CAR_H

#include "../include/Ship.h"


class Car : public Ship
{
    public:
        Car();
        Car(double x, double y);
        virtual ~Car();
        void Draw();
    protected:
    private:
};

#endif // CAR_H
