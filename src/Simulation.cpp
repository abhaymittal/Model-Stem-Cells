#include "Simulation.h"
#include "AutomatonCell.h"
#include "Cell.h"
#include "Point.h"
#include <cmath>
#include <cstdlib>
#include <queue>
#include <map>

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
        lattice[it->getCentroid().getX()][it->getCentroid().getY()][it->getCentroid().getZ()].setType(AutomatonCell::EMPTY);
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
    if(cells.size()==0)
        return -1;
    int totalNeighbours=(2*cells[0].getSenseRadius()+1)*(2*cells[0].getSenseRadius()+1)*(2*cells[0].getSenseRadius()+1);

    std::map<long int, long int> idToIndexMap;
    long int i=0;
    for(std::deque<Cell>::iterator it = cells.begin(); it!=cells.end(); it++, i++){
        idToIndexMap[it->getId()] = i;
    }

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
                        totalNeighbourEC+=cells[idToIndexMap[lattice[x][y][z].getId()]].getECadherin();
                    }
                }
            }
        }
        EBNew=0.5F*(((static_cast<float>(k))/(sumFiber+k))*(it->getEB())+(totalNeighbourEC/totalNeighbours));
        it->setEB(EBNew);
    }
    return 0;
}

int Simulation::simulate(SimulationParameters sim, AutomatonCell ***lattice, cellGroup &cells, int opId)
{
    cout<<"OPID => "<<opId<<endl;
    switch(opId)
    {
        case MOVE_CELLS:
            moveCells(sim,lattice,cells.stemCell);
            moveCells(sim,lattice,cells.taCell);
            moveCells(sim,lattice,cells.normalCell);
            break;

        case UPDATE_EB:
            updateEB(sim,lattice,cells.stemCell);
            updateEB(sim,lattice,cells.taCell);
            updateEB(sim,lattice,cells.normalCell);
            break;

        case EVOLVE_GENETIC_CODE:
            evolveGeneticCode(sim,cells.stemCell);
            evolveGeneticCode(sim,cells.taCell);
            evolveGeneticCode(sim,cells.normalCell);
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
    int numGenes = 15;
    bool prevGeneCode[numGenes];

    for(std::deque<Cell>::iterator it = cells.begin(); it!=cells.end(); it++)
    {
        for(int i=0; i<numGenes; i++){
            prevGeneCode[i] = it->getGeneticCode(i);
        }

        it->setGeneticCode(3, prevGeneCode[0] );
        it->setGeneticCode(4, !(prevGeneCode[1]) & !(prevGeneCode[5]) );
        it->setGeneticCode(5, !(prevGeneCode[2]) );
        it->setGeneticCode(6, prevGeneCode[3] );
        it->setGeneticCode(7, prevGeneCode[3] & prevGeneCode[6] );
        it->setGeneticCode(8, prevGeneCode[9] & !(prevGeneCode[4]) & prevGeneCode[3] & prevGeneCode[7] & !(prevGeneCode[10]) );
        it->setGeneticCode(9, prevGeneCode[8] & !(prevGeneCode[4]) & prevGeneCode[12] );
        it->setGeneticCode(10, prevGeneCode[11] & prevGeneCode[13] & !(prevGeneCode[9]) );
        it->setGeneticCode(11, prevGeneCode[14] & prevGeneCode[12] );
        it->setGeneticCode(12, !(prevGeneCode[5]) & prevGeneCode[10] & prevGeneCode[13] );
        it->setGeneticCode(13, prevGeneCode[7] & prevGeneCode[14] );
        it->setGeneticCode(14, prevGeneCode[8] );
    }
    return 0;
}


int Simulation::increaseAge(cellGroup &cells, int radius, int senseRadius, SimulationParameters sim, AutomatonCell ***environment) {
    std::queue<long long> taQ;
    std::queue<long long> stemQ;

    std::deque<long long> tempDQ;
    long long delIndex;
    long long i=0;
    for(std::deque<Cell>::iterator it = cells.normalCell.begin(); it!=cells.normalCell.end(); it++, i++) {
            if(it->incrementAge()>30) {
                environment[it->getCentroid().getX()][it->getCentroid().getY()][it->getCentroid().getZ()].setType(AutomatonCell::EMPTY);
                tempDQ.push_back(i);
                std::cout << "\nTo DEl => " << i << std::endl;
            }
    }
    std::cout << "DQ size : " << cells.normalCell.size();
    std::cout << "\nTEMP size : " << tempDQ.size();
    std::cout << "\nPRINTING dq \n";
    for(std::deque<long long>::iterator it=tempDQ.begin(); it!=tempDQ.end(); it++)
    {
        std::cout << *it << "\t";
    }
    std::cout << "\nEND dq \n";
    while(!tempDQ.empty()){
        delIndex = tempDQ.back();
        cells.normalCell.erase(cells.normalCell.begin()+delIndex);
        tempDQ.pop_back();
    }
    //ERROR

    i=0;
    for(std::deque<TACell>::iterator it = cells.taCell.begin(); it!=cells.taCell.end(); it++, i++) {
            if(it->incrementAge()>30) {
                it->setAge(0);
                taQ.push(i);
            }
    }

    i=0;
    for(std::deque<StemCell>::iterator it = cells.stemCell.begin(); it!=cells.stemCell.end(); it++, i++) {
            if(it->incrementAge()>30) {
                it->setAge(0);
                stemQ.push(i);
            }
    }

    //TA cell division
    while(!taQ.empty())
    {
        TACell newTACell;
        int newId = (cells.taCell.size()>0) ? cells.taCell.back().getId()+1 : 1;
        int status=cells.taCell.at(taQ.front()).divide(newTACell,newId,environment,sim);
         if(status==0) //new cell is successfully created
        {
            cells.taCell.push_back(newTACell);
        }
        taQ.pop();
    }

    //TA Differentiation
    int beta = sim.getBeta();
    if(!tempDQ.empty())tempDQ.clear();
    i=0;
    for(std::deque<TACell>::iterator it = cells.taCell.begin(); it!=cells.taCell.end(); it++, i++) {
        if(it->getCurrentBeta() > beta)
        {
            Cell newCell;
            int newId = (cells.normalCell.size()>0) ? cells.normalCell.back().getId()+1 : 1;
            it->differentiate(newCell, environment, newId);
            cells.normalCell.push_back(newCell);
            tempDQ.push_back(i); //we'll remove these from DQ later
        }
    }
    while(!tempDQ.empty()){
        delIndex = tempDQ.back();
        cells.taCell.erase(cells.taCell.begin()+delIndex);
        tempDQ.pop_back();
    }

    double alpha = sim.getAlpha();
    while(!stemQ.empty())
    {
        double r =(static_cast<double>(rand()%100))/100;
        if(r < alpha) //asymmetric division
        {
            TACell newTACell;
            int newId = (cells.taCell.size()>0) ? cells.taCell.back().getId()+1 : 1;
            int status = cells.stemCell.at(stemQ.front()).divide(newTACell, newId, environment, sim);
            if(status==0) //new cell is successfully created
            {
                cells.taCell.push_back(newTACell);
            }
        }
        else
        {
            StemCell newStemCell;
            int newId = (cells.stemCell.size()>0) ? cells.stemCell.back().getId()+1 : 1;
            int status = cells.stemCell.at(stemQ.front()).divide(newStemCell, newId, environment, sim);
            if(status==0) //new cell is successfully created
            {
                cells.stemCell.push_back(newStemCell);
            }
        }
        stemQ.pop();
    }

    return 0;
}


/* Operations for Stemcells */
int Simulation::moveCells(SimulationParameters sim, AutomatonCell ***lattice, std::deque<StemCell> &cells)
{
    for(std::deque<StemCell>::iterator it = cells.begin(); it!=cells.end(); it++)
    {
        Point p;
        int status = it->getFavorableLocation(p, lattice, sim);

        if(status!=0) continue;

        //Remove cell from current location (lattice DB)
        lattice[it->getCentroid().getX()][it->getCentroid().getY()][it->getCentroid().getZ()].setType(AutomatonCell::EMPTY);
        lattice[it->getCentroid().getX()][it->getCentroid().getY()][it->getCentroid().getZ()].setId(0);
        lattice[it->getCentroid().getX()][it->getCentroid().getY()][it->getCentroid().getZ()].setCount(0);

        //Reset cell centroid
        it->setCentroid(p);

        //Move cell to new location (lattice DB)
        lattice[p.getX()][p.getY()][p.getZ()].setType(AutomatonCell::STEM_CELL);
        lattice[p.getX()][p.getY()][p.getZ()].setId(it->getId());
        lattice[p.getX()][p.getY()][p.getZ()].setCount(0);
    }
    return 0;
}

int Simulation::updateEB(SimulationParameters sim, AutomatonCell ***lattice, std::deque<StemCell> &cells)
{
    int k=14;
    int sumFiber=0;
    float totalNeighbourEC=0;
    float EBNew;
    if(cells.size()==0)
        return -1;
    int totalNeighbours=(2*cells[0].getSenseRadius()+1)*(2*cells[0].getSenseRadius()+1)*(2*cells[0].getSenseRadius()+1);

    std::map<long int, long int> idToIndexMap;
    long int i=0;
    for(std::deque<StemCell>::iterator it = cells.begin(); it!=cells.end(); it++, i++){
        idToIndexMap[it->getId()] = i;
    }

    for(std::deque<StemCell>::iterator it = cells.begin(); it!=cells.end(); it++)
    {
        sumFiber=0;
        for(int x=it->getCentroid().getX()-it->getSenseRadius();x<=it->getCentroid().getX()+it->getSenseRadius();x++)
        {
            for(int y=it->getCentroid().getY()-it->getSenseRadius();y<=it->getCentroid().getY()+it->getSenseRadius();y++)
            {
                for(int z=it->getCentroid().getZ()-it->getSenseRadius();z<=it->getCentroid().getZ()+it->getSenseRadius();z++)
                {
                    sumFiber+=lattice[x][y][z].getCount();
                    if(lattice[x][y][z].getType()==AutomatonCell::STEM_CELL)
                    {
                        //Cell index in array = id -1 as id was created using index +1 in createCells (Environment.h)
                        totalNeighbourEC+=cells[idToIndexMap[lattice[x][y][z].getId()]].getECadherin();
                    }
                }
            }
        }
        EBNew=0.5F*(((static_cast<float>(k))/(sumFiber+k))*(it->getEB())+(totalNeighbourEC/totalNeighbours));
        it->setEB(EBNew);
    }
    return 0;
}
int Simulation::evolveGeneticCode(SimulationParameters sim,std::deque<StemCell> &cells)
{
    int numGenes = 15;
    bool prevGeneCode[numGenes];

    for(std::deque<StemCell>::iterator it = cells.begin(); it!=cells.end(); it++)
    {
        for(int i=0; i<numGenes; i++){
            prevGeneCode[i] = it->getGeneticCode(i);
        }

        it->setGeneticCode(3, prevGeneCode[0] );
        it->setGeneticCode(4, !(prevGeneCode[1]) & !(prevGeneCode[5]) );
        it->setGeneticCode(5, !(prevGeneCode[2]) );
        it->setGeneticCode(6, prevGeneCode[3] );
        it->setGeneticCode(7, prevGeneCode[3] & prevGeneCode[6] );
        it->setGeneticCode(8, prevGeneCode[9] & !(prevGeneCode[4]) & prevGeneCode[3] & prevGeneCode[7] & !(prevGeneCode[10]) );
        it->setGeneticCode(9, prevGeneCode[8] & !(prevGeneCode[4]) & prevGeneCode[12] );
        it->setGeneticCode(10, prevGeneCode[11] & prevGeneCode[13] & !(prevGeneCode[9]) );
        it->setGeneticCode(11, prevGeneCode[14] & prevGeneCode[12] );
        it->setGeneticCode(12, !(prevGeneCode[5]) & prevGeneCode[10] & prevGeneCode[13] );
        it->setGeneticCode(13, prevGeneCode[7] & prevGeneCode[14] );
        it->setGeneticCode(14, prevGeneCode[8] );
    }
    return 0;
}

/* Operations for TAcells */
int Simulation::moveCells(SimulationParameters sim, AutomatonCell ***lattice, std::deque<TACell> &cells)
{
    for(std::deque<TACell>::iterator it = cells.begin(); it!=cells.end(); it++)
    {
        Point p;
        int status = it->getFavorableLocation(p, lattice, sim);

        if(status!=0) continue;

        //Remove cell from current location (lattice DB)
        lattice[it->getCentroid().getX()][it->getCentroid().getY()][it->getCentroid().getZ()].setType(AutomatonCell::EMPTY);
        lattice[it->getCentroid().getX()][it->getCentroid().getY()][it->getCentroid().getZ()].setId(0);
        lattice[it->getCentroid().getX()][it->getCentroid().getY()][it->getCentroid().getZ()].setCount(0);

        //Reset cell centroid
        it->setCentroid(p);

        //Move cell to new location (lattice DB)
        lattice[p.getX()][p.getY()][p.getZ()].setType(AutomatonCell::TA_CELL);
        lattice[p.getX()][p.getY()][p.getZ()].setId(it->getId());
        lattice[p.getX()][p.getY()][p.getZ()].setCount(0);
    }
    return 0;
}

int Simulation::updateEB(SimulationParameters sim, AutomatonCell ***lattice, std::deque<TACell> &cells)
{
    int k=14;
    int sumFiber=0;
    float totalNeighbourEC=0;
    float EBNew;
    if(cells.size()==0)
        return -1;
    int totalNeighbours=(2*cells[0].getSenseRadius()+1)*(2*cells[0].getSenseRadius()+1)*(2*cells[0].getSenseRadius()+1);

    std::map<long int, long int> idToIndexMap;
    long int i=0;
    for(std::deque<TACell>::iterator it = cells.begin(); it!=cells.end(); it++, i++){
        idToIndexMap[it->getId()] = i;
    }

    for(std::deque<TACell>::iterator it = cells.begin(); it!=cells.end(); it++)
    {
        sumFiber=0;
        for(int x=it->getCentroid().getX()-it->getSenseRadius();x<=it->getCentroid().getX()+it->getSenseRadius();x++)
        {
            for(int y=it->getCentroid().getY()-it->getSenseRadius();y<=it->getCentroid().getY()+it->getSenseRadius();y++)
            {
                for(int z=it->getCentroid().getZ()-it->getSenseRadius();z<=it->getCentroid().getZ()+it->getSenseRadius();z++)
                {
                    sumFiber+=lattice[x][y][z].getCount();
                    if(lattice[x][y][z].getType()==AutomatonCell::TA_CELL)
                    {
                        //Cell index in array = id -1 as id was created using index +1 in createCells (Environment.h)
                        totalNeighbourEC+=cells[idToIndexMap[lattice[x][y][z].getId()]].getECadherin();
                    }
                }
            }
        }
        EBNew=0.5F*(((static_cast<float>(k))/(sumFiber+k))*(it->getEB())+(totalNeighbourEC/totalNeighbours));
        it->setEB(EBNew);
    }
    return 0;
}
int Simulation::evolveGeneticCode(SimulationParameters sim,std::deque<TACell> &cells)
{
    int numGenes = 15;
    bool prevGeneCode[numGenes];

    for(std::deque<TACell>::iterator it = cells.begin(); it!=cells.end(); it++)
    {
        for(int i=0; i<numGenes; i++){
            prevGeneCode[i] = it->getGeneticCode(i);
        }

        it->setGeneticCode(3, prevGeneCode[0] );
        it->setGeneticCode(4, !(prevGeneCode[1]) & !(prevGeneCode[5]) );
        it->setGeneticCode(5, !(prevGeneCode[2]) );
        it->setGeneticCode(6, prevGeneCode[3] );
        it->setGeneticCode(7, prevGeneCode[3] & prevGeneCode[6] );
        it->setGeneticCode(8, prevGeneCode[9] & !(prevGeneCode[4]) & prevGeneCode[3] & prevGeneCode[7] & !(prevGeneCode[10]) );
        it->setGeneticCode(9, prevGeneCode[8] & !(prevGeneCode[4]) & prevGeneCode[12] );
        it->setGeneticCode(10, prevGeneCode[11] & prevGeneCode[13] & !(prevGeneCode[9]) );
        it->setGeneticCode(11, prevGeneCode[14] & prevGeneCode[12] );
        it->setGeneticCode(12, !(prevGeneCode[5]) & prevGeneCode[10] & prevGeneCode[13] );
        it->setGeneticCode(13, prevGeneCode[7] & prevGeneCode[14] );
        it->setGeneticCode(14, prevGeneCode[8] );
    }
    return 0;
}
