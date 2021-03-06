/**
*   @class  Environment
*   @brief  This class provides functions for setting up the simulation environment
*   @author Abhay Mittal
*   @author Pratik Varshney
*/


#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H


#include "SimulationParameters.h"
#include "AutomatonCell.h"
#include "global.h"
#include "Point.h"
#include "Line.h"
#include "Var.h"
#include "Cell.h"
#include "global.h"
#include <deque>

class Environment
{
private:

    /**
    *   @brief  Function to generate a fiber frequency map for all points in the lattice.
    *    This function generates a 3d array(representing the environment) such that each array element
    *   represents a point in 3d space and tells the number of fibers intersecting at that point
    *   @param[in]  line : An array consisting of all the fibers
    *   @param[in]  sim : The simulation parameters
    *   @param[out] environment : The simulation environment lattice
    *   @return 0
    */
    int generatePtFreqMap(Line* line, SimulationParameters sim,AutomatonCell ***environment);

    /**
    *   @brief  Function to draw a line between two points
    *   @param  p1 : The first end point
    *   @param  p2 : The second end point
    *   @param outline : The output Line object
    *   @return 0
    *   @see Line
    */
    int drawLine(Point p1, Point p2, Line& outline);
public:
    /** Default constructor */
    Environment();

    /**
    *   @brief  Function to set up the Extra Cellular Matrix Fibers
    *   @param[in]  sim : The simulation parameters
    *   @param[out] environment: The simulation environment lattice.
    *   @return 0
    */
    int setupECM(SimulationParameters sim,AutomatonCell ***environment);

    /**
    *   @brief  Function to generate cells for simulation.
    *   This function generates cellCount number of cells and then places them randomly within the region of interest. The region
    *   of interest is another cuboid inside the lattice box.
    *   @param[in]  cellCount : The number of cells to generate
    *   @param[in]  radius : The radius of each cell
    *   @param[in]  senseRadius : The sensing radius of each cell
    *   @param[in]  sim : The simulation parameters
    *   @param[in]  environment :  The simulation environment lattice.
    *   @param[out] cells : A deque of generated cells
    *   @return 0
    */
    int createCells(int radius, int senseRadius, SimulationParameters sim, std::deque<Cell> &cells, AutomatonCell ***environment);

    /**
    *   @brief  Function to insert a new cell at a location in the Environment
    *   This function creates a new normal, stem or transit amplifying cell and places it at a  particular location.
    *   @param[in]  radius : The radius of the new cell
    *   @param[in]  senseRadius : The sensing radius of the new cell
    *   @param[in]  centroid : The location of the centroid of the new cell
    *   @param[in]  sim : The simulation parameters
    *   @param[in]  type : The type of cell to put (normal, transit or stem)
    *   @param[in]  environment :  The simulation environment lattice.
    *   @param[out] cellGroup : All the cells in the environment
    *   @return 0
    */
    int insertCell(int radius,int senseRadius, Point centroid, SimulationParameters sim,int type , AutomatonCell ***environment,cellGroup& cells);

    /**
    *   @brief  Function to clear the spherical region in the Environment
    *   This function creates an imaginary sphere and removes all the fibers within the sphere.
    *   @param[in]  xc : The x-coordinate of the center of the spherical region.
    *   @param[in]  yc : The y-coordinate of the center of the spherical region.
    *   @param[in]  zc : The z-coordinate of the center of the spherical region.
    *   @param[in]  radius : The radius of the spherical region.
    *   @param[in]  environment :  The simulation environment lattice.
    *   @return 0
    */
    int clearSphericalRegion(int xc, int yc, int zc, int radius, AutomatonCell ***environment);
};

#endif // ENVIRONMENT_H
