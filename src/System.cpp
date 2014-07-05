#include "System.h"
#include "Cell.h"
#include "Pixel.h"
#include "SimulationParameters.h"
#include "Point.h"
#include <cstdlib>
#include "Cell.h"
System::System()
{}

System::~System()
{}

int System::createCells(int cellCount, int radius, int senseRadius, SimulationParameters sim, Cell *cells, AutomatonCell ***environment) {
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
        environment[x][y][z].setId(i+1);
        environment[x][y][z].setType(2);
        environment[x][y][z].setCount(0);

    }

    return 0;
}
