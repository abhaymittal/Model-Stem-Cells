#include "Cell.h"
#include <cmath>
#include<cstdlib>

Cell::Cell():id(0),radius(0),senseRadius(0),eCadherin(0.0),centroid(*new Point(0,0,0)),EB(0.0),age(0)
{
    int i=0;
    for(i=0;i<3;i++) {
        geneticCode[i]=((rand()%2)==0)?false:true;
    }
}

Cell::~Cell()
{}

long int Cell::getId() const {
    return id;
}

int Cell::setId(long id_) {
    id=id_;
    return 0;
}

int Cell::getRadius() const {
    return radius;
}
int Cell::setRadius(int radius_) {
    radius=radius_;
    return 0;
}

int Cell::getSenseRadius() const {
    return senseRadius;
}
int Cell::setSenseRadius(int senseRadius_) {
    senseRadius=senseRadius_;
    return 0;
}

Point Cell::getCentroid() const {
    return centroid;
}
int Cell::setCentroid(Point centroid_) {
    centroid.setX(centroid_.getX());
    centroid.setY(centroid_.getY());
    centroid.setZ(centroid_.getZ());
    return 0;
}

int Cell::setECadherin(float eCadherin_) {
    eCadherin=eCadherin_;
    return 0;
}
float Cell::getECadherin() const {
    return eCadherin;
}

int Cell::setEB(float EB_) {
    EB=EB_;
    return 0;
}
float Cell::getEB() const {
    return EB;
}

int Cell::getGeneticCode(bool *gCode) const {
    gCode[0]=geneticCode[0];
    gCode[1]=geneticCode[1];
    gCode[2]=geneticCode[2];
    return 0;
 }

 bool Cell::getGeneticCode(int index) const {
    return geneticCode[index];
 }

int Cell::setGeneticCode(bool *gCode) {
    geneticCode[0]=gCode[0];
    geneticCode[1]=gCode[1];
    geneticCode[2]=gCode[2];
    return 0;
}

int Cell::setGeneticCode(int index,bool gCode) {
    geneticCode[index]=gCode;
    return 0;
}

 int Cell::getAge() {
    return age;
}

int Cell::setAge(int age_) {
    age=age_;
}

int Cell::incrementAge() {
    age++;
    return age;
}

int Cell::getFavorableLocation(Point& location, AutomatonCell ***environment, SimulationParameters sim) {
    int num=(2*senseRadius+1);
    int neighbourFiber[num][num][num];
    int probabNew;
    int sumFiber=0;
    double mean;
    double mu=0;
    double sigma=1;
    double sigmaSqr=sigma*sigma;
    int i,j,k,x,y,z;

    int xMin = centroid.getX()-senseRadius;
    int xMax = centroid.getX()+senseRadius;

    int yMin = centroid.getY()-senseRadius;
    int yMax = centroid.getY()+senseRadius;

    int zMin = centroid.getZ()-senseRadius;
    int zMax = centroid.getZ()+senseRadius;

    for(x=xMin;x<=xMax;x++)
    {
        for(y=yMin;y<=yMax;y++)
        {
            for(z=zMin;z<=zMax;z++)
            {
                neighbourFiber[x-xMin][y-yMin][z-zMin]=environment[x][y][z].getCount();
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
                x=i+xMin;
                y=j+yMin;
                z=k+zMin;
                if((x<sim.getFiberLength())||(x>(sim.getLatticeWidth()-sim.getFiberLength()))||(y<sim.getFiberLength())||(y>(sim.getLatticeWidth()-sim.getFiberLength()))||(z<sim.getFiberLength())||(z>(sim.getLatticeWidth()-sim.getFiberLength())))
                    continue;
                if((environment[x][y][z].getType()==2))
                        continue;
                double exponent=-1*(neighbourFiber[i][j][k]-mu)*(neighbourFiber[i][j][k]-mu)/(2*sigmaSqr);
                probabNew=exp(exponent);
                double r =(static_cast<double>(rand()%100))/100;
                if(r<probabNew)
                {

                    location.setX(x);
                    location.setY(y);
                    location.setZ(z);

                    return 0;
                }
            }
        }
    }

    return -1;

}
