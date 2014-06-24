/*
 * ECM.cpp
 *
 *  Created on: Jun 17, 2014
 *      Author: sandeep
 */

#include "ECM.h"

#include <ctime>    //time
#include <cstdlib>  //rand, srand
#include <cmath>    //sqrt, floor, ceil
#include <iostream>

using namespace std;

ECM::ECM() {
	// TODO Auto-generated constructor stub

}

ECM::~ECM() {
	// TODO Auto-generated destructor stub
}

Line ECM::drawLine(Point p1, Point p2)
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

Line ECM::drawRandomLine(SimulationParameters sim, Point box[8], int fiberLengthSqr, int zMaxSqr, int minRandomX, int maxRandomX, int rangeRandomX)
{
    int xTranslate, yTranslate, zTranslate;
    int minRandomY, maxRandomY, f2_x2, f2_x2_y2;
    Point startPoint, endPoint;
    int xMax=sim.getLatticeWidth()-1;
    int yMax=sim.getLatticeHeight()-1;
    int zMax=sim.getLatticeDepth()-1;

    startPoint=box[rand()%8]; //random vertex of box

    endPoint.setX(( rand() % rangeRandomX ) + minRandomX);

    f2_x2 = fiberLengthSqr - (endPoint.getX() * endPoint.getX()); // currently origin is assumed as fixed point, so f2_x2 is calculated before adjustment

    //adjustment
    if(startPoint.getX() != 0)
    {
        endPoint.setX(xMax - endPoint.getX()); //startPoint.x - endPoint.x
    }

    minRandomY=(f2_x2 > zMaxSqr)?ceil(sqrt(f2_x2 - zMaxSqr)):0;

    maxRandomY = floor(sqrt(f2_x2));
    if(yMax<maxRandomY) maxRandomY = yMax;

    endPoint.setY(( rand() % ((maxRandomY - minRandomY) + 1) ) + minRandomY);
    f2_x2_y2 = f2_x2 - (endPoint.getY() * endPoint.getY());

    if(startPoint.getY() != 0)
    {
        endPoint.setY(yMax - endPoint.getY());
    }

    endPoint.setZ(floor(sqrt(f2_x2_y2))); // floor => inside sphere of radius fiber_length, ceil => outside

    if(startPoint.getZ() != 0)
    {
        endPoint.setZ(zMax - endPoint.getZ());
    }


    if(startPoint.getX() == 0)
    {
        xTranslate = rand()%((xMax - endPoint.getX()) + 1 );
    }
    else
    {
        xTranslate = -( rand() % (endPoint.getX() + 1) );
    }

    if(startPoint.getY() == 0)
    {
        yTranslate = rand()%((yMax - endPoint.getY()) + 1 );
    }
    else
    {
        yTranslate = -( rand() % (endPoint.getY() + 1) );
    }

    if(startPoint.getZ() == 0)
    {
        zTranslate = rand()%((zMax - endPoint.getZ()) + 1 );
    }
    else
    {
        zTranslate = -( rand() % (endPoint.getZ() + 1) );
    }

    startPoint.setX(startPoint.getX() + xTranslate);
    startPoint.setY(startPoint.getY() + yTranslate);
    startPoint.setZ(startPoint.getZ() + zTranslate);
    endPoint.setX(endPoint.getX() + xTranslate);
    endPoint.setY(endPoint.getY() + yTranslate);
    endPoint.setZ(endPoint.getZ() + zTranslate);
    return drawLine(startPoint, endPoint);
}

void ECM::generatePtFreqMap(Line* line, SimulationParameters sim, AutomatonCell ***cells)
{
    cells=new AutomatonCell**[sim.getLatticeWidth()];
    for(int x=0;x<sim.getLatticeWidth();x++)
    {
        cells[x]=new AutomatonCell*[sim.getLatticeHeight()];
        for(int y=0;y<sim.getLatticeHeight();y++)
        {
            cells[x][y]=new AutomatonCell[sim.getLatticeDepth()];
            for(int z=0;z<sim.getLatticeDepth();z++)
            {
                cells[x][y][z].setCount(0);
            }
        }
    }

    for(long i=0;i<sim.getFiberCount();i++)
    {
        for(int j=0;j<line[i].getNumberOfPoints();j++)
        {
            cells[line[i].getPoint(j).getX()][line[i].getPoint(j).getY()][line[i].getPoint(j).getZ()].incrementCount();
        }
    }
}

void ECM::setupECM(SimulationParameters sim, AutomatonCell ***cells){

	Point box[8];
    Line *lines = new Line[sim.getFiberCount()];
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
    srand(time(NULL));

    fiberLengthSqr = sim.getFiberLength() * sim.getFiberLength();
    zMaxSqr = zMax * zMax;

    minRandomX=( (fiberLengthSqr - zMaxSqr) > (yMax*yMax) )?ceil(sqrt( (fiberLengthSqr - zMaxSqr) - (yMax*yMax) )):0;

    maxRandomX = (sim.getFiberLength()<xMax)?sim.getFiberLength():xMax;

    rangeRandomX = (maxRandomX - minRandomX) + 1;


    for(i=0; i<sim.getFiberCount(); i++)
    {
        lines[i]=drawRandomLine(sim, box, fiberLengthSqr, zMaxSqr, minRandomX, maxRandomX, rangeRandomX);
        lines[i].setId(id);
        id++;
    }

    generatePtFreqMap(lines, sim, cells);

}

