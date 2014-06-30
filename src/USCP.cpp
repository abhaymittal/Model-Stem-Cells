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

    /*****Display Parameters' Value******/

	cout << "height = " << height << endl;
	cout << "width = " << width << endl;
	cout << "depth = " << depth << endl;
    cout << "fiberCount = " << fiberCount << endl;
    cout << "fiberLength = " << fiberLength << endl;

    /*******Generate Output file*********/

    Utilities util;
    util.generateECMFile(sim, environment, util.COUNT);

	return 0;

}
