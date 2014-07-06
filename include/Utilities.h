/*
 * Utilities.h
 *
 *  Created on: Jun 18, 2014
 *      Author: sandeep
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include "AutomatonCell.h"
#include "SimulationParameters.h"
class Utilities {
public:
	Utilities();
	virtual ~Utilities();

	void generateECMFile(SimulationParameters sim, AutomatonCell ***environment, int field);

	static const int TYPE = 1, COUNT = 2, ID = 3;


};

#endif /* UTILITIES_H_ */
