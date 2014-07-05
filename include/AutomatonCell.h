/*
 * AutomatonCell.h
 *
 *  Created on: Jun 18, 2014
 *      Author: sandeep
 */

#ifndef AUTOMATONCELL_H_
#define AUTOMATONCELL_H_

class AutomatonCell {
private:
    short unsigned int type;
	short unsigned int cellCount;
	long int ID;

public:
	AutomatonCell();

	short unsigned int getType() const {
		return type;
	}

	void setType(short unsigned int type) {
		this->type = type;
	}

	short unsigned int getCount() const {
		return cellCount;
	}

	void setCount(short unsigned int cellCount) {
		this->cellCount = cellCount;
	}

	long int getId() const {
		return ID;
	}

	void setId(long int ID) {
		this->ID = ID;
	}

	void incrementCount();

};

#endif /* AUTOMATONCELL_H_ */
