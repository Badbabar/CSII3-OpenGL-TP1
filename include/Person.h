#ifndef PERSON_H
#define PERSON_H


class Person
{
    public:
        Person();
        Person(double x, double y, double angle);
        virtual ~Person();
        void Draw();
    protected:
        double x;
        double y;
        double angle;
    private:
};

#endif // PERSON_H
