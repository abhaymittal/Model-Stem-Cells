#ifndef SYSTEM_H
#define SYSTEM_H

#include"Cell.h"
#include"Pixel.h"
#include"SimulationParameters.h"
#include"AutomatonCell.h"

class System
{
    private:

    public:
        /** Default constructor */
        System();
        /** Default destructor */
        virtual ~System();
        int createCells(int cellCount, int radius, int senseRadius, SimulationParameters sim, Cell *cells, AutomatonCell ***environment);
};

#endif // SYSTEM_H
