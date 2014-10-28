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
    int i,j,k,x,y,z;
    for(std::deque<Cell>::iterator it = cells.begin(); it!=cells.end(); it++)
    {
        sumFiber=0;
        for(x=it->getCentroid().getX()-it->getSenseRadius();x<=it->getCentroid().getX()+it->getSenseRadius();x++)
        {
            for(y=it->getCentroid().getY()-it->getSenseRadius();y<=it->getCentroid().getY()+it->getSenseRadius();y++)
            {
                for(z=it->getCentroid().getZ()-it->getSenseRadius();z<=it->getCentroid().getZ()+it->getSenseRadius();z++)
                {
                    neighbourFiber[x-it->getCentroid().getX()+it->getSenseRadius()][y-it->getCentroid().getY()+it->getSenseRadius()][z-it->getCentroid().getZ()+it->getSenseRadius()]=lattice[x][y][z].getCount();
                    sumFiber+=lattice[x][y][z].getCount();
                }
            }
        }
        mean=(static_cast<int>(sumFiber))/(num*num*num);
        mu=mean;
        for(i=0;i<num;i++)
        {
            for(j=0;j<num;j++)
            {
                for(k=0;k<num;k++)
                {
                    x=i+it->getCentroid().getX()-it->getSenseRadius();
                    y=j+it->getCentroid().getY()-it->getSenseRadius();
                    z=k+it->getCentroid().getZ()-it->getSenseRadius();

                    if((x<sim.getFiberLength())||(x>(sim.getLatticeWidth()-sim.getFiberLength()))||(y<sim.getFiberLength())||(y>(sim.getLatticeWidth()-sim.getFiberLength()))||(z<sim.getFiberLength())||(z>(sim.getLatticeWidth()-sim.getFiberLength())))
                        continue;
                    double exponent=-1*(neighbourFiber[i][j][k]-mu)*(neighbourFiber[i][j][k]-mu)/(2*sigmaSqr);
                    probabMove=exp(exponent);
                    double r =(static_cast<double>(rand()%100))/100; //Generate a normalized random number
                    if(r<probabMove)
                    {
                        //Remove cell from current location (lattice DB)
                        lattice[it->getCentroid().getX()][it->getCentroid().getY()][it->getCentroid().getZ()].setType(1);
                        lattice[it->getCentroid().getX()][it->getCentroid().getY()][it->getCentroid().getZ()].setId(0);
                        lattice[it->getCentroid().getX()][it->getCentroid().getY()][it->getCentroid().getZ()].setCount(0);

                        //Reset cell centroid
                        Point p(x,y,z);
                        it->setCentroid(p);

                        //Move cell to new location (lattice DB)
                        lattice[p.getX()][p.getY()][p.getZ()].setType(2);
                        lattice[p.getX()][p.getY()][p.getZ()].setId(it->getId());
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
    for(std::deque<Cell>::iterator it = cells.begin(); it!=cells.end(); it++)
    {
        sumFiber=0;
        for(int x=it->getCentroid().getX()-it->getSenseRadius();x<=it->getCentroid().getX()+it->getSenseRadius();x++)
        {
            for(int y=it->getCentroid().getY()-it->getSenseRadius();y<=it->getCentroid().getY()+it->getSenseRadius();y++)
            {
                for(int z=it->getCentroid().getZ()-it->getSenseRadius();z<=it->getCentroid().getZ()+it->getSenseRadius();z++)
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
        it->setEB(EBNew);
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
    for(std::deque<Cell>::iterator it = cells.begin(); it!=cells.end(); it++)
    {
        it->setGeneticCode(0, it->getGeneticCode(0) & it->getGeneticCode(1) );
        it->setGeneticCode(1, it->getGeneticCode(1) | it->getGeneticCode(2) );
        it->setGeneticCode(2, !(it->getGeneticCode(2)) );
    }
    return 0;
}


int Simulation::increaseAge(std::deque<Cell>& cells, int radius, int senseRadius, SimulationParameters sim, AutomatonCell ***environment) {
    long int lastId = cells.back().getId();
    cout<<"Got last id"<<endl;
    for(std::deque<Cell>::iterator it = cells.begin(); it->getId()!=lastId; it++) {
            if(it->incrementAge()>30) {
                it->setAge(0);
                splitCell(*it,cells,environment,radius,senseRadius,sim);

            }
    }
}

int Simulation::splitCell(Cell& agedCell, std::deque<Cell>& cells, AutomatonCell ***environment, int radius, int senseRadius, SimulationParameters sim) {
    int num=(2*cells[0].getSenseRadius()+1);
    int neighbourFiber[num][num][num];
    int probabNew;
    int sumFiber=0;
    double mean;
    double mu=0;
    double sigma=1;
    double sigmaSqr=sigma*sigma;
    int i,j,k,x,y,z;

    for(x=agedCell.getCentroid().getX()-agedCell.getSenseRadius();x<=agedCell.getCentroid().getX()+agedCell.getSenseRadius();x++)
    {
        for(y=agedCell.getCentroid().getY()-agedCell.getSenseRadius();y<=agedCell.getCentroid().getY()+agedCell.getSenseRadius();y++)
        {
            for(z=agedCell.getCentroid().getZ()-agedCell.getSenseRadius();z<=agedCell.getCentroid().getZ()+agedCell.getSenseRadius();z++)
            {
                neighbourFiber[x-agedCell.getCentroid().getX()+agedCell.getSenseRadius()][y-agedCell.getCentroid().getY()+agedCell.getSenseRadius()][z-agedCell.getCentroid().getZ()+agedCell.getSenseRadius()]=environment[x][y][z].getCount();
                sumFiber+=environment[x][y][z].getCount();
            }
        }
    }

    mean=(static_cast<int>(sumFiber))/(num*num*num);
    mu=mean;
    for(i=0;i<num;i++)
    {
        for(j=0;j<num;j++)
        {
            for(k=0;k<num;k++)
            {
                x=i+agedCell.getCentroid().getX()-agedCell.getSenseRadius();
                y=j+agedCell.getCentroid().getY()-agedCell.getSenseRadius();
                z=k+agedCell.getCentroid().getZ()-agedCell.getSenseRadius();
                if((x<sim.getFiberLength())||(x>(sim.getLatticeWidth()-sim.getFiberLength()))||(y<sim.getFiberLength())||(y>(sim.getLatticeWidth()-sim.getFiberLength()))||(z<sim.getFiberLength())||(z>(sim.getLatticeWidth()-sim.getFiberLength())))
                    continue;
                if((environment[x][y][z].getType()==2))
                        continue;
                double exponent=-1*(neighbourFiber[i][j][k]-mu)*(neighbourFiber[i][j][k]-mu)/(2*sigmaSqr);
                probabNew=exp(exponent);
                double r =(static_cast<double>(rand()%100))/100;
                if(r<probabNew)
                {
                    Cell newCell;
                    newCell.setCentroid(Point(x,y,z));
                    newCell.setId(cells.back().getId()+1);
                    newCell.setSenseRadius(senseRadius);
                    newCell.setRadius(radius);
                    newCell.setECadherin(1.0F);
                    newCell.setEB(0.0F);
                    newCell.setAge(0);

                    cells.push_back(newCell);
                    //exit the loop (goto used to avoid checking flags)
                    goto cellGenerated;
                }
            }
        }
        cellGenerated:;
    }

    return 0;

}
