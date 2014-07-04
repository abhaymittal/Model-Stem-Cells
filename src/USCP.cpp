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
	ecm.setupECM(sim,environment);

    /*****Display Parameters' Value******/

	cout << "height = " << height << endl;
	cout << "width = " << width << endl;
	cout << "depth = " << depth << endl;
    cout << "fiberCount = " << fiberCount << endl;
    cout << "fiberLength = " << fiberLength << endl;

    System sys;
    sys.setupCells(30,1,1,sim);
    Pixel ***pxlMap;
    sys.getPixelArray(pxlMap);
    AutomatonCell ***maps;
    Utilities util;
    cout<<"To merge"<<endl;
    util.mergeCellECM(maps,environment,pxlMap,sim);
    cout<<"Merged";

    /*******Generate Output file*********/


    util.generateECMFile(sim, maps, util.COUNT);
    /*Testing for the System class*/

	return 0;

}
