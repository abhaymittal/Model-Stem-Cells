/**
*   @class StemCell
*   @brief This class models the Stem Cells and is derived from the Cell class
*   @author Abhay Mittal
*   @author Pratik Varshney
*/

#ifndef STEMCELL_H
#define STEMCELL_H

#include "Cell.h"


class StemCell : public Cell
{
    public:

        StemCell();

        int divide(StemCell& daughterCell, AutomatonCell ***environment, SimulationParameters sim);
        int divide(TACell& daughterCell, AutomatonCell*** environment,SimulationParameters sim);
};

#endif // STEMCELL_H
