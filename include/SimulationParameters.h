/*
 * SimulationParameters.h
 *
 *  Created on: Jun 17, 2014
 *      Author: sandeep
 */

#ifndef SIMULATIONPARAMETERS_H_
#define SIMULATIONPARAMETERS_H_

#include <string>

class SimulationParameters {
private:
    int latticeHeight;
	int latticeWidth;
	int latticeDepth;
	int fiberLength;
	long int fiberCount;

public:
	SimulationParameters();
	virtual ~SimulationParameters();

	void loadParameters();
	void loadParametersFromFile(std::string filename);

	long int getFiberCount() const {
		return fiberCount;
	}

	void setFiberCount(long int fiberCount) {
		this->fiberCount = fiberCount;
	}

	int getFiberLength() const {
		return fiberLength;
	}

	int getLatticeDepth() const {
		return latticeDepth;
	}

	int getLatticeHeight() const {
		return latticeHeight;
	}

	int getLatticeWidth() const {
		return latticeWidth;
	}
};

#endif /* SIMULATIONPARAMETERS_H_ */
