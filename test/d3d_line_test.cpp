#include "../stem_env.h"
#include <cstdio>

int main()
{
    Stem_env st;
    Point_3d p1(1,2,1),p2(19,11,11);

    Point_3d *pt=st.draw_3D_line(p1,p2);

    for(int i=0;i<19;i++)
    {
        printf("%d | %d | %d\n",pt[i].get_x(),pt[i].get_y(),pt[i].get_z());
    }
}
