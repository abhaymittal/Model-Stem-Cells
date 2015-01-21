/**
*   @class TACell
*   @brief This class models the Transit Amplifying Cells and is derived from the Cell class
*   @author Abhay Mittal
*   @author Pratik Varshney
*/

#ifndef TACELL_H
#define TACELL_H

#include "Cell.h"


class TACell : public Cell
{
private:
    int currentBeta;

public:
    TACell();

    /**
    *   @brief  Method to return the current value of Beta
    *   @return The current value of Beta
    */
    int getCurrentBeta();

    /**
    *   @brief  Method to set the current value of Beta
    *   @param  The new value of Beta
    *   @return 0
    */
    int setCurrentBeta(int Beta);

    /**
    *   @brief  Method to increment the current value of Beta
    *   @return 0
    */
    int incrementBeta();

    /**
    *   @brief Function for differentiating  the Transit Amplifying Cell
    *   @param[out] TDC : The terminally differentiated cell to generate
    *   @param[in,out] taCells : The deque containing all the TA cells in the environment
    *   @return 0
    */
    int differentiate(Cell& TDC, std::deque<TACell> &tacells);

    /**
    *   @brief               Method for division of Transit Amplifying Cells
    *   @param[out]  daughter: The new daughter cell generated
    *   @pram[in]        environment: The simulation environment lattice
    *   @pram[in]        sim: The simulation parameters
    *   @return            The function returns the following values
    *                               Return Value | Meaning
    *                               -------------------|-------------
    *                               0              | A daughter was created
    *                               -1            | No suitable location was found
    */
    int divide(TACell& daughter, int id_, AutomatonCell ***environment, SimulationParameters sim);
};

#endif // TACELL_H
