#include "../stem_env.h"
#include <cstdio>

int main()
{
    stem_env st;
    int **pt=st.draw_3D_line(1,2,1,19,11,11);

    for(int i=0;i<19;i++)
    {
        printf("%d | %d | %d\n",pt[i][0],pt[i][1],pt[i][2]);
    }
}
