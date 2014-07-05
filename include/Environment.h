#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H


#include "SimulationParameters.h"
#include "AutomatonCell.h"
#include "Point.h"
#include "Line.h"
#include "Var.h"
#include "Cell.h"

class Environment
{
    private:
        int drawRandomLine(SimulationParameters sim, Point box[8], int fiberLengthSqr, int zMaxSqr, int xMin, int xMax, int xRange, Line *outLine);
        int generatePtFreqMap(Line* line, SimulationParameters sim,AutomatonCell ***cells);
        Line drawLine(Point p1, Point p2);
    public:
        /** Default constructor */
        Environment();
        int setupECM(SimulationParameters sim,AutomatonCell ***ptFreqMap);
        int createCells(int cellCount, int radius, int senseRadius, SimulationParameters sim, Cell *cells, AutomatonCell ***environment);
};

#endif // ENVIRONMENT_H
