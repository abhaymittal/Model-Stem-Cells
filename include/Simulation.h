/**
*   @class Simulation
*   @brief  This class provides necessary functions for performing the simulation.

*   It performs two operations: (i) Moving cells and (ii) updating the ECadherin -&beta; Catenin value.
*   An operation id is associated with each operation:
*   Operation Id    |   Operation
*   ----------------|------------
*   1               |   Move cells
*   2               |   Update ECadherin - &beta; Catenin value
*   3               |   Evolve the genetic code of the cells
*   @author Abhay Mittal
*   @author Pratik Varshney
*/
#ifndef SIMULATION_H
#define SIMULATION_H

#include "SimulationParameters.h"
#include "AutomatonCell.h"
#include "Cell.h"
#include "global.h"
#include <deque>

class Simulation
{
private:
    /**
    *   @brief          Function to move normal cells
    *   @param[in]      sim : the simulation parameters
    *   @param[in, out] lattice : An array containing of all the points along with the number of fibers at each point
    *   @param[in, out] cells : The cells in the simulation environment
    *   @return         0
    */
    int moveCells(SimulationParameters sim, AutomatonCell ***lattice, std::deque<Cell> &cells);

    /**
    *   @brief          Function to update ECadherin - &beta; Catenin value of normal cells
    *   @param[in]      sim : the simulation parameters
    *   @param[in, out] lattice : An array containing of all the points along with the number of fibers at each point
    *   @param[in, out] cells : The cells in the simulation environment
    *   @return         The function returns the following values
    *   Return Value | Meaning
    *   -------------------|------------
    *   0                          | Function updated the EB value of the cells
    *   -1                        | There were no normal cells in the environment
    */
    int updateEB(SimulationParameters sim, AutomatonCell ***lattice, std::deque<Cell> &cells);

    /**
    *   @brief  Function to change the genetic code of normal cells
    *   @param  sim : The simulation parameters (cellCount required)
    *   @param  cells : The cells in the simulation environment
    *   @return 0
    */
    int evolveGeneticCode(SimulationParameters sim,std::deque<Cell> &cells);

    /* Operations for stemcells */

     /**
    *   @brief          Function to move stem cells
    *   @param[in]      sim : the simulation parameters
    *   @param[in, out] lattice : An array containing of all the points along with the number of fibers at each point
    *   @param[in, out] cells : The stem cells in the simulation environment
    *   @return         0
    */
    int moveCells(SimulationParameters sim, AutomatonCell ***lattice, std::deque<StemCell> &cells);

    /**
    *   @brief          Function to update ECadherin - &beta; Catenin value of  stem cells
    *   @param[in]      sim : the simulation parameters
    *   @param[in, out] lattice : An array containing of all the points along with the number of fibers at each point
    *   @param[in, out] cells : The stem cells in the simulation environment
    *   @return         The function returns the following values
    *   Return Value | Meaning
    *   -------------------|------------
    *   0                          | Function updated the EB value of the stem cells
    *   -1                        | There were no stem cells in the environment
    */
    int updateEB(SimulationParameters sim, AutomatonCell ***lattice, std::deque<StemCell> &cells);

    /**
    *   @brief  Function to change the genetic code of stem cells
    *   @param  sim : The simulation parameters (cellCount required)
    *   @param  cells : The stem cells in the simulation environment
    *   @return 0
    */
    int evolveGeneticCode(SimulationParameters sim,std::deque<StemCell> &cells);

    /* Operations for TAcells */

     /**
    *   @brief          Function to move TAcells
    *   @param[in]      sim : the simulation parameters
    *   @param[in, out] lattice : An array containing of all the points along with the number of fibers at each point
    *   @param[in, out] cells : The TAcells in the simulation environment
    *   @return         0
    */
    int moveCells(SimulationParameters sim, AutomatonCell ***lattice, std::deque<TACell> &cells);

    /**
    *   @brief          Function to update ECadherin - &beta; Catenin value
    *   @param[in]      sim : the simulation parameters
    *   @param[in, out] lattice : An array containing of all the points along with the number of fibers at each point
    *   @param[in, out] cells : The TAcells in the simulation environment
     *   @return         The function returns the following values
    *   Return Value | Meaning
    *   -------------------|------------
    *   0                          | Function updated the EB value of the transit amplifying cells
    *   -1                        | There were no transit amplifying cells in the environment
    */
    int updateEB(SimulationParameters sim, AutomatonCell ***lattice, std::deque<TACell> &cells);

    /**
    *   @brief  Function to change the genetic code
    *   @param  sim : The simulation parameters (cellCount required)
    *   @param  cells : The TAcells in the simulation environment
    *   @return 0
    */
    int evolveGeneticCode(SimulationParameters sim,std::deque<TACell> &cells);
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

    /**
    *   @brief  Function to increase age of all cells and multiply cells
    *   @param cells : the group of cells
    *   @param  radius : the radius of the new cells
    *   @param  senseRadius : The sensing radius of new cells
    *   @param  sim : The simulation parameters
    *   @param  environment : The lattice
    */
    int increaseAge(cellGroup &cells, int radius, int senseRadius, SimulationParameters sim, AutomatonCell ***environment);


};

#endif // SIMULATION_H
