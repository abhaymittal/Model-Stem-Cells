#include "Simulation_Parameters.h"
#include <iostream>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <libxml++/libxml++.h>

//getter
int Simulation_Parameters::get_length()
{
    return length;
}
int Simulation_Parameters::get_width()
{
    return width;
}
int Simulation_Parameters::get_depth()
{
    return depth;
}
int Simulation_Parameters::get_fiber_length()
{
    return fiber_length;
}
long Simulation_Parameters::get_fiber_count()
{
    return fiber_count;
}

//setter
int Simulation_Parameters::set_length(int _length)
{
    length = _length;
    return 0;
}
int Simulation_Parameters::set_width(int _width)
{
    width = _width;
    return 0;
}
int Simulation_Parameters::set_depth(int _depth)
{
    depth = _depth;
    return 0;
}
int Simulation_Parameters::set_fiber_length(int _fiber_length)
{
    fiber_length = _fiber_length;
    return 0;
}
long Simulation_Parameters::set_fiber_count(long _fiber_count)
{
    fiber_count = _fiber_count;
    return 0;
}

//functions
int Simulation_Parameters::load_XML(std::string input_file)
{
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
    catch(const std::exception& ex)
    {
        std::cout << "Exception: " << ex.what() << std::endl;
        return -1;
    }

    return 0;
}
