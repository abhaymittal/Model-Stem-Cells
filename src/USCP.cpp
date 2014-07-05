//============================================================================
// Name        : USCP.cpp
// Author      : Sandeep Kumar @IIT Bombay
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "SimulationParameters.h"
#include "ECM.h"
#include "AutomatonCell.h"
#include "Utilities.h"
#include "System.h"
#include <cstdlib>

using namespace std;

int main() {

	/*********Input Parameters***********/
	SimulationParameters sim;
	ECM ecm;
	sim.loadParameters();
    srand(time(NULL));
	int height = sim.getLatticeHeight();
	int width = sim.getLatticeWidth();
	int depth = sim.getLatticeDepth();
	long int fiberCount = sim.getFiberCount();
	int fiberLength = sim.getFiberLength();
    /*****Display Parameters' Value******/

	cout << "height = " << height << endl;
	cout << "width = " << width << endl;
	cout << "depth = " << depth << endl;
    cout << "fiberCount = " << fiberCount << endl;
    cout << "fiberLength = " << fiberLength << endl;


    int cellCount=30;

    AutomatonCell ***environment;
    cout<<"Check"<<endl;
	ecm.setupECM(sim,environment);


    cout<<"Works till here"<<endl;
//    System sys;
//
//    Cell *cells = new Cell[cellCount];
//    sys.createCells(cellCount,1,1,sim,cells,environment);
//    Utilities util;
//    /*******Generate Output file*********/
//    cout<<"Works till here 2"<<endl;
//    util.generateECMFile(sim, environment, util.COUNT);
//    /*Testing for the System class*/

	return 0;

}
