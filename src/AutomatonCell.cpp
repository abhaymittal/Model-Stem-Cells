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

short unsigned int getType() const {
		return type;
}

int setType(short unsigned int type) {
		this->type = type;
		return 0;
}

short unsigned int getCount() const {
		return cellCount;
}

int setCount(short unsigned int cellCount) {
		this->cellCount = cellCount;
}


long int getId() const {
		return ID;
}

int setId(long int ID) {
		this->ID = ID;
}
