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
    int betaCount;
    int beta;

public:
    TACell();

    /**
    *   @brief  Method to return the value of beta counter
    *   @return The value of betaCounter
    */
    int getBetaCount();

    /**
    *   @brief  Method to set the value of betaCounter
    *   @param  The value of betaCounter
    *   @return 0
    */
    int setBetaCount(int betaCount_);

     /**
    *   @brief  Method to return the value of Beta
    *   @return The value of Beta
    */
    int getBeta();

    /**
    *   @brief  Method to set the value of Beta
    *   @param  The new value of Beta
    *   @return 0
    */
    int setBeta(int beta_);

    /**
    *   @brief  Method to increment the value of betaCounter
    *   @return Current value of Beta
    */
    int incrementBetaCount();

    /**
    *   @brief Function for differentiating  the Transit Amplifying Cell
    *   @param[out] TDC : The terminally differentiated cell to generate
    *   @param[in,out] environment : The simulation environment lattice
    *   @param[in]  id_ : The id of the TDC to be generated
    *   @return 0
    */
    int differentiate(Cell& TDC, AutomatonCell ***environment, int id_);

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
