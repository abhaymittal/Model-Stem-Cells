#include <ctime>    //time
#include <cstdlib>  //rand, srand
#include <cmath>    //sqrt, floor, ceil
#include <iostream>

#include "Stem_env.h"
#include "Var.h"
#include "Point_3d.h"
#include "Line_3d.h"

using namespace std;




Line_3d Stem_env::create_line(int length, int width, int depth, Point_3d box[8], int f2, int d2, int xmin, int xmax, int xdiff1)
{
    int j, x_translate, y_translate, z_translate;
    int ymin, ymax, f2_x2, f2_x2_y2;
    Point_3d start_pt, end_pt;

    j = rand()%8; //random vertex of box
    start_pt.set_x(box[j].get_x());
    start_pt.set_y(box[j].get_y());
    start_pt.set_z(box[j].get_z());

    end_pt.set_x(( rand() % xdiff1 ) + xmin);

    f2_x2 = f2 - (end_pt.get_x() * end_pt.get_x()); // currently origin is assumed as fixed point, so f2_x2 is calculated before adjustment

    //adjustment
    if(start_pt.get_x() != 0)
    {
        end_pt.set_x(length - end_pt.get_x()); //start_pt.x - end_pt.x
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

    end_pt.set_y(( rand() % ((ymax - ymin) + 1) ) + ymin);
    f2_x2_y2 = f2_x2 - (end_pt.get_y() * end_pt.get_y());

    if(start_pt.get_y() != 0)
    {
        end_pt.set_y(width - end_pt.get_y());
    }

    end_pt.set_z(floor(sqrt(f2_x2_y2))); // floor => inside sphere of radius fiber_length, ceil => outside

    if(start_pt.get_z() != 0)
    {
        end_pt.set_z(depth - end_pt.get_z());
    }


    if(start_pt.get_x() == 0)
    {
        x_translate = rand()%((length - end_pt.get_x()) + 1 );
    }
    else
    {
        x_translate = -( rand() % (end_pt.get_x() + 1) );
    }

    if(start_pt.get_y() == 0)
    {
        y_translate = rand()%((width - end_pt.get_y()) + 1 );
    }
    else
    {
        y_translate = -( rand() % (end_pt.get_y() + 1) );
    }

    if(start_pt.get_z() == 0)
    {
        z_translate = rand()%((depth - end_pt.get_z()) + 1 );
    }
    else
    {
        z_translate = -( rand() % (end_pt.get_z() + 1) );
    }

    start_pt.set_x(start_pt.get_x() + x_translate);
    start_pt.set_y(start_pt.get_y() + y_translate);
    start_pt.set_z(start_pt.get_z() + z_translate);
    end_pt.set_x(end_pt.get_x() + x_translate);
    end_pt.set_y(end_pt.get_y() + y_translate);
    end_pt.set_z(end_pt.get_z() + z_translate);
    return draw_3D_line(start_pt, end_pt);
}

Line_3d* Stem_env::setup_environment(int length, int width, int depth, long fiber_count, int fiber_length)
{

    Point_3d box[8];
    Line_3d *lines = new Line_3d[fiber_count];
    long i;
    static long id=0L;
    int f2, d2, xmin, xmax, xdiff1;
    length--;
    depth--;
    width--;
    //Initialize coordinates of box
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

    //seed random number generator with current time
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
        lines[i]=create_line(length, width, depth, box, f2, d2, xmin, xmax, xdiff1);
        lines[i].set_id(id);
        id++;
    }

    return lines;
}

