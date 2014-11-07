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
#include <deque>

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

    deque<Cell> cells(sim.getCellCount());
    env.createCells(1,1,sim,cells,environment);
    Simulation simul;
    Utilities util;
    int maxIteration = 100;

    util.writeIteration(sim, environment, cells, 0);

    for(int itr=1; itr<=maxIteration; itr++)
    {
        int opId=simul.generateOpId();
        cout<<"Iteration - "<<itr<<endl;
        simul.simulate(sim,environment,cells,opId);
        simul.increaseAge(cells,1,1,sim,environment);
        util.writeIteration(sim, environment, cells, itr);
    }

    cout<<"Going to generate file"<<endl;
    /*******Generate Output file*********/
    util.generateECMFile(sim, environment, util.COUNT);
    /*Testing for the System class*/

    /*Free dynamic memory*/

    for(int i=0;i<width;i++) {
        for(int j=0;j<height;j++) {
            delete[] environment[i][j];
        }
        delete[] environment[i];
    }
    delete[] environment;
	return 0;

}
