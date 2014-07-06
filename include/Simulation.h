#ifndef SIMULATION_H
#define SIMULATION_H

#include "SimulationParameters.h"
#include "AutomatonCell.h"
#include "Cell.h"
class Simulation
{
    public:

        Simulation();
        int moveCell(SimulationParameters sim, AutomatonCell ***lattice, Cell *cells);
    protected:
    private:
};

#endif // SIMULATION_H
