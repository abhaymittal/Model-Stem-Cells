#include "Stem_env.h"
#include "Line_3d.h"
#include <iostream>
#include<fstream>
using namespace std;
int main()
{
    Stem_env st;
    Line_3d *line;
    long ***pt_map;
    ofstream output_file("pt_map.xyz");
    int length = 20, width = 20, depth = 20, fiber_count = 1000, fiber_length = 15;

    line=st.setup_environment(length,width,depth,fiber_count,fiber_length);
    pt_map=st.generate_pt_freq_map(line,length,width,depth,fiber_count);

    if(output_file.is_open())
    {
        output_file<<(length*width*depth); //store num of points in .xyz file
        output_file<<"\n"<<"Box Dimensions: length = "<<length<<", width = "<<width<<", depth = "<<depth; //comment line of .xyz file

        for(int x=0;x<length;x++)
        {
            for(int y=0;y<width;y++)
            {
                for(int z=0;z<depth;z++)
                {
                    output_file<<"\n"<<pt_map[x][y][z]<<"\t"<<x<<"\t"<<y<<"\t"<<z;
                }
            }
        }
        output_file.close();
    }

    return 0;
}
