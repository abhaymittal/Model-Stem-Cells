#include <ctime>    //time
#include <cstdlib>  //rand, srand
#include <cmath>    //sqrt, floor, ceil

#include "stem_env.h"
#include "var.h"

using namespace std;

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


int Stem_env::create_line(int i, Point_3d box[8], Point_3d lines[][2], int f2, int d2, int xmin, int xmax, int xdiff1, int length, int width, int depth)
{
    int j, x_translate, y_translate, z_translate;
    int ymin, ymax, f2_x2, f2_x2_y2;

    j = rand()%8; //random vertex of box
    lines[i][0].set_x(box[j].get_x());
    lines[i][0].set_y(box[j].get_y());
    lines[i][0].set_z(box[j].get_z());

    lines[i][1].set_x(( rand() % xdiff1 ) + xmin);

    f2_x2 = f2 - (lines[i][1].get_x() * lines[i][1].get_x()); // currently origin is assumed as fixed point, so f2_x2 is calculated before adjustment

    //adjustment
    if(lines[i][0].get_x() != 0)
    {
        lines[i][1].set_x(length - lines[i][1].get_x()); //lines[i][0].x - lines[i][1].x
    }

    if( f2_x2 > d2 )
    {
        ymin = ceil(sqrt(f2_x2 - d2));
    }
    else
    {
        ymin = 0;
    }

    ymax = floor(sqrt(f2_x2));
    if(width<ymax) ymax = width;

    lines[i][1].set_y(( rand() % ((ymax - ymin) + 1) ) + ymin);
    f2_x2_y2 = f2_x2 - (lines[i][1].get_y() * lines[i][1].get_y());

    if(lines[i][0].get_y() != 0)
    {
        lines[i][1].set_y(width - lines[i][1].get_y());
    }

    lines[i][1].set_z(floor(sqrt(f2_x2_y2))); // floor => inside sphere of radius fiber_length, ceil => outside

    if(lines[i][0].get_z() != 0)
    {
        lines[i][1].set_z(depth - lines[i][1].get_z());
    }


    if(lines[i][0].get_x() == 0)
    {
        x_translate = rand()%((length - lines[i][1].get_x()) + 1 );
    }
    else
    {
        x_translate = -( rand() % (lines[i][1].get_x() + 1) );
    }

    if(lines[i][0].get_y() == 0)
    {
        y_translate = rand()%((width - lines[i][1].get_y()) + 1 );
    }
    else
    {
        y_translate = -( rand() % (lines[i][1].get_y() + 1) );
    }

    if(lines[i][0].get_z() == 0)
    {
        z_translate = rand()%((depth - lines[i][1].get_z()) + 1 );
    }
    else
    {
        z_translate = -( rand() % (lines[i][1].get_z() + 1) );
    }

    lines[i][0].set_x(lines[i][0].get_x() + x_translate);
    lines[i][0].set_y(lines[i][0].get_y() + y_translate);
    lines[i][0].set_z(lines[i][0].get_z() + z_translate);
    lines[i][1].set_x(lines[i][1].get_x() + x_translate);
    lines[i][1].set_y(lines[i][1].get_y() + y_translate);
    lines[i][1].set_z(lines[i][1].get_z() + z_translate);

    return 0;
}

int Stem_env::setup_environment(int length, int width, int depth, int fiber_count, int fiber_length);
{

    Point_3d box[8];
    Point_3d lines[fiber_count][2];
    int i;
    int f2, d2, xmin, xmax, xdiff1;

    box[0].set_x(0);
    box[0].set_y(0);
    box[0].set_z(0);

    box[1].set_x(0);
    box[1].set_y(0);
    box[1].set_z(depth);

    box[2].set_x(0);
    box[2].set_y(width);
    box[2].set_z(0);

    box[3].set_x(0);
    box[3].set_y(width);
    box[3].set_z(depth);

    box[4].set_x(length);
    box[4].set_y(0);
    box[4].set_z(0);

    box[5].set_x(length);
    box[5].set_y(0);
    box[5].set_z(depth);

    box[6].set_x(length);
    box[6].set_y(width);
    box[6].set_z(0);

    box[7].set_x(length);
    box[7].set_y(width);
    box[7].set_z(depth);

    srand(time(NULL));

    f2 = fiber_length * fiber_length;
    d2 = depth * depth;
    if( (f2 - d2) > (width*width) )
    {
        xmin = ceil(sqrt( (f2 - d2) - (width*width) ));
    }
    else
    {
        xmin = 0;
    }

    xmax = (fiber_length<length)?fiber_length:length;

    xdiff1 = (xmax - xmin) + 1;


    for(i=0; i<fiber_count; i++)
    {
        create_line(i, box, lines, f2, d2, xmin, xmax, xdiff1, length, width, depth);
    }

    return 0;
}

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
        if(counter_1>=ind_val.get_delta())
        {
            dep_val_1.set_value(dep_val_1.get_value()+inc_dep_1);
            counter_1=counter_1-ind_val.get_delta();
        }
        if(counter_2>=ind_val.get_delta())
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
