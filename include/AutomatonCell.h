/*
 * AutomatonCell.h
 *
 *  Created on: Jun 18, 2014
 *      Author: sandeep
 */

#ifndef AUTOMATONCELL_H_
#define AUTOMATONCELL_H_

class AutomatonCell {
public:
	AutomatonCell();
	virtual ~AutomatonCell();

	short unsigned int type;
	short unsigned int count;
	long int ID;

};

#endif /* AUTOMATONCELL_H_ */
