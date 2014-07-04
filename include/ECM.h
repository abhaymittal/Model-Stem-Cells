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
#include "Point.h"
#include "Line.h"
#include "Var.h"

class ECM {
private:
    Line drawLine(Point p1, Point p2);
    Line drawRandomLine(SimulationParameters sim, Point box[8], int fiberLengthSqr, int zMaxSqr, int xMin, int xMax, int xRange);
    int ECM::generatePtFreqMap(Line* line, SimulationParameters sim,AutomatonCell ***cells);

public:
	ECM();
	virtual ~ECM();

	int ECM::setupECM(SimulationParameters sim,AutomatonCell ***ptFreqMap)
};

#endif /* ECM_H_ */
