/*
 * Utilities.h
 *
 *  Created on: Jun 18, 2014
 *      Author: sandeep
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include "AutomatonCell.h"
class Utilities {
public:
	Utilities();
	virtual ~Utilities();

	void generateECMFile(AutomatonCell * environment, int field);

};

#endif /* UTILITIES_H_ */
