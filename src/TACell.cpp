#include "TACell.h"

TACell::TACell():Cell(),currentBeta(0)
{

}

int getCurrentBeta() {
    return currentBeta;
}
int setCurrentBeta(int Beta) {
    currentBeta=Beta;
    return 0;
}
int incrementBeta() {
    currentBeta=currentBeta+1;
    return 0;
}

int differentiate(Cell& TDC, std::deque<TACell> &tacells) {
    TDC.setAge(0);
    TDC.setCentroid(this->getCentroid());
    TDC.setRadius(this->getRadius());
    TDC.setSenseRadius(this->getSenseRadius());
}


int TACell::divide(TACell& daughter, int id_, AutomatonCell ***environment, SimulationParameters sim) {

    Point childPoint;
    int status =getFavorableLocation(childPoint, environment, sim);

    if(status!=0) return status;

    daughter.setCentroid(childPoint);
    daughter.setId(id_);
    daughter.setRadius(this->getRadius());
    daughter.setSenseRadius(this->getSenseRadius());
    daughter.setECadherin(1.0F);
    daughter.setEB(0.0F);
    daughter.setAge(0);
    this->setAge(0);
    this->incrementBeta();
    daughter.setCurrentBeta(this->getCurrentBeta());
    environment[childPoint.getX()][childPoint.getY()][childPoint.getZ()].setType(AutomatonCell::CELL);
    environment[childPoint.getX()][childPoint.getY()][childPoint.getZ()].setCount(0);
    environment[childPoint.getX()][childPoint.getY()][childPoint.getZ()].setId(daughter.getId());
    return 0;

}
