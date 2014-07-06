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


Line Environment::drawLine(Point p1, Point p2)
{
    char signInd, signDep1, signDep2;

    Var indVal, depVal1, depVal2;

    if(abs(p2.getY()-p1.getY())>abs(p2.getX()-p1.getX()))
    {
        if(abs(p2.getZ()-p1.getZ())>abs(p2.getY()-p1.getY()))
        {
            indVal=*(new Var('z',2,abs(p2.getZ()-p1.getZ()),p1.getZ()));
            signInd=((p2.getZ()-p1.getZ())<0)?'-':'+';

            depVal1=*(new Var('x',0,abs(p2.getX()-p1.getX()),p1.getX()));
            signDep1=((p2.getX()-p1.getX())<0)?'-':'+';

            depVal2=*(new Var('y',1,abs(p2.getY()-p1.getY()),p1.getY()));
            signDep2=((p2.getY()-p1.getY())<0)?'-':'+';
        }
        else
        {
            indVal=*(new Var('y',1,abs(p2.getY()-p1.getY()),p1.getY()));
            signInd=((p2.getY()-p1.getY())<0)?'-':'+';

            depVal1=*(new Var('z',2,abs(p2.getZ()-p1.getZ()),p1.getZ()));
            signDep1=((p2.getZ()-p1.getZ())<0)?'-':'+';

            depVal2=*(new Var('x',0,abs(p2.getX()-p1.getX()),p1.getX()));
            signDep2=((p2.getX()-p1.getX())<0)?'-':'+';
        }
    }
    else
    {
        if (abs(p2.getZ()-p1.getZ())>abs(p2.getX()-p1.getX()))
        {
            indVal=*(new Var('z',2,abs(p2.getZ()-p1.getZ()),p1.getZ()));
            signInd=((p2.getZ()-p1.getZ())<0)?'-':'+';

            depVal1=*(new Var('x',0,abs(p2.getX()-p1.getX()),p1.getX()));
            signDep1=((p2.getX()-p1.getX())<0)?'-':'+';

            depVal2=*(new Var('y',1,abs(p2.getY()-p1.getY()),p1.getY()));
            signDep2=((p2.getY()-p1.getY())<0)?'-':'+';
        }
        else
        {
            indVal=*(new Var('x',0,abs(p2.getX()-p1.getX()),p1.getX()));
            signInd=((p2.getX()-p1.getX())<0)?'-':'+';

            depVal1=*(new Var('y',1,abs(p2.getY()-p1.getY()),p1.getY()));
            signDep1=((p2.getY()-p1.getY())<0)?'-':'+';

            depVal2=*(new Var('z',2,abs(p2.getZ()-p1.getZ()),p1.getZ()));
            signDep2=((p2.getZ()-p1.getZ())<0)?'-':'+';
        }
    }

    Line outLine(indVal.getDelta()+1);

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
    return outLine;
}

int Environment::generatePtFreqMap(Line* line, SimulationParameters sim,AutomatonCell ***cells)
{
    cout<<"Enter generate PT Freq MAP"<<endl;
    for(long i=0;i<sim.getFiberCount();i++)
    {
        cout<<"Line "<<i+1<<endl;
        for(int j=0;j<line[i].getNumberOfPoints();j++)
        {
           // cout<<" Line ==> "<<line[i].getPoint(j).getX()<<" "<<line[i].getPoint(j).getY()<<" "<<line[i].getPoint(j).getZ()<<endl;
            cells[line[i].getPoint(j).getX()][line[i].getPoint(j).getY()][line[i].getPoint(j).getZ()].setType(1);
            cells[line[i].getPoint(j).getX()][line[i].getPoint(j).getY()][line[i].getPoint(j).getZ()].incrementCount();
        }
    }
    cout<<"Working\n";
    return 0;
}

int Environment::setupECM(SimulationParameters sim,AutomatonCell ***ptFreqMap){

	Point box[8];
    //Line *lines = new Line[sim.getFiberCount()];
    Line lines[sim.getFiberCount()];
    long i;
    static long id=0L;
    int fiberLengthSqr, zMaxSqr, minRandomX, maxRandomX, rangeRandomX;
    int xMax=sim.getLatticeWidth()-1;
    int yMax=sim.getLatticeHeight()-1;
    int zMax=sim.getLatticeDepth()-1;

    //Initialize coordinates of box
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

    //seed random number generator with current time
    fiberLengthSqr = sim.getFiberLength() * sim.getFiberLength();
    zMaxSqr = zMax * zMax;

    minRandomX=( (fiberLengthSqr - zMaxSqr) > (yMax*yMax) )?ceil(sqrt( (fiberLengthSqr - zMaxSqr) - (yMax*yMax) )):0;

    maxRandomX = (sim.getFiberLength()<xMax)?sim.getFiberLength():xMax;

    rangeRandomX = (maxRandomX -minRandomX) + 1;

    for(i=0; i<sim.getFiberCount(); i++)
    {
        int randX=sim.getFiberLength()+(rand()%(sim.getLatticeWidth()-2*sim.getFiberLength()));
        int randY=sim.getFiberLength()+(rand()%(sim.getLatticeHeight()-2*sim.getFiberLength()));
        int randZ=sim.getFiberLength()+(rand()%(sim.getLatticeDepth()-2*sim.getFiberLength()));
        int randTheta=rand()%360;
        int randPhi=rand()%360;

        int x2=(int)(randX+sim.getFiberLength()*sin(randTheta)*cos(randPhi));
        int y2=(int)(randX+sim.getFiberLength()*sin(randTheta)*sin(randPhi));
        int z2=(int)(randX+sim.getFiberLength()*cos(randTheta));
        Point p1(randX,randY,randZ);
        Point p2(x2,y2,z2);
        cout<<"Line = "<<id<<"Pt1 = "<<randX<<" "<<randY<<" "<<randZ<<" | Pt2 = "<<x2<<" "<<y2<<" "<<z2<<endl;


        lines[i]=drawLine(p1,p2);
        lines[i].setId(id);
        id++;
    }
    generatePtFreqMap(lines, sim,ptFreqMap);
    return 0;
}

int Environment::createCells(int cellCount, int radius, int senseRadius, SimulationParameters sim, Cell *cells, AutomatonCell ***environment) {
    int width=sim.getLatticeWidth();
    int height=sim.getLatticeHeight();
    int depth=sim.getLatticeDepth();
     int x,y,z;

    for(int i=0;i<cellCount;i++)
    {
        do {
            x=rand()%(width);
            y=rand()%(height);
            z=rand()%(depth);
        } while(environment[x][y][z].getId()!=0);
        cells[i].setCentroid(*new Point(x,y,z));
        cells[i].setID(i+1);
        cells[i].setSenseRadius(senseRadius);
        cells[i].setRadius(radius);
        cells[i].setECadherin(1.0F);
        cells[i].setEB(0.0F);
        environment[x][y][z].setId(i+1);
        environment[x][y][z].setType(2);
        environment[x][y][z].setCount(0);

    }

    return 0;
}
