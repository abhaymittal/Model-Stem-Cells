/*
 * ECM.h
 *
 *  Created on: Jun 17, 2014
 *      Author: sandeep
 */

#ifndef ECM_H_
#define ECM_H_

#include "SimulationParameters.h"
#include "AutomatonCell.h"

class ECM {
public:
	ECM();
	virtual ~ECM();

	void setupECM(SimulationParameters sim, AutomatonCell *cells);
};

#endif /* ECM_H_ */
