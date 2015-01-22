#include "TACell.h"

TACell::TACell():Cell(),currentBeta(0)
{

}

int TACell::getCurrentBeta() {
    return currentBeta;
}
int TACell::setCurrentBeta(int Beta) {
    currentBeta=Beta;
    return 0;
}
int TACell::incrementBeta() {
    currentBeta=currentBeta+1;
    return currentBeta;
}

int TACell::differentiate(Cell& TDC, AutomatonCell ***environment,int id_) {
    TDC.setAge(0);
    TDC.setCentroid(this->getCentroid());
    TDC.setRadius(this->getRadius());
    TDC.setSenseRadius(this->getSenseRadius());
    TDC.setId(id_);
    TDC.setECadherin(this->getECadherin());
    TDC.setEB(this->getEB());
    for(int i=0;i<15;i++)
        TDC.setGeneticCode(i,this->getGeneticCode(i));
    environment[TDC.getCentroid().getX()][TDC.getCentroid().getY()][TDC.getCentroid().getZ()].setType(AutomatonCell::CELL);
    environment[TDC.getCentroid().getX()][TDC.getCentroid().getY()][TDC.getCentroid().getZ()].setId(id_);
    return 0;
}


int TACell::divide(TACell& daughter, int id_, AutomatonCell ***environment, SimulationParameters sim) {

    Point childPoint;
    int status =getFavorableLocation(childPoint, environment, sim);

    if(status!=0) return status;

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
    this->incrementBeta();
    daughter.setCurrentBeta(this->getCurrentBeta());
    environment[childPoint.getX()][childPoint.getY()][childPoint.getZ()].setType(AutomatonCell::TA_CELL);
    environment[childPoint.getX()][childPoint.getY()][childPoint.getZ()].setCount(0);
    environment[childPoint.getX()][childPoint.getY()][childPoint.getZ()].setId(daughter.getId());
    return 0;

}
