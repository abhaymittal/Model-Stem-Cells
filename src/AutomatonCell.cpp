/*
 * AutomatonCell.cpp
 *
 *  Created on: Jun 18, 2014
 *      Author: sandeep
 */

#include "AutomatonCell.h"

AutomatonCell::AutomatonCell() {

	type=0;
	cellCount=0;
    ID=0;
}

AutomatonCell::~AutomatonCell() {
	// TODO Auto-generated destructor stub
}

void AutomatonCell::incrementCount() {
    cellCount+=1;
}
