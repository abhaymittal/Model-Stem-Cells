/*
 * Utilities.cpp
 *
 *  Created on: Jun 18, 2014
 *      Author: sandeep
 */

#include "Utilities.h"
#include <iostream>
#include <fstream>

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

int Utilities::mergeCellECM(AutomatonCell ***ptFreqMap,AutomatonCell ***ecm,Pixel ***pixels, SimulationParameters sim)
{
    ptFreqMap=new AutomatonCell**[sim.getLatticeWidth()];
    for(int i=0;i<sim.getLatticeWidth();i++)
    {
        ptFreqMap[i]=new AutomatonCell*[sim.getLatticeHeight()];
        for(int j=0;j<sim.getLatticeHeight();j++)
        {
            ptFreqMap[i][j]=new AutomatonCell[sim.getLatticeDepth()];
        }
    }
    cout<<"Array creatae"<<endl;

    for(int x=0;x<sim.getLatticeWidth();x++)
    {
        for(int y=0;y<sim.getLatticeHeight();y++)
        {
            for(int z=0;z<sim.getLatticeDepth();z++)
            {
                cout<<x<<" "<<y<<" "<<z<<endl;
                if(pixels[x][y][z].getCellID()==-1)
                {
                    ptFreqMap[x][y][z].setCount(ecm[x][y][z].getCount());
                    if(ecm[x][y][z].getCount()!=0)
                        ptFreqMap[x][y][z].setType(1);
                }
                else
                {
                    ptFreqMap[x][y][z].setId(pixels[x][y][z].getCellID());
                    ptFreqMap[x][y][z].setType(2);
                    cout<<"check"<<endl;
                }
            }
        }
    }
return 0;
}

