//============================================================================
// Name        : USCP.cpp
// Author      : Sandeep Kumar @IIT Bombay
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "SimulationParameters.h"
#include "Environment.h"
#include "AutomatonCell.h"
#include "Utilities.h"
#include <cstdlib>
#include "Simulation.h"

using namespace std;

int main() {

	/*********Input Parameters***********/
	SimulationParameters sim;
	Environment env;
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


    int cellCount=3000;

    AutomatonCell ***environment;
    environment=new AutomatonCell**[width];
    for(int i=0;i<width;i++) {
        environment[i]=new AutomatonCell*[height];
        for(int j=0;j<height;j++) {
            environment[i][j]=new AutomatonCell[depth];
            for(int k=0;k<depth;k++)
            {
                environment[i][j][k].setCount(0);
                environment[i][j][k].setId(0);
                environment[i][j][k].setType(0);
            }
        }
    }
	env.setupECM(sim,environment);


    Cell *cells = new Cell[cellCount];
    env.createCells(cellCount,1,1,sim,cells,environment);
    Simulation simul;
    for(int itr=0;itr<10000;itr++)
    {
        int opId=simul.findOpId();
        cout<<"Iteration - "<<itr<<endl;
        simul.simulate(sim,environment,cells,opId);
    }

    Utilities util;
    cout<<"Going to generate file"<<endl;
    /*******Generate Output file*********/
    util.generateECMFile(sim, environment, util.COUNT);
    /*Testing for the System class*/

	return 0;

}
