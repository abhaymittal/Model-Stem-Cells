#include "SimulationParameters.h"
#include <iostream>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <libxml++/libxml++.h>

SimulationParameters::SimulationParameters() {
	// TODO Auto-generated constructor stub
}

SimulationParameters::~SimulationParameters() {
	// TODO Auto-generated destructor stub
}

void SimulationParameters::loadParameters()
{
    //set default filename
    std::string defaultFile = "uscp.conf";

    //load parameters from default file
    loadParametersFromFile(defaultFile);
}

void SimulationParameters::loadParametersFromFile(std::string filename)
{
    latticeHeight=latticeWidth=latticeDepth=fiberLength=fiberCount=0; //Fix memory Error when file not found
    try
    {
        //create DomParser object to parse xml file
        xmlpp::DomParser parser;

        //parse the xml file whose name is provided as an argument
        parser.parse_file(filename);

        if(parser)
        {
            //get the root node of parsed file
            const xmlpp::Node* rootNode = parser.get_document()->get_root_node();

            //set parameters value by evaluating corresponding xml xpath values
            //Note: returned double value is stored as int
            latticeHeight = rootNode->eval_to_number("//Parameters/Lattice/Height");
            latticeWidth = rootNode->eval_to_number("//Parameters/Lattice/Width");
            latticeDepth = rootNode->eval_to_number("//Parameters/Lattice/Depth");
            fiberLength = rootNode->eval_to_number("//Parameters/FiberLength");
            fiberCount = rootNode->eval_to_number("//Parameters/FiberCount");
            cellCount = rootNode->eval_to_number("//Parameters/CellCount");
            cellDivisionAge = rootNode->eval_to_number("//Parameters/CellDivisionAge");
            maxIteration = rootNode->eval_to_number("//Parameters/MaxIteration");
            alpha = rootNode->eval_to_number("//Parameters/Alpha");
        }
    }
    catch(const std::exception& ex)
    {
        //display exception information
        std::cout << "Exception: " << ex.what() << std::endl;
    }
}
