#include "../include/Stem_env.h"
#include <cstdio>

int main()
{
    Stem_env st;
    Point_3d p1(1,2,1),p2(19,11,11);

    Line_3d l1=st.draw_3D_line(p1,p2);

    for(int i=0;i<l1.get_no_point();i++)
    {
        printf("%d | %d | %d\n",l1.get_point(i).get_x(),l1.get_point(i).get_y(),l1.get_point(i).get_z());
    }
}
