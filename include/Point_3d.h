#ifndef POINT_3D_H
#define POINT_3D_H


class Point_3d
{
    private:
    int x;
    int y;
    int z;

    public:
    Point_3d(){}
    Point_3d(int _x,int _y, int _z):x(_x),y(_y),z(_z)
    {}
    int get_x();
    int get_y();
    int get_z();
    int get_var(char var_name);

    int set_x(int xval);
    int set_y(int yval);
    int set_z(int zval);
    int set_var(char var_name, int val);

};

#endif // POINT_3D_H
