#include "Simulation.h"
#include "AutomatonCell.h"
#include "Cell.h"
#include "Point.h"
#include <cmath>
#include <cstdlib>
#include <queue>

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
    for(std::deque<Cell>::iterator it = cells.begin(); it!=cells.end(); it++)
    {
        Point p;
        int status = it->getFavorableLocation(p, lattice, sim);

        if(status!=0) continue;

        //Remove cell from current location (lattice DB)
        lattice[it->getCentroid().getX()][it->getCentroid().getY()][it->getCentroid().getZ()].setType(AutomatonCell::ECM);
        lattice[it->getCentroid().getX()][it->getCentroid().getY()][it->getCentroid().getZ()].setId(0);
        lattice[it->getCentroid().getX()][it->getCentroid().getY()][it->getCentroid().getZ()].setCount(0);

        //Reset cell centroid
        it->setCentroid(p);

        //Move cell to new location (lattice DB)
        lattice[p.getX()][p.getY()][p.getZ()].setType(AutomatonCell::CELL);
        lattice[p.getX()][p.getY()][p.getZ()].setId(it->getId());
        lattice[p.getX()][p.getY()][p.getZ()].setCount(0);
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
                    if(lattice[x][y][z].getType()==AutomatonCell::CELL)
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


int Simulation::increaseAge(cellGroup &cells, int radius, int senseRadius, SimulationParameters sim, AutomatonCell ***environment) {
    queue<Cell> q;
    queue<StemCell> stemQ;
    for(std::deque<Cell>::iterator it = cells.normalCell.begin(); it!=cells.normalCell.end(); it++) {
            if(it->incrementAge()>30) {
                it->setAge(0);
                q.push(*it);
            }
    }

    for(std::deque<StemCell>::iterator it = cells.stemCell.begin(); it!=cells.stemCell.end(); it++) {
            if(it->incrementAge()>30) {
                it->setAge(0);
                stemQ.push(*it);
            }
    }

    while(!q.empty())
    {
        Cell newCell;
        int newId = (cells.normalCell.size()>0) ? cells.normalCell.back().getId()+1 : 1;
        int status=q.front().divide(newCell,newId,environment,sim);
         if(status==0) //new cell is successfully created
        {
            cells.normalCell.push_back(newCell);
        }
        q.pop();
    }

    double alpha = sim.getAlpha();
    while(!stemQ.empty())
    {
        double r =(static_cast<double>(rand()%100))/100;
        if(r < alpha) //asymmetric division
        {
            TACell newTACell;
            int newId = (cells.taCell.size()>0) ? cells.taCell.back().getId()+1 : 1;
            int status = stemQ.front().divide(newTACell, newId, environment, sim);
            if(status==0) //new cell is successfully created
            {
                cells.taCell.push_back(newTACell);
            }
        }
        else
        {
            StemCell newStemCell;
            int newId = (cells.stemCell.size()>0) ? cells.stemCell.back().getId()+1 : 1;
            int status = stemQ.front().divide(newStemCell, newId, environment, sim);
            if(status==0) //new cell is successfully created
            {
                cells.stemCell.push_back(newStemCell);
            }
        }
        stemQ.pop();
    }

    return 0;
}

