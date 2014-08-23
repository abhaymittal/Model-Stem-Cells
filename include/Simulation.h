/**
*   @brief  This class provides necessary functions for performing the simulation.

*   It performs two operations: (i) Moving cells and (ii) updating the ECadherin -&beta; Catenin value.
*   An operation id is associated with each operation:
*   Operation Id    |   Operation
*   ----------------|------------
*   1               |   Move cells
*   2               |   Update ECadherin - &beta; Catenin value

*   @author Abhay Mittal
*   @author Pratik Varshney
*/
#ifndef SIMULATION_H
#define SIMULATION_H

#include "SimulationParameters.h"
#include "AutomatonCell.h"
#include "Cell.h"
#include <deque>

class Simulation
{
private:
    /**
    *   @brief          Function to move cells
    *   @param[in]      sim : the simulation parameters
    *   @param[in, out] lattice : An array containing of all the points along with the number of fibers at each point
    *   @param[in, out] cells : The cells in the simulation environment
    *   @return         0
    */
    int moveCells(SimulationParameters sim, AutomatonCell ***lattice, std::deque<Cell> &cells);

    /**
    *   @brief          Function to update ECadherin - &beta; Catenin value
    *   @param[in]      sim : the simulation parameters
    *   @param[in, out] lattice : An array containing of all the points along with the number of fibers at each point
    *   @param[in, out] cells : The cells in the simulation environment
    *   @return         0
    */
    int updateEB(SimulationParameters sim, AutomatonCell ***lattice, std::deque<Cell> &cells);

    /**
    *   @brief  Function to change the genetic code
    *   @param  sim : The simulation parameters (cellCount required)
    *   @param  cells : The cells in the simulation environment
    *   @return 0
    */
    int evolveGeneticCode(SimulationParameters sim,std::deque<Cell> &cells);
public:

    /**
    *   @brief  Default constructor
    */
    Simulation();

    /**
    *   @brief  Function to randomly generate an operation id.
    *
    *   This function generates a random variable r and moves the cells if r <0.5, else updates the ECadherin - &beta; Catenin value
    *
    *   @return An operation id
    */
    int generateOpId();
    /**
    *   @brief          Function to move cells
    *   @param[in]      sim : the simulation parameters
    *   @param[in, out] lattice : An array containing of all the points along with the number of fibers at each point
    *   @param[in, out] cells : The cells in the simulation environment
    *   @return         0
    */
    int simulate(SimulationParameters sim, AutomatonCell ***lattice, std::deque<Cell> &cells, int opId);

};

#endif // SIMULATION_H
