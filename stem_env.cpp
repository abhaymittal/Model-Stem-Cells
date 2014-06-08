#include "stem_env.h"
#include "var.h"
#include <cmath>
using namespace std;
int** stem_env:: draw_3D_line(int x1, int y1, int z1, int x2, int y2, int z2)
{

    char sign_x=((z2-z1)<0)?'-':'+';
    char sign_y=((y2-y1)<0)?'-':'+';
    char sign_z=((x2-x1)<0)?'-':'+';
    char sign_ind, sign_dep_1, sign_dep_2;

    Var ind_val,dep_val_1,dep_val_2;

    if(abs(y2-y1)>abs(x2-x1))
    {
        if(abs(z2-z1)>abs(y2-y1))
        {
            ind_val=*(new Var('z',2,abs(z2-z1),z1));
            sign_ind=((z2-z1)<0)?'-':'+';

            dep_val_1=*(new Var('x',0,abs(x2-x1),x1));
            sign_dep_1=((x2-x1)<0)?'-':'+';

            dep_val_2=*(new Var('y',1,abs(y2-y1),y1));
            sign_dep_2=((y2-y1)<0)?'-':'+';
        }
        else
        {
            ind_val=*(new Var('y',1,abs(y2-y1),y1));
            sign_ind=((y2-y1)<0)?'-':'+';

            dep_val_1=*(new Var('z',2,abs(z2-z1),z1));
            sign_dep_1=((z2-z1)<0)?'-':'+';

            dep_val_2=*(new Var('x',0,abs(x2-x1),x1));
            sign_dep_2=((x2-x1)<0)?'-':'+';
        }
    }
    else
    {
        if (abs(z2-z1)>abs(x2-x1))
        {
            ind_val=*(new Var('z',2,abs(z2-z1),z1));
            sign_ind=((z2-z1)<0)?'-':'+';

            dep_val_1=*(new Var('x',0,abs(x2-x1),x1));
            sign_dep_1=((x2-x1)<0)?'-':'+';

            dep_val_2=*(new Var('y',1,abs(y2-y1),y1));
            sign_dep_2=((y2-y1)<0)?'-':'+';
        }
        else
        {
            ind_val=*(new Var('x',0,abs(x2-x1),x1));
            sign_ind=((x2-x1)<0)?'-':'+';

            dep_val_1=*(new Var('y',1,abs(y2-y1),y1));
            sign_dep_1=((y2-y1)<0)?'-':'+';

            dep_val_2=*(new Var('z',2,abs(z2-z1),z1));
            sign_dep_2=((z2-z1)<0)?'-':'+';
        }
    }


    int **pt_array;
    pt_array=new int*[ind_val.get_delta()+1];
    for(int i=0;i<ind_val.get_delta()+1;i++)
    {
        pt_array[i]=new int[3];
    }

    int ind_val_f=ind_val.get_delta()+ind_val.get_value();
    int counter_1=0, counter_2=0;
    int inc_ind, inc_dep_1, inc_dep_2;
    int pt_index=0;

    inc_ind=(sign_ind=='+')?1:-1;
    inc_dep_1=(sign_dep_1=='+')?1:-1;
    inc_dep_2=(sign_dep_2=='+')?1:-1;

    pt_array[pt_index][ind_val.get_index()]=ind_val.get_value();
    pt_array[pt_index][dep_val_1.get_index()]=dep_val_1.get_value();
    pt_array[pt_index][dep_val_2.get_index()]=dep_val_2.get_value();
    pt_index++;

    while(ind_val.get_value()!=ind_val_f)
    {
        counter_1=counter_1+dep_val_1.get_delta();
        counter_2=counter_2+dep_val_2.get_delta();

        ind_val.set_value(ind_val.get_value()+inc_ind);
        if(counter_1>ind_val.get_delta())
        {
            dep_val_1.set_value(dep_val_1.get_value()+inc_dep_1);
            counter_1=counter_1-ind_val.get_delta();
        }
        if(counter_2>ind_val.get_delta())
        {
            dep_val_2.set_value(dep_val_2.get_value()+inc_dep_2);
            counter_2=counter_2-ind_val.get_delta();
        }

        pt_array[pt_index][ind_val.get_index()]=ind_val.get_value();
        pt_array[pt_index][dep_val_1.get_index()]=dep_val_1.get_value();
        pt_array[pt_index][dep_val_2.get_index()]=dep_val_2.get_value();
        pt_index++;

    }
    return pt_array;

}

