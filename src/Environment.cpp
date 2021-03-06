#include "Environment.h"

#include <ctime>    //time
#include <cstdlib>  //rand
#include <cmath>    //sqrt, floor, ceil
#include <iostream>

using namespace std;
Environment::Environment()
{
    //ctor
}


int Environment::drawLine(Point p1, Point p2,Line& outLine)
{
    char signInd, signDep1, signDep2;

    Var indVal, depVal1, depVal2;

    if(abs(p2.getY()-p1.getY())>abs(p2.getX()-p1.getX()))
    {
        if(abs(p2.getZ()-p1.getZ())>abs(p2.getY()-p1.getY()))
        {
            indVal=Var('z',2,abs(p2.getZ()-p1.getZ()),p1.getZ());
            signInd=((p2.getZ()-p1.getZ())<0)?'-':'+';

            depVal1=Var('x',0,abs(p2.getX()-p1.getX()),p1.getX());
            signDep1=((p2.getX()-p1.getX())<0)?'-':'+';

            depVal2=Var('y',1,abs(p2.getY()-p1.getY()),p1.getY());
            signDep2=((p2.getY()-p1.getY())<0)?'-':'+';
        }
        else
        {
            indVal=Var('y',1,abs(p2.getY()-p1.getY()),p1.getY());
            signInd=((p2.getY()-p1.getY())<0)?'-':'+';

            depVal1=Var('z',2,abs(p2.getZ()-p1.getZ()),p1.getZ());
            signDep1=((p2.getZ()-p1.getZ())<0)?'-':'+';

            depVal2=Var('x',0,abs(p2.getX()-p1.getX()),p1.getX());
            signDep2=((p2.getX()-p1.getX())<0)?'-':'+';
        }
    }
    else
    {
        if (abs(p2.getZ()-p1.getZ())>abs(p2.getX()-p1.getX()))
        {
            indVal=Var('z',2,abs(p2.getZ()-p1.getZ()),p1.getZ());
            signInd=((p2.getZ()-p1.getZ())<0)?'-':'+';

            depVal1=Var('x',0,abs(p2.getX()-p1.getX()),p1.getX());
            signDep1=((p2.getX()-p1.getX())<0)?'-':'+';

            depVal2=Var('y',1,abs(p2.getY()-p1.getY()),p1.getY());
            signDep2=((p2.getY()-p1.getY())<0)?'-':'+';
        }
        else
        {
            indVal=Var('x',0,abs(p2.getX()-p1.getX()),p1.getX());
            signInd=((p2.getX()-p1.getX())<0)?'-':'+';

            depVal1=Var('y',1,abs(p2.getY()-p1.getY()),p1.getY());
            signDep1=((p2.getY()-p1.getY())<0)?'-':'+';

            depVal2=Var('z',2,abs(p2.getZ()-p1.getZ()),p1.getZ());
            signDep2=((p2.getZ()-p1.getZ())<0)?'-':'+';
        }
    }

    //Line outLine(indVal.getDelta()+1);
    outLine.setNumberOfPoints(indVal.getDelta()+1);


    int indValF=p2.getVar(indVal.getVarName());
    int counter_1=0, counter_2=0;
    int incInd, incDep1, incDep2;
    int ptIndex=0;
    Point tempPt;

    incInd=(signInd=='+')?1:-1;
    incDep1=(signDep1=='+')?1:-1;
    incDep2=(signDep2=='+')?1:-1;

    tempPt.setVar(indVal.getVarName(),indVal.getValue());
    tempPt.setVar(depVal1.getVarName(),depVal1.getValue());
    tempPt.setVar(depVal2.getVarName(),depVal2.getValue());
    outLine.setPoint(ptIndex,tempPt);
    ptIndex++;

    while(indVal.getValue()!=indValF)
    {
        counter_1=counter_1+depVal1.getDelta();
        counter_2=counter_2+depVal2.getDelta();

        indVal.setValue(indVal.getValue()+incInd);
        if(counter_1>=indVal.getDelta())
        {
            depVal1.setValue(depVal1.getValue()+incDep1);
            counter_1=counter_1-indVal.getDelta();
        }
        if(counter_2>=indVal.getDelta())
        {
            depVal2.setValue(depVal2.getValue()+incDep2);
            counter_2=counter_2-indVal.getDelta();
        }

        tempPt.setVar(indVal.getVarName(),indVal.getValue());
        tempPt.setVar(depVal1.getVarName(),depVal1.getValue());
        tempPt.setVar(depVal2.getVarName(),depVal2.getValue());
        outLine.setPoint(ptIndex,tempPt);
        ptIndex++;
    }
    return 0;
}

