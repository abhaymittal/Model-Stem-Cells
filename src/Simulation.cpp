#include "Simulation.h"
#include "AutomatonCell.h"
#include "Cell.h"
#include "Point.h"
#include <cmath>
#include <cstdlib>

#define MOVE_CELLS 1
#define UPDATE_EB 2
#define EVOLVE_GENETIC_CODE 3

#include <iostream>
using namespace std;

Simulation::Simulation()
{
    //ctor
}

int Simulation::moveCells(SimulationParameters sim, AutomatonCell ***lattice, std::deque<Cell> &cells)
{
    int num=(2*cells[0].getSenseRadius()+1);
    int neighbourFiber[num][num][num];
    int probabMove;
    int sumFiber=0;
    double mean;
    double mu=0;
    double sigma=1;
    double sigmaSqr=sigma*sigma;

    for(int i=0;i<sim.getCellCount();i++)
    {
        sumFiber=0;
        for(int x=cells[i].getCentroid().getX()-cells[i].getSenseRadius();x<=cells[i].getCentroid().getX()+cells[i].getSenseRadius();x++)
        {
            for(int y=cells[i].getCentroid().getY()-cells[i].getSenseRadius();y<=cells[i].getCentroid().getY()+cells[i].getSenseRadius();y++)
            {
                for(int z=cells[i].getCentroid().getZ()-cells[i].getSenseRadius();z<=cells[i].getCentroid().getZ()+cells[i].getSenseRadius();z++)
                {
                    neighbourFiber[x-cells[i].getCentroid().getX()+cells[i].getSenseRadius()][y-cells[i].getCentroid().getY()+cells[i].getSenseRadius()][z-cells[i].getCentroid().getZ()+cells[i].getSenseRadius()]=lattice[x][y][z].getCount();
                    sumFiber+=lattice[x][y][z].getCount();
                }
            }
        }
        mean=(static_cast<int>(sumFiber))/(num*num*num);
        mu=mean;
        for(int x=0;x<num;x++)
        {
            for(int y=0;y<num;y++)
            {
                for(int z=0;z<num;z++)
                {
                    if((x<sim.getFiberLength())||(x>(sim.getLatticeWidth()-sim.getFiberLength()))||(y<sim.getFiberLength())||(y>(sim.getLatticeWidth()-sim.getFiberLength()))||(z<sim.getFiberLength())||(z>(sim.getLatticeWidth()-sim.getFiberLength())))
                        continue;
                    double exponent=-1*(neighbourFiber[x][y][z]-mu)*(neighbourFiber[x][y][z]-mu)/(2*sigmaSqr);
                    probabMove=exp(exponent);
                    double r =(static_cast<double>(rand()%100))/100;
                    if(r<probabMove)
                    {
                        //Remove cell from current location (lattice DB)
                        lattice[cells[i].getCentroid().getX()][cells[i].getCentroid().getY()][cells[i].getCentroid().getZ()].setType(1);
                        lattice[cells[i].getCentroid().getX()][cells[i].getCentroid().getY()][cells[i].getCentroid().getZ()].setId(0);
                        lattice[cells[i].getCentroid().getX()][cells[i].getCentroid().getY()][cells[i].getCentroid().getZ()].setCount(0);

                        //Reset cell centroid
                        Point p(x+cells[i].getCentroid().getX()-cells[i].getSenseRadius(),y+cells[i].getCentroid().getY()-cells[i].getSenseRadius(),z+cells[i].getCentroid().getZ()-cells[i].getSenseRadius());
                        cells[i].setCentroid(p);

                        //Move cell to new location (lattice DB)
                        lattice[p.getX()][p.getY()][p.getZ()].setType(2);
                        lattice[p.getX()][p.getY()][p.getZ()].setId(cells[i].getId());
                        lattice[p.getX()][p.getY()][p.getZ()].setCount(0);

                        //exit the loop (goto used to avoid checking flags)
                        goto cellMoved;
                    }
                }
            }
            cellMoved:;
        }
    }
    return 0;
}

int Simulation::updateEB(SimulationParameters sim, AutomatonCell ***lattice, std::deque<Cell> &cells)
{
    int k=14;
    int sumFiber=0;
    float totalNeighbourEC=0;
    float EBNew;
    int totalNeighbours=(2*cells[0].getSenseRadius()+1)*(2*cells[0].getSenseRadius()+1)*(2*cells[0].getSenseRadius()+1);
    for(int i=0;i<sim.getCellCount();i++)
    {
        sumFiber=0;
        for(int x=cells[i].getCentroid().getX()-cells[i].getSenseRadius();x<=cells[i].getCentroid().getX()+cells[i].getSenseRadius();x++)
        {
            for(int y=cells[i].getCentroid().getY()-cells[i].getSenseRadius();y<=cells[i].getCentroid().getY()+cells[i].getSenseRadius();y++)
            {
                for(int z=cells[i].getCentroid().getZ()-cells[i].getSenseRadius();z<=cells[i].getCentroid().getZ()+cells[i].getSenseRadius();z++)
                {
                    sumFiber+=lattice[x][y][z].getCount();
                    if(lattice[x][y][z].getType()==2)
                    {
                        //Cell index in array = id -1 as id was created using index +1 in createCells (Environment.h)
                        totalNeighbourEC+=cells[lattice[x][y][z].getId()-1].getECadherin();
                    }
                }
            }
        }
        EBNew=((static_cast<float>(sumFiber))/(sumFiber+k))+(totalNeighbourEC/totalNeighbours);
        cells[i].setEB(EBNew);
    }
    return 0;
}

int Simulation::simulate(SimulationParameters sim, AutomatonCell ***lattice, std::deque<Cell> &cells, int opId)
{
    cout<<"OPID => "<<opId<<endl;
    switch(opId)
    {
        case MOVE_CELLS:
            moveCells(sim,lattice,cells);
            break;

        case UPDATE_EB:
            updateEB(sim,lattice,cells);
            break;

        case EVOLVE_GENETIC_CODE:
            evolveGeneticCode(sim,cells);
            break;
    }
    return 0;
}

int Simulation::generateOpId()
{
    double r=(static_cast<double>(rand()%100))/100;
    if(r<(1.0/3))
        return MOVE_CELLS;
    else if ((r>=(1.0/3))&&(r<(2.0/3)))
        return UPDATE_EB;
    else
        return EVOLVE_GENETIC_CODE;
}
int Simulation::evolveGeneticCode(SimulationParameters sim,std::deque<Cell> &cells)
{
    for(int i=0;i<sim.getCellCount();i++)
    {
        cells[i].setGeneticCode(0, cells[i].getGeneticCode(0) & cells[i].getGeneticCode(1) );
        cells[i].setGeneticCode(1, cells[i].getGeneticCode(1) | cells[i].getGeneticCode(2) );
        cells[i].setGeneticCode(2, !(cells[i].getGeneticCode(2)) );
    }
    return 0;
}
