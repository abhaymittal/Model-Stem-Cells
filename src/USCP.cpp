//============================================================================
// Name        : USCP.cpp
// Author      : Sandeep Kumar @IIT Bombay
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include "SimulationParameters.h"
#include "ECM.h"
#include "AutomatonCell.h"

using namespace std;

int main() {

	/*********Input Parameters***********/
	SimulationParameters sim;
	ECM ecm;
	sim.loadParameters();

	int height = sim.getLatticeHeight();
	int width = sim.getLatticeWidth();
	int depth = sim.getLatticeDepth();

	long int fiberCount = sim.getFiberCount();
	int fiberLength = sim.getFiberLength();

	AutomatonCell ***environment;
	environment=ecm.setupECM(sim);

    /*****Display Parameters' Value*******/

	cout << "height = " << height << endl;
	cout << "width = " << width << endl;
	cout << "depth = " << depth << endl;
    cout << "fiberCount = " << fiberCount << endl;
    cout << "fiberLength = " << fiberLength << endl;

    ofstream outputFile("ptMap.xyz");

    if(outputFile.is_open())
    {
        outputFile<<(sim.getLatticeWidth() * sim.getLatticeHeight() * sim.getLatticeDepth()); //store num of points in .xyz file
        outputFile<<"\n"<<"Box Dimensions: width = "<<sim.getLatticeWidth()<<", height = "<<sim.getLatticeHeight()<<", depth = "<<sim.getLatticeDepth(); //comment line of .xyz file

        for(int x=0;x<sim.getLatticeWidth();x++)
        {
            for(int y=0;y<sim.getLatticeHeight();y++)
            {
                for(int z=0;z<sim.getLatticeDepth();z++)
                {
                    outputFile<<"\n"<<environment[x][y][z].getCount()<<" "<<x<<" "<<y<<" "<<z;
                }
            }
        }
        outputFile.close();
        cout << "\nOutput file saved\n";
    }
    else
    {
        cout << "Error in saving output file\n";
    }

	return 0;

}
