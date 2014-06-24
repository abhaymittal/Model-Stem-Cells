#include "Point.h"

Point::Point() {
	// TODO Auto-generated constructor stub

}

Point::~Point() {
	// TODO Auto-generated destructor stub
}

int Point::getVar(char varName)
{
    switch(varName)
    {
        case 'x':
            return x;
        break;

        case 'y':
            return y;
        break;

        case 'z':
            return z;
        break;

    }
    return -1;
}

int Point::setVar(char varName, int value)
{
    switch(varName)
    {
        case 'x':
            x=value;
        break;

        case 'y':
            y=value;
        break;

        case 'z':
            z=value;
        break;
    }
    return 0;
}
