#include <ctime>    //time
#include <cstdlib>  //rand, srand
#include <cmath>    //sqrt, floor, ceil

#include <iostream>

using namespace std;

class Point_3d
{
private:
    int x;
    int y;
    int z;

public:
    int get_x();
    int get_y();
    int get_z();

    int set_x(int xval);
    int set_y(int yval);
    int set_z(int zval);
};

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

int create_line(int i, Point_3d box[8], Point_3d lines[][2], int f2, int d2, int xmin, int xmax, int xdiff1, int length, int width, int depth);

int main()
{
    //args
    int length = 10, width = 20, depth = 30, fiber_count = 25, fiber_length = 15;

    //function

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

    cout << "BOX vertices:\n";

    for(i=0; i<8; i++)
    {
        cout << "("  << box[i].get_x() << "," << box[i].get_y() << "," << box[i].get_z() << ")\n";
    }

    cout << "\n\nLines:\n";

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


int create_line(int i, Point_3d box[8], Point_3d lines[][2], int f2, int d2, int xmin, int xmax, int xdiff1, int length, int width, int depth)
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

    cout << "("  << lines[i][0].get_x() << "," << lines[i][0].get_y() << "," << lines[i][0].get_z() << ")  \t----\t(" << lines[i][1].get_x() << "," << lines[i][1].get_y() << "," << lines[i][1].get_z() << ")\n";

    cout << "dist = " << sqrt(((lines[i][1].get_x() - lines[i][0].get_x()) * (lines[i][1].get_x() - lines[i][0].get_x())) + ((lines[i][1].get_y() - lines[i][0].get_y()) * (lines[i][1].get_y() - lines[i][0].get_y())) + ((lines[i][1].get_z() - lines[i][0].get_z()) * (lines[i][1].get_z() - lines[i][0].get_z())) ) << "\n\n";

    return 0;
}

