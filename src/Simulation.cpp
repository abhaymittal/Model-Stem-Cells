#include "Simulation.h"
#include "Cell.h"
#include "Point.h""
#include <cmath>

Simulation::Simulation()
{
    //ctor
}

int Simulation::moveCell(SimulationParameters sim, AutomatonCell ***lattice, Cell *cells)
{
    int cellCount=100;
    int num=(2*cells[0].getSenseRadius()+1);
    int neighbourFiber[num][num][num];
    int probabMove;
    int sumFiber=0;
    double mean;
    double mu=0;
    double sigma=1;
    double sigmaSqr=sigma*sigma;

    for(int i=0;i<cellCount;i++)
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
                    if((x<sim.getFiberlength())||(x>(sim.getLatticeWidth()-sim.getFiberLength()))||(y<sim.getFiberlength())||(y>(sim.getLatticeWidth()-sim.getFiberLength())(z<sim.getFiberlength())||(z>(sim.getLatticeWidth()-sim.getFiberLength()))))
                        continue;
                    double exponent=-1*(neighbourFiber[x][y][z]-mu)*(neighbourFiber[x][y][z]-mu)/(2*sigmaSqr);
                    probabMove=exp(exponent);
                    double r =(static_cast<double>(rand()%100))/100;
                    if(r<probabMove[x][y][z])
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
            cellMoved:
        }
    }

}

int updateECadherin(SimulationParameters sim, AutomatonCell ***lattice, Cell *cells)
{
    int k=14;
    int sumFiber=0;
    float eCadherinNew;
    for(int i=0;i<cellCount;i++)
    {
        sumFiber=0;
        for(int x=cells[i].getCentroid().getX()-cells[i].getSenseRadius();x<=cells[i].getCentroid().getX()+cells[i].getSenseRadius();x++)
        {
            for(int y=cells[i].getCentroid().getY()-cells[i].getSenseRadius();y<=cells[i].getCentroid().getY()+cells[i].getSenseRadius();y++)
            {
                for(int z=cells[i].getCentroid().getZ()-cells[i].getSenseRadius();z<=cells[i].getCentroid().getZ()+cells[i].getSenseRadius();z++)
                {
                    sumFiber+=lattice[x][y][z].getCount();
                }
            }
        }
        eCadherinNew=(static_cast<float>(sumFiber))/(sumFiber+k);
        cells[i].setECadherin(eCadherinNew);
    }
}
