#include "stem_env.h"
#include "var.h"
stem_env::draw_3D_line(int x1, int y1, int z1, int x2, int y2, int z2)
{

    if(abs(y2-y1)>abs(x2-x1))
    {
        if(abs(z2-z1)>abs(y2-y1))
        {
            Var ind_val('z',2,abs(z2-z1),z1);
            Var dep_val_1('x',0,abs(x2-x1),x1);
            Var dep_val_2('y',1,abs(y2-y1),y1);
        }
        else
        {
            Var ind_val'y',1,abs(y2-y1),y1);
            Var dep_val_1('z',2,abs(z2-z1),z1);
            Var dep_val_2('x',0,abs(x2-x1),x1);
        }
    }
    else
    {
        if (abs(z2-z1)>abs(x2-x1))
        {
            Var ind_val('z',2,abs(z2-z1),z1);
            Var dep_val_1('x',0,abs(x2-x1),x1);
            Var dep_val_2('y',1,abs(y2-y1),y1);
        }
        else
        {
            Var ind_val('x',0,abs(x2-x1),x1);
            Var dep_val_1('y',1,abs(y2-y1),y1);
            Var dep_val_2('z',2,abs(z2-z1),z1);
        }
    }


    int counter_1=0, counter_2=0;

    int **pt_array;
    pt_array=new int*[ind_val.get_delta()+1];
    for(int i=0;i<ind_val.get_delta()+1;i++)
    {
        pt_array[i]=new int[3];
    }



}

