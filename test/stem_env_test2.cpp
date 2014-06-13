#include <iostream>
#include <cmath>
#include "../include/Stem_env.h"

using namespace std;

int main()
{
    //args
    int length = 10, width = 20, depth = 30, fiber_count = 25, fiber_length = 15;
    //end args

    Line_3d* lines;
    Point_3d start_pt, end_pt;
    Stem_env obj;
    lines = obj.setup_environment(length, width, depth, fiber_count, fiber_length);
    int i;

    for(i=0; i<fiber_count; i++)
    {
        start_pt = lines[i].get_point(0);
        end_pt = lines[i].get_point(lines[i].get_no_point()-1);

        cout << "("  << start_pt.get_x() << "," << start_pt.get_y() << "," << start_pt.get_z() << ")  \t----\t(" << end_pt.get_x() << "," << end_pt.get_y() << "," << end_pt.get_z() << ")\n";

        cout << "dist = " << sqrt(((end_pt.get_x() - start_pt.get_x()) * (end_pt.get_x() - start_pt.get_x())) + ((end_pt.get_y() - start_pt.get_y()) * (end_pt.get_y() - start_pt.get_y())) + ((end_pt.get_z() - start_pt.get_z()) * (end_pt.get_z() - start_pt.get_z())) ) << "\n\n";

    }

    return 0;
}
