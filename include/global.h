#ifndef GLOBAL_H_
#define GLOBAL_H_

/**
*   @brief  HEADER file for global variables
*   @author Abhay Mittal
*   @author Pratik Varshney
*/

using namespace std;

#include <deque>
#include "Cell.h"
#include "StemCell.h"
#include "TACell.h"

struct cellGroupStruct
{
    deque<Cell> normalCell;
    deque<StemCell> stemCell;
    deque<TACell> taCell;
};

typedef struct cellGroupStruct cellGroup;

#endif // GLOBAL_H_
