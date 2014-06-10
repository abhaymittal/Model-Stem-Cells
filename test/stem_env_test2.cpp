#include <iostream>
#include <cmath>
#include "../stem_env.h"

using namespace std;

int main()
{
    //args
    int length = 10, width = 20, depth = 30, fiber_count = 25, fiber_length = 15;
    //end args

    Point_3d** lines;
    Stem_env obj;
    lines = obj.setup_environment(length, width, depth, fiber_count, fiber_length);
    int i;

    for(i=0; i<fiber_count; i++)
    {
        cout << "("  << lines[i][0].get_x() << "," << lines[i][0].get_y() << "," << lines[i][0].get_z() << ")  \t----\t(" << lines[i][1].get_x() << "," << lines[i][1].get_y() << "," << lines[i][1].get_z() << ")\n";

        cout << "dist = " << sqrt(((lines[i][1].get_x() - lines[i][0].get_x()) * (lines[i][1].get_x() - lines[i][0].get_x())) + ((lines[i][1].get_y() - lines[i][0].get_y()) * (lines[i][1].get_y() - lines[i][0].get_y())) + ((lines[i][1].get_z() - lines[i][0].get_z()) * (lines[i][1].get_z() - lines[i][0].get_z())) ) << "\n\n";

    }

    return 0;
}
