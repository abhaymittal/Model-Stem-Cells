#ifndef CELL_H
#define CELL_H

/**
*   @class  Cell
*   @brief  Class representing a cell
*   @author Abhay Mittal
*   @author Pratik Varshney
*/

class Cell
{
    private:
        long int id;
        Point centroid;
        int radius;
        int senseRadius;
    public:
        /** Default constructor */
        Cell();

        /** Default destructor */
        virtual ~Cell();

        long int getId() const {
            return id;
        }

        int setId(long id_) {
            id=id_;
            return 0;
        }

        int getRadius() const {
            return radius;
        }
        int setRadius(int radius_) {
            radius=radius_;
            return 0;
        }

        int getSenseRadius() const {
            return senseRadius;
        }
        int setSenseRadius(int senseRadius_) {
            senseRadius=senseRadius_;
            return 0;
        }

        Point getCentroid() const {
            return centroid;
        }
        int setCentroid(Point centroid_) {
            centroid=centroid_;
            return 0;
        }

        // End of setter and getter functions

        /**
        *   This method creates ablah blahc blachsdjaihfi
        *   @brief  Function for creating cells in the environment
        *   @param  cellCount   The number of cells to create
        *   @param  Radius  The radius of each cell
        *   @param  SenseRad    The sensing radius of each cell
        *   @param  *cell   An array of cells
        *   @param  *pixels An array of pixels
        */
    protected:
};

#endif // CELL_H
