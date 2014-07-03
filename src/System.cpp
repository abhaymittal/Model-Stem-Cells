#include "System.h"
#include "Cell.h"
#include "Pixel.h"
#include "SimulationParameters.h"
#include "Point.h"
#include <cstdlib>
System::System()
{}

System::~System()
{}

int System::setupCells(int cellCount_, int radius, int senseRadius, SimulationParameters sim) {
    cellCount=cellCount_;
    xMax=sim.getLatticeWidth()-1;
    yMax=sim.getLatticeHeight()-1;
    zMax=sim.getLatticeDepth()-1;

    cells=new Cell[cellCount];
    pixels=new Pixel**[xMax];
    for(int i=0;i<xMax;i++) {
        pixels[i]=new Pixel*[yMax];
        for(int j=0;j<yMax;j++) {
            pixels[i][j]=new Pixel[zMax];
        }
    }

    int x,y,z;
    for(int i=1;i<=cellCount;i++) {

        do {
            x=rand()%(xMax+1);
            y=rand()%(yMax+1);
            z=rand()%(zMax+1);
        } while(pixels[x][y][z].getCellID()!=-1);
        cells[i].setCentroid(*new Point(x,y,z));
        cells[i].setRadius(1);
        cells[i].setSenseRadius(1);
        cells[i].setID(i);
        pixels[x][y][z].setCellID(i);
    }
    return 0;
}

long int System::getCellID(int x, int y, int z) {
    return pixels[x][y][z].getCellID();
}
