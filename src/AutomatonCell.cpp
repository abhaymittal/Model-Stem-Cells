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


int AutomatonCell::incrementCount() {
    cellCount+=1;
    return 0;
}

short unsigned int AutomatonCell::getType() const {
		return type;
}

int AutomatonCell::setType(short unsigned int type) {
		this->type = type;
		return 0;
}

short unsigned int AutomatonCell::getCount() const {
		return cellCount;
}

int AutomatonCell::setCount(short unsigned int cellCount) {
		this->cellCount = cellCount;
}


long int AutomatonCell::getId() const {
		return ID;
}

int AutomatonCell::setId(long int ID) {
		this->ID = ID;
}
