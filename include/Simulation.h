#ifndef SIMULATION_H
#define SIMULATION_H

#include "SimulationParameters.h"
#include "AutomatonCell.h"
#include "Cell.h"
class Simulation
{
    private:
        int moveCells(SimulationParameters sim, AutomatonCell ***lattice, Cell *cells);
        int updateEB(SimulationParameters sim, AutomatonCell ***lattice, Cell *cells);
    public:
        Simulation();
        int findOpId();
        int simulate(SimulationParameters sim, AutomatonCell ***lattice, Cell *cells, int opId);

};

#endif // SIMULATION_H
