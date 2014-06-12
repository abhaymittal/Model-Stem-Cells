#include "Point_3d.h"

int Point_3d::get_x()
{
    return x;
}

int Point_3d::get_y()
{
    return y;
}

int Point_3d::get_z()
{
    return z;
}

int Point_3d::get_var(char var_name)
{
    switch(var_name)
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


int Point_3d::set_x(int xval)
{
    x = xval;
    return 0;
}

int Point_3d::set_y(int yval)
{
    y = yval;
    return 0;
}

int Point_3d::set_z(int zval)
{
    z = zval;
    return 0;
}

int Point_3d::set_var(char var_name,int val)
{
    switch(var_name)
    {
        case 'x':
            x=val;
        break;

        case 'y':
            y=val;
        break;

        case 'z':
            z=val;
        break;
    }
    return 0;
}
