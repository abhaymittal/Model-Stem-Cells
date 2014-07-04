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
    int width;
    int height;
    int depth;
    public:
        /** Default constructor */
        System();
        /** Default destructor */
        virtual ~System();

        int setupCells(int cellCount_, int radius, int senseRadius, SimulationParameters sim);
        long int getCellID(int x, int y, int z);

        int getPixelArray(Pixel ***px);
};

#endif // SYSTEM_H
