#ifndef SHOOT_H
#define SHOOT_H


class Shoot
{
    public:
        Shoot();
        Shoot(double x, double y, double angle);
        virtual ~Shoot();
        void Draw();
        bool IsOut(double minX, double maxX, double minY, double maxY);
        void UpdatePositions();
        bool Collision(double x, double y);
        double GetX();
        double GetY();
    protected:
        double x;
        double y;
        double angle;
    private:
};

#endif // SHOOT_H
