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
    public:
        TACell();
        /**
        *   @brief Function for differentiating  the Transit Amplifying Cell
        *
        */
    int differentiate();
};

#endif // TACELL_H
