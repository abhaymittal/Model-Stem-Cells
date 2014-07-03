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
    width=sim.getLatticeWidth();
    height=sim.getLatticeHeight();
    depth=sim.getLatticeDepth();

    cells=new Cell[cellCount];
    pixels=new Pixel**[width];
    for(int i=0;i<width;i++) {
        pixels[i]=new Pixel*[height];
        for(int j=0;j<height;j++) {
            pixels[i][j]=new Pixel[depth];
        }
    }
    int x,y,z;
    for(int i=0;i<cellCount;i++) {

        do {
            x=rand()%(width);
            y=rand()%(height);
            z=rand()%(depth);
        } while(pixels[x][y][z].getCellID()!=-1);

        cells[i].setCentroid(*new Point(x,y,z));
        cells[i].setRadius(1);
        cells[i].setSenseRadius(1);
        cells[i].setID(i+1);
        pixels[x][y][z].setCellID(i+1);
    }
    return 0;
}

long int System::getCellID(int x, int y, int z) {
    return pixels[x][y][z].getCellID();
}
