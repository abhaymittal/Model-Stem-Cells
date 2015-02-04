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
#include <ctime>    //time
#include <cstdlib>  //rand
#include <cmath>    //sqrt, floor, ceil

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

	int sphereRadius = 20;
	int cellRadius = 1;
	env.clearSphericalRegion(sim.getLatticeWidth()/2, sim.getLatticeHeight()/2, sim.getLatticeDepth()/2, sphereRadius, environment);

	cellGroup cells;
	/*cells.normalCell.resize(sim.getCellCount());
    env.createCells(1,1,sim,cells.normalCell,environment);*/

    double randTheta=(rand()%360)*PI/180;
    double randPhi=(rand()%360)*PI/180;
    int dist = sphereRadius - cellRadius; //distance between centers of the sphere and a cell attached to its boundary

    int x=(int)((sim.getLatticeWidth()/2)+dist*sin(randTheta)*cos(randPhi));
    int y=(int)((sim.getLatticeHeight()/2)+dist*sin(randTheta)*sin(randPhi));
    int z=(int)((sim.getLatticeDepth()/2)+dist*cos(randTheta));

    env.insertCell(cellRadius,1,Point(x,y,z),sim, AutomatonCell::STEM_CELL,environment,cells);

    Simulation simul;
    Utilities util;


    //util.writeIteration(sim, environment, cells.normalCell, 0);

    /* collecting data for plotting vs time(iteration) */

    long long numStemCells = 0;
    long long numTACells = 0;
    long long numNormalCells = 0;
    long long numTotalCells = 0;
    double averageEB = 0.0;
    long long totalECMFiber = 0;

    ofstream numStemCellsFile("log/numStemCells.csv");
    ofstream numTACellsFile("log/numTACells.csv");
    ofstream numNormalCellsFile("log/numNormalCells.csv");
    ofstream numTotalCellsFile("log/numTotalCells.csv");
    ofstream averageEBFile("log/averageEB.csv");
    ofstream totalECMFiberFile("log/totalECMFiber.csv");

    numStemCells = cells.stemCell.size();
    numTACells = cells.taCell.size();
    numNormalCells = cells.normalCell.size();
    numTotalCells = numStemCells + numTACells + numNormalCells;

    double sumEB = 0.0;
    for(std::deque<StemCell>::iterator it = cells.stemCell.begin(); it!=cells.stemCell.end(); it++)
        sumEB += (it->getEB());
    for(std::deque<TACell>::iterator it = cells.taCell.begin(); it!=cells.taCell.end(); it++)
        sumEB += (it->getEB());
    for(std::deque<Cell>::iterator it = cells.normalCell.begin(); it!=cells.normalCell.end(); it++)
        sumEB += (it->getEB());

    averageEB = sumEB/numTotalCells;

    for(int i=0;i<width;i++) {
        for(int j=0;j<height;j++) {
            for(int k=0;k<depth;k++){
                if(environment[i][j][k].getType() == AutomatonCell::ECM) totalECMFiber++;
            }
        }
    }

    numStemCellsFile << 0 << "," << numStemCells << endl;
    numTACellsFile << 0 << "," << numTACells << endl;
    numNormalCellsFile << 0 << "," << numNormalCells << endl;
    numTotalCellsFile << 0 << "," << numTotalCells << endl;
    averageEBFile << 0 << "," << averageEB << endl;
    totalECMFiberFile << 0 << "," << totalECMFiber << endl;

    /* End data collection for 0th iteration */
    util.generateECMFile(sim, environment, Utilities::TYPE, 0);

    for(int itr=1; itr<=maxIteration; itr++)
    {
        int opId=simul.generateOpId();
        cout<<"Iteration - "<<itr<<endl;
        simul.simulate(sim,environment,cells,opId);
        simul.increaseAge(cells,1,1,sim,environment);
        //util.writeIteration(sim, environment, cells.normalCell, itr);

        /* collecting data for plotting vs time(iteration) */

        /* Reset values */
        numStemCells = 0;
        numTACells = 0;
        numNormalCells = 0;
        numTotalCells = 0;
        averageEB = 0.0;
        totalECMFiber = 0;

        numStemCells = cells.stemCell.size();
        numTACells = cells.taCell.size();
        numNormalCells = cells.normalCell.size();
        numTotalCells = numStemCells + numTACells + numNormalCells;

        sumEB = 0.0;
        for(std::deque<StemCell>::iterator it = cells.stemCell.begin(); it!=cells.stemCell.end(); it++)
            sumEB += (it->getEB());
        for(std::deque<TACell>::iterator it = cells.taCell.begin(); it!=cells.taCell.end(); it++)
            sumEB += (it->getEB());
        for(std::deque<Cell>::iterator it = cells.normalCell.begin(); it!=cells.normalCell.end(); it++)
            sumEB += (it->getEB());

        averageEB = sumEB/numTotalCells;

        for(int i=0;i<width;i++) {
            for(int j=0;j<height;j++) {
                for(int k=0;k<depth;k++){
                    if(environment[i][j][k].getType() == AutomatonCell::ECM) totalECMFiber++;
                }
            }
        }

        numStemCellsFile << itr << "," << numStemCells << endl;
        numTACellsFile << itr << "," << numTACells << endl;
        numNormalCellsFile << itr << "," << numNormalCells << endl;
        numTotalCellsFile << itr << "," << numTotalCells << endl;
        averageEBFile << itr << "," << averageEB << endl;
        totalECMFiberFile << itr << "," << totalECMFiber << endl;

        /* End data collection for ith iteration */
        //util.generateECMFile(sim, environment, Utilities::TYPE, itr);
    }

    /* close data collection files */
    numStemCellsFile.close();
    numStemCellsFile.close();
    numTACellsFile.close();
    numNormalCellsFile.close();
    numTotalCellsFile.close();
    averageEBFile.close();
    totalECMFiberFile.close();

    cout<<"Going to generate file"<<endl;
    /*******Generate Output file*********/
  //util.generateECMFile(sim, environment, Utilities::COUNT, maxIteration);

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
