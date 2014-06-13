#include "../include/Line_3d.h"

Line_3d::Line_3d(){}
Line_3d::Line_3d(int n_point)
{
    no_point=n_point;
    point=new Point_3d[n_point];
}
Line_3d::Line_3d(int _id, int n_point)
{
    id=_id;
    no_point=n_point;
    point=new Point_3d[n_point];
}

long Line_3d::get_id()
{
    return id;
}
int Line_3d::set_id(long _id)
{
    id=_id;
    return 0;
}

int Line_3d::get_no_point()
{
    return no_point;
}
int Line_3d::set_no_point(int _no_point)
{
    no_point=_no_point;
    return 0;
}

int Line_3d::set_point(int index,Point_3d pt)
{
    point[index].set_x(pt.get_x());
    point[index].set_y(pt.get_y());
    point[index].set_z(pt.get_z());
    return 0;
}

Point_3d Line_3d::get_point(int index)
{
    return point[index];
}

int Line_3d::set_point_array(int n_point, Point_3d* p_array)
{
    no_point=n_point;
    point=new Point_3d[no_point];
    for(int i=0; i<no_point; i++)
    {
        point[i]=p_array[i];
    }
    return 0;
}
Point_3d* Line_3d::get_point_array()
{
    Point_3d *pt;
    pt=new Point_3d[no_point];
    for(int i=0; i<no_point; i++)
    {
        pt[i]=point[i];
    }
    return pt;
}
