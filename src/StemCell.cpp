#include "StemCell.h"

StemCell::StemCell() : Cell()
{

}


int StemCell::divide(StemCell& daughter, int id_, AutomatonCell ***environment, SimulationParameters sim) {
    int status;
    Point childPoint;
    status= getFavorableLocation(childPoint,environment, sim);
    if(status!=0)
        return status;
    daughter.setCentroid(childPoint);
    daughter.setId(id_);
    daughter.setRadius(this->getRadius());
    daughter.setSenseRadius(this->getSenseRadius());
    daughter.setECadherin(this->getECadherin());
    daughter.setEB(this->getEB());
    for(int i=0;i<15;i++)
        daughter.setGeneticCode(i,this->getGeneticCode(i));
    daughter.setAge(0);
    this->setAge(0);
    environment[childPoint.getX()][childPoint.getY()][childPoint.getZ()].setType(AutomatonCell::STEM_CELL);
    environment[childPoint.getX()][childPoint.getY()][childPoint.getZ()].setCount(0);
    environment[childPoint.getX()][childPoint.getY()][childPoint.getZ()].setId(daughter.getId());
    return 0;
}

int StemCell::divide(TACell& daughter, int id_, AutomatonCell*** environment, SimulationParameters sim) {
    int status;
    Point childPoint;
    status= getFavorableLocation(childPoint,environment, sim);
    if(status!=0)
        return status;
    daughter.setCentroid(childPoint);
    daughter.setId(id_);
    daughter.setRadius(this->getRadius());
    daughter.setSenseRadius(this->getSenseRadius());
    daughter.setECadherin(this->getECadherin());
    daughter.setEB(this->getEB());
    for(int i=0;i<15;i++)
        daughter.setGeneticCode(i,this->getGeneticCode(i));
    daughter.setAge(0);
    this->setAge(0);
    environment[childPoint.getX()][childPoint.getY()][childPoint.getZ()].setType(AutomatonCell::TA_CELL);
    environment[childPoint.getX()][childPoint.getY()][childPoint.getZ()].setCount(0);
    environment[childPoint.getX()][childPoint.getY()][childPoint.getZ()].setId(daughter.getId());

    int totalFiber=0;

    for(int x=daughter.getCentroid().getX()-daughter.getSenseRadius();x<=daughter.getCentroid().getX()+daughter.getSenseRadius();x++) {
        for(int y=daughter.getCentroid().getY()-daughter.getSenseRadius();y<=daughter.getCentroid().getY()+daughter.getSenseRadius();y++) {
            for(int z=daughter.getCentroid().getZ()-daughter.getSenseRadius();z<=daughter.getCentroid().getZ()+daughter.getSenseRadius();z++) {
                    if(environment[x][y][z].getType()==AutomatonCell::ECM)
                        totalFiber+=environment[x][y][z].getCount();
            }
        }
    }

    int beta=sim.getBeta()*0.87F*(static_cast<double>(totalFiber)/(totalFiber+4));

    daughter.setBeta(beta);
    return 0;
}
