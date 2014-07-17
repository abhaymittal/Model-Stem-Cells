#include "Point.h"

Point::Point() {
	// TODO Auto-generated constructor stub

}

Point(int x_, int y_, int z_):x(x_), y(y_), z(z_)
{}

int Point::getX() const
{
    return x;
}

void Point::setX(int x_)
{
    this->x = x_;
}

int Point::getY() const
{
    return y;
}

void Point::setY(int y_)
{
    this->y = y_;
}

int Point::getZ() const
{
    return z;
}

void Point::setZ(int z_)
{
    this->z = z_;
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
