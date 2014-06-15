#include "Stem_env.h"
#include "Line_3d.h"
#include "Simulation_Parameters.h"
#include <iostream>
#include<fstream>


using namespace std;
int main(int argc, char* argv[])
{
    Stem_env st;
    Line_3d *line;
    long ***pt_map;
    Simulation_Parameters sim_param;

    string input_file;
    if(argc > 1)
    {
        input_file = argv[1]; //To specify input file as command line argument
    }
    else
    {
        input_file = "input.xml";
    }

    sim_param.load_XML(input_file);

    ofstream output_file("pt_map.xyz");

    line=st.setup_environment(sim_param.get_length(),sim_param.get_width(),sim_param.get_depth(),sim_param.get_fiber_count(),sim_param.get_fiber_length());
    pt_map=st.generate_pt_freq_map(line,sim_param.get_length(),sim_param.get_width(),sim_param.get_depth(),sim_param.get_fiber_count());

    if(output_file.is_open())
    {
        output_file<<(sim_param.get_length()*sim_param.get_width()*sim_param.get_depth()); //store num of points in .xyz file
        output_file<<"\n"<<"Box Dimensions: length = "<<sim_param.get_length()<<", width = "<<sim_param.get_width()<<", depth = "<<sim_param.get_depth(); //comment line of .xyz file

        for(int x=0;x<sim_param.get_length();x++)
        {
            for(int y=0;y<sim_param.get_width();y++)
            {
                for(int z=0;z<sim_param.get_depth();z++)
                {
                    output_file<<"\n"<<pt_map[x][y][z]<<" "<<x<<" "<<y<<" "<<z;
                }
            }
        }
        output_file.close();
    }

    return 0;
}
