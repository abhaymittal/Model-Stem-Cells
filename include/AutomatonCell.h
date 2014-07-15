/**
*   @class  AutomatonCell
*   @brief  Class representing a Lattice Point

*   The following are the legal values for the type
*   Type    |    Meaning
*   --------|-----------
*   0       |    Nothing present
*   1       |    ECM
*   2       |    Cell

*   The following are the legal values for cellID
*   Cell ID |   Denotes
*   --------|----------
*   0       |   Cell not present
*   >0      |   The id of the cell present

*   @author Abhay Mittal
*   @author Pratik Varshney
*/
#ifndef AUTOMATONCELL_H_
#define AUTOMATONCELL_H_

class AutomatonCell {
private:
    short unsigned int type;        /**< Denotes the content at this point*/
	short unsigned int cellCount;   /**< Number of fibers at this point if ECM, else 0*/
	long int ID;                    /**< The cell id if a cell is present, else 0*/

public:

    /**
    *   @brief  Default no argument constructor
    */
	AutomatonCell();

    /**
    *   @brief  Getter function for type
    *   @return The type of the point
    */
	short unsigned int getType() const;

    /**
    *   @brief  Setter function for the type
    *   @param  type : The type of point
    *   @return 0
    */
	int setType(short unsigned int type);

    /**
    *   @brief  Getter function for number of ECM fibers
    *   @return Number of ECM fibers
    */
	short unsigned int getCount() const;

    /**
    *   @brief  Setter function for number of ECM fibers
    *   @param  cellCount:  The number of ECM fibers
    *   @return 0
    */
	int setCount(short unsigned int cellCount);

	/**
    *   @brief  Getter function for the cell ID
    *   @return Cell ID

    *        (if cell is present, else 0)
    */
	long int getId() const;

    /**
    *   @brief  Setter function for the cell ID
    *   @param  ID: The id of the cell
    *   @return 0
    */
	int setId(long int ID);

    /**
    *   @brief  Function to increment the number of fibers
    *   @return 0
    */
	int incrementCount();

};

#endif /* AUTOMATONCELL_H_ */
