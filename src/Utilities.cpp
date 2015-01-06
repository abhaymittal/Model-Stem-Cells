#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Utilities::Utilities() {
	// TODO Auto-generated constructor stub

}

Utilities::~Utilities() {
	// TODO Auto-generated destructor stub
}

using namespace std;

void Utilities::generateECMFile(SimulationParameters sim, AutomatonCell ***environment, int field)
{
	//field = 1, type
	//field = 2, count
	//field = 3, ID

    switch(field)
    {
        case COUNT:
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
                           // if(environment[x][y][z].getType()!=AutomatonCell::EMPTY)
                                outputFile<<"\n"<<environment[x][y][z].getType()<<" "<<x<<" "<<y<<" "<<z<<" "<<environment[x][y][z].getCount();
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
        break;
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
        int* cellAge = new int[(cells.back()).getId()+1](); // array of zeroes
        for(std::deque<Cell>::iterator it = cells.begin(); it!=cells.end(); it++)
        {
            cellAge[it->getId()]=it->getAge();
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
                        outputFile << cellAge[environment[x][y][z].getId()] << "\n";
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
        delete[] cellAge;
    }
    else
    {
        cout << "Error in saving " << filename << "\n";
        return -1;
    }

    return 0;
}
