#ifndef LINE_3D_H
#define LINE_3D_H
#include "Point_3d.h"


class Line_3d
{
    private:
    long id;
    int no_point;
    Point_3d *point;

    public:

    Line_3d(int n_point);
    Line_3d(int _id, int n_point);
    long get_id();
    int set_id(long _id);
    int get_no_point();
    int set_no_point(int _no_point);
    int set_point(int index,Point_3d pt);
    Point_3d get_point(int index);
    int set_point_array(int n_point, Point_3d* p_array);
    Point_3d* get_point_array();

};


#endif // LINE_3D_H
