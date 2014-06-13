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
    ofstream output_file("pt_map.tsv");
    line=st.setup_environment(20,20,20,1000,15);
    pt_map=st.generate_pt_freq_map(line,20,20,20,1000);

    if(output_file.is_open())
    {
        for(int x=0;x<20;x++)
        {
            for(int y=0;y<20;y++)
            {
                for(int z=0;z<20;z++)
                {
                    output_file<<pt_map[x][y][z]<<"\t"<<x<<"\t"<<y<<"\t"<<z<<endl;
                }
            }
        }
        output_file.close();
    }

    return 0;
}
