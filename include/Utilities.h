#ifndef UTILITIES_H_
#define UTILITIES_H_

/**
*   @class  Utilities
*   @brief  Class for generating the Output
*   @author Pratik Varshney
*   @author Abhay Mittal
*/

#include "AutomatonCell.h"
#include "SimulationParameters.h"
#include "Cell.h"
#include <deque>

class Utilities {
public:

    	static const int 	TYPE = 1,	/**<The CONSTANT value to specify the listing of points according to their TYPE*/
						COUNT = 2,	/**<The CONSTANT value to specify the listing of points according to their COUNT*/
						ID = 3;		/**<The CONSTANT value to specify the listing of points according to their ID*/

	/**
    *   @brief  Default no argument constructor
    */
	Utilities();


	/**
    *   @brief  	Function for generating the Output file "ptMap.xyz"
    *   @param[in]  sim 		: the simulation parameters
    *   @param[in]  environment : the Automaton Cell
    *   @param[in]  field 		: the field (TYPE | COUNT | ID) according to which the output points are listed
    *   @param[in]  iterationNumber 		: used as filename
    *   @return 	void
    */
	void generateECMFile(SimulationParameters sim, AutomatonCell ***environment, int field, int iterationNumber);




    /**
    *   @brief  	Function for generating the current Iteration Output file "iterationNumber.txt"
    *   @param[in]  sim 		    : the simulation parameters
    *   @param[in]  environment     : the Automaton Cell
    *   @param[in]  iterationNumber : the output file will be saved with name "iterationNumber.txt"
    *   @return 	int             : 0 for success, -1 for failure
    */
    int writeIteration(SimulationParameters sim, AutomatonCell ***environment, std::deque<Cell> &cells, int iterationNumber);

};

#endif /* UTILITIES_H_ */
