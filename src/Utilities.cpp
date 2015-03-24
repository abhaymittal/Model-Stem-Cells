#include "Utilities.h"
#include <iostream>
#include <fstream>
#include<map>
#include <string>
#include <sstream>

Utilities::Utilities() {
	// TODO Auto-generated constructor stub

}

Utilities::~Utilities() {
	// TODO Auto-generated destructor stub
}

using namespace std;

void Utilities::generateECMFile(SimulationParameters sim, AutomatonCell ***environment, int field, int iterationNumber)
{
	//field = 1, type
	//field = 2, count
	//field = 3, ID

	string filename;
    stringstream ss;
    ss << "iterations/iter.csv." << iterationNumber;
    filename = ss.str();
    ofstream outputFile(filename.c_str());

    if(outputFile.is_open())
    {
        switch(field)
        {
            case COUNT:

                outputFile<< "count,x,y,z";

                for(int x=0;x<sim.getLatticeWidth();x++)
                {
                    for(int y=0;y<sim.getLatticeHeight();y++)
                    {
                        for(int z=0;z<sim.getLatticeDepth();z++)
                        {
                           // if(environment[x][y][z].getType()!=AutomatonCell::EMPTY)
                                outputFile<<"\n"<<environment[x][y][z].getCount()<<","<<x<<","<<y<<","<<z;
                        }
                    }
                }
            break;

            case TYPE:

                outputFile<< "type,x,y,z";

                for(int x=0;x<sim.getLatticeWidth();x++)
                {
                    for(int y=0;y<sim.getLatticeHeight();y++)
                    {
                        for(int z=0;z<sim.getLatticeDepth();z++)
                        {
                           // if(environment[x][y][z].getType()!=AutomatonCell::EMPTY)
                                outputFile<<"\n"<<environment[x][y][z].getType()<<","<<x<<","<<y<<","<<z;
                        }
                    }
                }
            break;

            case ID:

                outputFile<< "id,x,y,z";

                for(int x=0;x<sim.getLatticeWidth();x++)
                {
                    for(int y=0;y<sim.getLatticeHeight();y++)
                    {
                        for(int z=0;z<sim.getLatticeDepth();z++)
                        {
                           // if(environment[x][y][z].getType()!=AutomatonCell::EMPTY)
                                outputFile<<"\n"<<environment[x][y][z].getId()<<","<<x<<","<<y<<","<<z;
                        }
                    }
                }
            break;
        }
        outputFile.close();
        cout << "\nOutput file saved\n";
    }
    else
    {
        cout << "Error in saving output file\n";
    }
}

int Utilities::writeIteration(SimulationParameters sim, AutomatonCell ***environment, std::deque<Cell> &cells, int iterationNumber)
{
    string filename;
    stringstream ss;
    ss << "iterations/" << iterationNumber << ".txt";
    filename = ss.str();
    ofstream outputFile(filename.c_str());

    if(outputFile.is_open())
    {
        //Map cellId to corresponding cellAge
        std::map<long long int, int> idToAgeMap;
        for(std::deque<Cell>::iterator it = cells.begin(); it!=cells.end(); it++)
        {
            idToAgeMap[it->getId()]=it->getAge();
        }

        //write to file
        for(int x=0;x<sim.getLatticeWidth();x++)
        {
            for(int y=0;y<sim.getLatticeHeight();y++)
            {
                for(int z=0;z<sim.getLatticeDepth();z++)
                {
                    outputFile << x << "," << y << "," << z <<"," << environment[x][y][z].getType() << "," << environment[x][y][z].getId() << ",";
                    if(environment[x][y][z].getType()==AutomatonCell::CELL)
                    {
                        outputFile <<idToAgeMap[environment[x][y][z].getId()] << "\n";
                    }
                    else
                    {
                        outputFile << "-1" << "\n";
                    }
                }
            }
        }
        outputFile.close();
        cout << "\n" << filename << " saved\n";
    }
    else
    {
        cout << "Error in saving " << filename << "\n";
        return -1;
    }

    return 0;
}