Line_3d Stem_env::draw_3D_line(Point_3d p1, Point_3d p2)
{

    char sign_ind, sign_dep_1, sign_dep_2;

    Var ind_val,dep_val_1,dep_val_2;

    if(abs(p2.get_y()-p1.get_y())>abs(p2.get_x()-p1.get_x()))
    {
        if(abs(p2.get_z()-p1.get_z())>abs(p2.get_y()-p1.get_y()))
        {
            ind_val=*(new Var('z',2,abs(p2.get_z()-p1.get_z()),p1.get_z()));
            sign_ind=((p2.get_z()-p1.get_z())<0)?'-':'+';

            dep_val_1=*(new Var('x',0,abs(p2.get_x()-p1.get_x()),p1.get_x()));
            sign_dep_1=((p2.get_x()-p1.get_x())<0)?'-':'+';

            dep_val_2=*(new Var('y',1,abs(p2.get_y()-p1.get_y()),p1.get_y()));
            sign_dep_2=((p2.get_y()-p1.get_y())<0)?'-':'+';
        }
        else
        {
            ind_val=*(new Var('y',1,abs(p2.get_y()-p1.get_y()),p1.get_y()));
            sign_ind=((p2.get_y()-p1.get_y())<0)?'-':'+';

            dep_val_1=*(new Var('z',2,abs(p2.get_z()-p1.get_z()),p1.get_z()));
            sign_dep_1=((p2.get_z()-p1.get_z())<0)?'-':'+';

            dep_val_2=*(new Var('x',0,abs(p2.get_x()-p1.get_x()),p1.get_x()));
            sign_dep_2=((p2.get_x()-p1.get_x())<0)?'-':'+';
        }
    }
    else
    {
        if (abs(p2.get_z()-p1.get_z())>abs(p2.get_x()-p1.get_x()))
        {
            ind_val=*(new Var('z',2,abs(p2.get_z()-p1.get_z()),p1.get_z()));
            sign_ind=((p2.get_z()-p1.get_z())<0)?'-':'+';

            dep_val_1=*(new Var('x',0,abs(p2.get_x()-p1.get_x()),p1.get_x()));
            sign_dep_1=((p2.get_x()-p1.get_x())<0)?'-':'+';

            dep_val_2=*(new Var('y',1,abs(p2.get_y()-p1.get_y()),p1.get_y()));
            sign_dep_2=((p2.get_y()-p1.get_y())<0)?'-':'+';
        }
        else
        {
            ind_val=*(new Var('x',0,abs(p2.get_x()-p1.get_x()),p1.get_x()));
            sign_ind=((p2.get_x()-p1.get_x())<0)?'-':'+';

            dep_val_1=*(new Var('y',1,abs(p2.get_y()-p1.get_y()),p1.get_y()));
            sign_dep_1=((p2.get_y()-p1.get_y())<0)?'-':'+';

            dep_val_2=*(new Var('z',2,abs(p2.get_z()-p1.get_z()),p1.get_z()));
            sign_dep_2=((p2.get_z()-p1.get_z())<0)?'-':'+';
        }
    }

    Line_3d out_line(ind_val.get_delta()+1);

    int ind_val_f=p2.get_var(ind_val.get_var_name());
    int counter_1=0, counter_2=0;
    int inc_ind, inc_dep_1, inc_dep_2;
    int pt_index=0;
    Point_3d temp_pt;

    inc_ind=(sign_ind=='+')?1:-1;
    inc_dep_1=(sign_dep_1=='+')?1:-1;
    inc_dep_2=(sign_dep_2=='+')?1:-1;

    temp_pt.set_var(ind_val.get_var_name(),ind_val.get_value());
    temp_pt.set_var(dep_val_1.get_var_name(),dep_val_1.get_value());
    temp_pt.set_var(dep_val_2.get_var_name(),dep_val_2.get_value());
    out_line.set_point(pt_index,temp_pt);
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

        temp_pt.set_var(ind_val.get_var_name(),ind_val.get_value());
        temp_pt.set_var(dep_val_1.get_var_name(),dep_val_1.get_value());
        temp_pt.set_var(dep_val_2.get_var_name(),dep_val_2.get_value());
        out_line.set_point(pt_index,temp_pt);
        pt_index++;

    }
    return out_line;

}

long*** Stem_env::generate_pt_freq_map(Line_3d* line,int length, int width, int depth,long fiber_count)
{
    long ***pt_map;
    pt_map=new long**[length];
    for(int i=0;i<length;i++)
    {
        pt_map[i]=new long*[width];
        for(int j=0;j<width;j++)
        {
            pt_map[i][j]=new long[depth];
            for(int k=0;k<depth;k++)
            {
                pt_map[i][j][k]=0;
            }
        }
    }

    for(long i=0;i<fiber_count;i++)
    {
        for(int j=0;j<line[i].get_no_point();j++)
        {
            pt_map[line[i].get_point(j).get_x()][line[i].get_point(j).get_y()][line[i].get_point(j).get_z()]++;
        }
    }

    return pt_map;
}