int Environment::generatePtFreqMap(Line* line, SimulationParameters sim,AutomatonCell ***environment)
{
    for(long i=0;i<sim.getFiberCount();i++)
    {

        for(int j=0;j<line[i].getNumberOfPoints();j++)
        {
           // cout<<" Line ==> "<<line[i].getPoint(j).getX()<<" "<<line[i].getPoint(j).getY()<<" "<<line[i].getPoint(j).getZ()<<endl;
            environment[line[i].getPoint(j).getX()][line[i].getPoint(j).getY()][line[i].getPoint(j).getZ()].setType(AutomatonCell::ECM);
            environment[line[i].getPoint(j).getX()][line[i].getPoint(j).getY()][line[i].getPoint(j).getZ()].incrementCount();

        }

    }
    return 0;
}

int Environment::setupECM(SimulationParameters sim,AutomatonCell ***environment){

	Point box[8];
    //Line *lines = new Line[sim.getFiberCount()];
    Line lines[sim.getFiberCount()];
    long i;
    static long id=0L;
    int xMax=sim.getLatticeWidth()-1;
    int yMax=sim.getLatticeHeight()-1;
    int zMax=sim.getLatticeDepth()-1;

    //Initialize coordinates of environment
    box[0].setX(0);
    box[0].setY(0);
    box[0].setZ(0);

    box[1].setX(0);
    box[1].setY(0);
    box[1].setZ(zMax);

    box[2].setX(0);
    box[2].setY(yMax);
    box[2].setZ(0);

    box[3].setX(0);
    box[3].setY(yMax);
    box[3].setZ(zMax);

    box[4].setX(xMax);
    box[4].setY(0);
    box[4].setZ(0);

    box[5].setX(xMax);
    box[5].setY(0);
    box[5].setZ(zMax);

    box[6].setX(xMax);
    box[6].setY(yMax);
    box[6].setZ(0);

    box[7].setX(xMax);
    box[7].setY(yMax);
    box[7].setZ(zMax);


    for(i=0; i<sim.getFiberCount(); i++)
    {
        int randX=sim.getFiberLength()+(rand()%(sim.getLatticeWidth()-2*sim.getFiberLength()));
        int randY=sim.getFiberLength()+(rand()%(sim.getLatticeHeight()-2*sim.getFiberLength()));
        int randZ=sim.getFiberLength()+(rand()%(sim.getLatticeDepth()-2*sim.getFiberLength()));
        double randTheta=(rand()%360)*PI/180;
        double randPhi=(rand()%360)*PI/180;

        int x2=(int)(randX+sim.getFiberLength()*sin(randTheta)*cos(randPhi));
        int y2=(int)(randY+sim.getFiberLength()*sin(randTheta)*sin(randPhi));
        int z2=(int)(randZ+sim.getFiberLength()*cos(randTheta));
        Point p1(randX,randY,randZ);
        Point p2(x2,y2,z2);
        cout<<"Line = "<<id<<"Pt1 = "<<randX<<" "<<randY<<" "<<randZ<<" | Pt2 = "<<x2<<" "<<y2<<" "<<z2<<endl;


        drawLine(p1,p2,lines[i]);
        lines[i].setId(id);
        id++;
    }

    generatePtFreqMap(lines, sim,environment);

    return 0;
}

int Environment::createCells(int radius, int senseRadius, SimulationParameters sim, std::deque<Cell> &cells, AutomatonCell ***environment) {
    int width=sim.getLatticeWidth();
    int height=sim.getLatticeHeight();
    int depth=sim.getLatticeDepth();
     int x,y,z;
    int i=1;
    for(std::deque<Cell>::iterator it = cells.begin(); it!=cells.end(); it++)
    {
        do {
            x=sim.getFiberLength()+(rand()%(width-2*sim.getFiberLength()));
            y=sim.getFiberLength()+(rand()%(height-2*sim.getFiberLength()));
            z=sim.getFiberLength()+(rand()%(depth-2*sim.getFiberLength()));
        } while(environment[x][y][z].getId()!=0);
        it->setCentroid(Point(x,y,z));
        it->setId(i);
        it->setSenseRadius(senseRadius);
        it->setRadius(radius);
        it->setECadherin(1.0F);
        it->setEB(0.0F);
        environment[x][y][z].setId(i);
        environment[x][y][z].setType(AutomatonCell::CELL);
        environment[x][y][z].setCount(0);
        i++;

    }
    cout<<"Cells created\n";

    return 0;
}

