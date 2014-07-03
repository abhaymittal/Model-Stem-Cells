#ifndef SYSTEM_H
#define SYSTEM_H

#include"Cell.h"
#include"Pixel.h"
#include"SimulationParameters.h"

class System
{
    private:
    Cell *cells;
    int cellCount;
    Pixel ***pixels;
    int xMax;
    int yMax;
    int zMax;
    public:
        /** Default constructor */
        System();
        /** Default destructor */
        virtual ~System();

        int setupCells(int cellCount_, int radius, int senseRadius, SimulationParameters sim);
        long int getCellID(int x, int y, int z);
};

#endif // SYSTEM_H
