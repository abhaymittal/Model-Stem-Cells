/**
*   @class StemCell
*   @brief This class models the Stem Cells and is derived from the Cell class
*   @author Abhay Mittal
*   @author Pratik Varshney
*/

#ifndef STEMCELL_H
#define STEMCELL_H

#include "Cell.h"
#include "TACell.h"


class StemCell : public Cell
{
    public:

        StemCell();

        /**
        *   @brief               Method for symmetric division of Stem Cell
        *   @param[out]  daughterCell: The new daughter cell generated
        *   @pram[in]        environment: The lattice
        *   @pram[in]        sim: The simulation parameters
        *   @return            The function returns the following values
        *                               Return Value | Meaning
        *                               -------------------|-------------
        *                               0              | A daughter was created
        *                               -1            | No suitable location was found
        */
        int divide(StemCell& daughterCell, AutomatonCell ***environment, SimulationParameters sim);

         /**
        *   @brief               Method for asymmetric division of Stem Cell
        *   @param[out]  daughterCell: The new daughter cell generated. It will be a Transit Amplifying Cell.
        *   @pram[in]        environment: The lattice
        *   @pram[in]        sim: The simulation parameters
        *   @return            The function returns the following values
        *                               Return Value | Meaning
        *                               -------------------|-------------
        *                               0              | A daughter was created
        *                               -1            | No suitable location was found
        */
        int divide(TACell& daughterCell, AutomatonCell*** environment,SimulationParameters sim);
};

#endif // STEMCELL_H
