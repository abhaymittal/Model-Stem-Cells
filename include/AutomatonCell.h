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
	short unsigned int count;
	long int ID;

public:
	AutomatonCell();
	virtual ~AutomatonCell();

};

#endif /* AUTOMATONCELL_H_ */
