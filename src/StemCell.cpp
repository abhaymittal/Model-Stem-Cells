#include "StemCell.h"

StemCell::StemCell() : Cell()
{

}


int StemCell::divide(StemCell& daughter, AutomatonCell ***environment, SimulationParameters sim) {
    int temp;
    Point childPoint;
    temp= getFavorableLocation(childPoint,environment, sim);
    if(temp!=0)
        return temp;
    daughter.setAge(0);
    daughter.setCentroid(childPoint);
    daughter.setRadius(this->getRadius());
    daughter.setSenseRadius(this->getSenseRadius());
    daughter.setEB(0);
    daughter.setECadherin(1.0F);
    this->setAge(0);
    return 0;
}

int StemCell::divide(TACell& daughter, AutomatonCell*** environment,SimulationParameters sim) {
    int temp;
    Point childPoint;
    temp= getFavorableLocation(childPoint,environment, sim);
    if(temp!=0)
        return temp;
    daughter.setAge(0);
    daughter.setCentroid(childPoint);
    daughter.setRadius(this->getRadius());
    daughter.setSenseRadius(this->getSenseRadius());
    daughter.setEB(0);
    daughter.setECadherin(1.0F);
    this->setAge(0);
    return 0;
}
