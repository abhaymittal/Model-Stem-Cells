/*
 * SimulationParameters.cpp
 *
 *  Created on: Jun 17, 2014
 *      Author: sandeep
 */

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
    try
    {
        //create DomParser object to parse xml file
        xmlpp::DomParser parser;

        //parse the xml file whose name is provided as an argument
        parser.parse_file(filename);

        //check if parser is not NULL (i.e. a valid xml file is parsed)
        if(parser)
        {
            //get the root node of parsed file
            const xmlpp::Node* rootNode = parser.get_document()->get_root_node();

            //set parameters value by evaluating corresponding xml xpath values
            //Note: returned double value is stored as int
            latticeHeight = rootNode->eval_to_number("//Parameters/Lattice/Length");
            latticeWidth = rootNode->eval_to_number("//Parameters/Lattice/Width");
            latticeDepth = rootNode->eval_to_number("//Parameters/Lattice/Depth");
            fiberLength = rootNode->eval_to_number("//Parameters/FiberLength");
            fiberCount = rootNode->eval_to_number("//Parameters/FiberCount");
        }
    }
    catch(const std::exception& ex)
    {
        //display exception information
        std::cout << "Exception: " << ex.what() << std::endl;
    }
}
