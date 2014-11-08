/*
 * SimulationParameters.h
 *
 *  Created on: Jun 17, 2014
 *      Author: sandeep
 */

#ifndef SIMULATIONPARAMETERS_H_
#define SIMULATIONPARAMETERS_H_

/**
*   @class  SimulationParameters
*   @brief  Class for loading simulation parameters
*/

#include <string>

class SimulationParameters {
private:
    int latticeHeight; 		/**<The Height of the lattice*/
	int latticeWidth;		/**<The Width of the lattice*/
	int latticeDepth;		/**<The Depth of the lattice*/
	int fiberLength;		/**<The Length of each fiber*/
	long int fiberCount;	/**<The number of fibers in the lattice*/
	int cellCount;          /**<The number of cells present at the beginning of simulation*/
	int cellDivisionAge;    /**<The age after which the cell divides*/
    int alpha;              /**<The probability of asymmetric division*/
    int maxIteration;       /**<The maximum number of simulation iteration*/

public:

	/**
    *   @brief  Default no argument constructor
    */
	SimulationParameters();

	/**
    *   @brief  A virtual destructor
    */
	virtual ~SimulationParameters();

	/**
    *   @brief  Function for loading Simulation Parameters from default file "uscp.conf"
    *   @return void
    */
	void loadParameters();

	/**
    *   @brief  Function for loading Simulation Parameters from specified file
    *   @param  filename - Path to file containing simulation parameters
    *   @return void
    */
	void loadParametersFromFile(std::string filename);

	/**
    *   @brief  Getter function for the fiberCount
    *   @return The count of the fibers in the lattice
    */
	long int getFiberCount() const {
		return fiberCount;
	}

	/**
    *   @brief  Setter function for the fiberCount
    *   @param  fiberCount - The count of the fibers in the lattice
    *   @return void
    */
	void setFiberCount(long int fiberCount) {
		this->fiberCount = fiberCount;
	}

	/**
    *   @brief  Getter function for the fiberLength
    *   @return The length of the fiber
    */
	int getFiberLength() const {
		return fiberLength;
	}

	/**
    *   @brief  Getter function for the latticeDepth
    *   @return The Depth of the lattice
    */
	int getLatticeDepth() const {
		return latticeDepth;
	}

	/**
    *   @brief  Getter function for the latticeHeight
    *   @return The Height of the lattice
    */
	int getLatticeHeight() const {
		return latticeHeight;
	}

	/**
    *   @brief  Getter function for the latticeWidth
    *   @return The Width of the lattice
    */
	int getLatticeWidth() const {
		return latticeWidth;
	}

	/**
    *   @brief  Getter function for the cellCount
    *   @return The number of cells present at the beginning of simulation
    */
	int getCellCount() const {
		return cellCount;
	}
};

#endif /* SIMULATIONPARAMETERS_H_ */
