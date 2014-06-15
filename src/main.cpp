#include "Stem_env.h"
#include "Line_3d.h"
#include <iostream>
#include<fstream>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <libxml++/libxml++.h>

using namespace std;
int main(int argc, char* argv[])
{
    Stem_env st;
    Line_3d *line;
    long ***pt_map;
    int length, width, depth, fiber_length;
    long fiber_count;

    //Loading XML file

    string input_file;
    if(argc > 1)
    {
        input_file = argv[1]; //To specify input file as command line argument
    }
    else
    {
        input_file = "input.xml";
    }

    try
    {
        xmlpp::DomParser parser;
        parser.parse_file(input_file);
        if(parser)
        {
            const xmlpp::Node* pNode = parser.get_document()->get_root_node();

            length = pNode->eval_to_number("//Parameters/Lattice/Length"); //returned double value is stored as int
            width = pNode->eval_to_number("//Parameters/Lattice/Width");
            depth = pNode->eval_to_number("//Parameters/Lattice/Depth");
            fiber_length = pNode->eval_to_number("//Parameters/FiberLength");
            fiber_count = pNode->eval_to_number("//Parameters/FiberCount");
        }
    }
    catch(const exception& ex)
    {
        cout << "Exception: " << ex.what() << endl;
    }

    //End Loading XML file

    ofstream output_file("pt_map.xyz");

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