int Environment::insertCell(int radius,int senseRadius, Point centroid, SimulationParameters sim,int type , AutomatonCell ***environment,cellGroup& cells) {
    long int newId;
    switch(type) {
    case AutomatonCell::CELL: {
        Cell newCell;
        newCell.setCentroid(centroid);
        newId = (cells.normalCell.size()>0) ? cells.normalCell.back().getId()+1 : 1;
        newCell.setId(newId);
        newCell.setSenseRadius(senseRadius);
        newCell.setRadius(radius);
        newCell.setECadherin(1.0F);
        newCell.setEB(0.0F);
        environment[centroid.getX()][centroid.getY()][centroid.getZ()].setId(newId);
        environment[centroid.getX()][centroid.getY()][centroid.getZ()].setType(AutomatonCell::CELL);
        environment[centroid.getX()][centroid.getY()][centroid.getZ()].setCount(0);
        cells.normalCell.push_back(newCell);
        break;
    }
    case AutomatonCell::STEM_CELL: {
        StemCell newSCell;
        newSCell.setCentroid(centroid);
        newId = (cells.stemCell.size()>0) ? cells.stemCell.back().getId()+1 : 1;
        newSCell.setId(newId);
        newSCell.setSenseRadius(senseRadius);
        newSCell.setRadius(radius);
        newSCell.setECadherin(1.0F);
        newSCell.setEB(0.0F);
        environment[centroid.getX()][centroid.getY()][centroid.getZ()].setId(newId);
        environment[centroid.getX()][centroid.getY()][centroid.getZ()].setType(AutomatonCell::STEM_CELL);
        environment[centroid.getX()][centroid.getY()][centroid.getZ()].setCount(0);
        cells.stemCell.push_back(newSCell);
        break;
    }
    case AutomatonCell::TA_CELL: {
        TACell newTACell;
        newTACell.setCentroid(centroid);
        newId = (cells.taCell.size()>0) ? cells.taCell.back().getId()+1 : 1;
        newTACell.setId(newId);
        newTACell.setSenseRadius(senseRadius);
        newTACell.setRadius(radius);
        newTACell.setECadherin(1.0F);
        newTACell.setEB(0.0F);
        environment[centroid.getX()][centroid.getY()][centroid.getZ()].setId(newId);
        environment[centroid.getX()][centroid.getY()][centroid.getZ()].setType(AutomatonCell::TA_CELL);
        environment[centroid.getX()][centroid.getY()][centroid.getZ()].setCount(0);
        cells.taCell.push_back(newTACell);
        break;
    }
    }
    return 0;
}

int Environment::clearSphericalRegion(int xc, int yc, int zc, int radius, AutomatonCell ***environment){
    int sqrRadius = radius * radius;
    for(int x=0; x<=radius; x++){
        for(int y=0; y<=radius; y++){
            for(int z=0; z<=radius; z++){
                if((x*x)+(y*y)+(z*z) <= sqrRadius){
                    environment[x+xc][y+yc][z+zc].setType(AutomatonCell::EMPTY);
                    environment[x+xc][y+yc][-z+zc].setType(AutomatonCell::EMPTY);
                    environment[x+xc][-y+yc][z+zc].setType(AutomatonCell::EMPTY);
                    environment[x+xc][-y+yc][-z+zc].setType(AutomatonCell::EMPTY);
                    environment[-x+xc][y+yc][z+zc].setType(AutomatonCell::EMPTY);
                    environment[-x+xc][y+yc][-z+zc].setType(AutomatonCell::EMPTY);
                    environment[-x+xc][-y+yc][z+zc].setType(AutomatonCell::EMPTY);
                    environment[-x+xc][-y+yc][-z+zc].setType(AutomatonCell::EMPTY);
                }
            }
        }
    }
    return 0;
}
