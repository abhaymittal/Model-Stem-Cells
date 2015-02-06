#ifndef SIMULATIONPARAMETERS_H_
#define SIMULATIONPARAMETERS_H_

/**
*   @class  SimulationParameters
*   @brief  Class for loading simulation parameters
*   @author Pratik Varshney
*   @author Abhay Mittal
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
    double alpha;           /**<The probability of asymmetric division*/
    int beta;               /**<The number of rounds of amplification a TA cell undergo before differentiation*/
    int gamma;      /**< The age at which TDC die*/
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

	/**
    *   @brief  Getter function for the cellDivisionAge
    *   @return The age after which the cell divides
    */
	int getCellDivisionAge() const {
		return cellDivisionAge;
	}

	/**
    *   @brief  Getter function for the alpha value
    *   @return The probability of asymmetric division
    */
	double getAlpha() const {
		return alpha;
	}

	/**
    *   @brief  Getter function for the beta value
    *   @return The number of rounds of amplification a TA cell undergo before differentiation
    */
	int getBeta() const {
		return beta;
	}

	/**
    *   @brief  Getter function for the maximum number of iterations
    *   @return The maximum number of simulation iteration
    */
	int getMaxIteration() const {
		return maxIteration;
	}

    /**
    *   @brief  Getter function for the gamma value
    *   @return The value of gamma at which TDC die
    */
	int getGamma() const {
        return gamma;
	}

};

#endif /* SIMULATIONPARAMETERS_H_ */
