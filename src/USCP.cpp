#include <iostream>
#include "SimulationParameters.h"
#include "Environment.h"
#include "AutomatonCell.h"
#include "Utilities.h"
#include "StemCell.h"
#include "TACell.h"
#include "global.h"
#include <cstdlib>
#include "Simulation.h"
#include <deque>

#include <fstream>

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
	int maxIteration = sim.getMaxIteration();
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
                environment[i][j][k].setType(AutomatonCell::EMPTY);
            }
        }
    }
	env.setupECM(sim,environment);

	cellGroup cells;
	cells.normalCell.resize(sim.getCellCount());

    env.createCells(1,1,sim,cells.normalCell,environment);
    Simulation simul;
    Utilities util;

    //util.writeIteration(sim, environment, cells.normalCell, 0);

    int numcells = cells.normalCell.size();

    int kval = 20;
    int arr[kval];
    int tmp_val;
    int found;
    for(int i=0; i<kval; )
    {
        tmp_val = rand() % numcells;
        found=0;
        for(int j=0; j<i; j++)
        {
            if(arr[j]==tmp_val)
            {
                found=1;
                break;
            }
        }
        if(found)
        {
            continue;
        }
        else
        {
            arr[i]=tmp_val;
            i++;
        }
    }
    cout << "RANDOM : ";
    for(int i=0; i<kval; i++)
        cout << arr[i] << ',';
    cout << endl;
    maxIteration = 1600;

    ofstream cell_vs_time("cell_vs_time.csv");
    ofstream evt("avg_eb_vs_time.csv");
    ofstream avg_k("avg_k.csv");
    cell_vs_time << 0 << "," << cells.normalCell.size() << endl;

    double sumEB = 0.0;
    for(std::deque<Cell>::iterator it = cells.normalCell.begin(); it!=cells.normalCell.end(); it++)
        sumEB += (it->getEB());

    evt << 0 << "," << sumEB/cells.normalCell.size() << endl;

    avg_k << 0;
    for(int i=0; i<kval; i++)
    {
        avg_k << ',' << cells.normalCell[i].getEB();
    }
    avg_k << endl;

    for(int itr=1; itr<=maxIteration; itr++)
    {
        int opId=simul.generateOpId();
        cout<<"Iteration - "<<itr<<endl;
        simul.simulate(sim,environment,cells.normalCell,opId);
        simul.increaseAge(cells,1,1,sim,environment);
        //util.writeIteration(sim, environment, cells.normalCell, itr);
        cell_vs_time << itr << "," << cells.normalCell.size() << endl;

        sumEB = 0.0;
        for(std::deque<Cell>::iterator it = cells.normalCell.begin(); it!=cells.normalCell.end(); it++)
            sumEB += (it->getEB());

        evt << itr << "," << sumEB/cells.normalCell.size() << endl;

        avg_k << itr;
        for(int i=0; i<kval; i++)
        {
            avg_k << ',' << cells.normalCell[i].getEB();
        }
        avg_k << endl;
    }
    cell_vs_time.close();

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
