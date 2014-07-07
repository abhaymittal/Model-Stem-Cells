#ifndef CELL_H
#define CELL_H

#include "Point.h"
/**
*   @class  Cell
*   @brief  Class representing a cell
*   @author Abhay Mittal
*   @author Pratik Varshney
*/

class Cell
{

    private:
        long int id;        /**<The id of cell*/
        Point centroid;     /**<The centroid of the cell*/
        int radius;         /**<The radius of the cell*/
        int senseRadius;    /**<The sensing radius of the cell*/
        float eCadherin;    /**<A protein named ECadherin*/
        float EB;           /**<Denotes ECadherin-Beta Cadherin*/

    public:

        /** Default constructor */
        Cell();


        /** Default destructor */
        virtual ~Cell();

        long int getId() const;
        int setId(long id_);
        int getRadius() const;
        int setRadius(int radius_);
        int getSenseRadius() const;
        int setSenseRadius(int senseRadius_);
        Point getCentroid() const;
        int setCentroid(Point centroid_);
        int setECadherin(float eCadherin_);
        float getECadherin() const;
        int setEB(float EB_);
        float getEB() const;


};

#endif // CELL_H
