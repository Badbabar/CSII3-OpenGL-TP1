#ifndef BLOOD_H
#define BLOOD_H

#include "../include/Point.h"

class Blood
{
    public:
        Blood();
        virtual ~Blood();
        Point offset;
        int size;
    protected:
    private:
};

#endif // BLOOD_H
