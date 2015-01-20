#ifndef LINE_H_
#define LINE_H_
/**
*   @class  Line
*   @brief  Class representing a line in 3d plane
*   @author Abhay Mittal
*   @author Pratik Varshney
*/

#include "Point.h"


class Line
{
private:
    long int id;            /**<The id of the line*/
    int numberOfPoints;     /**<The number of sampled points in the line*/
    Point *point;           /**<The array of sampled points in the line*/

public:

    /**
    *   @brief  Default no argument constructor
    */
    Line();

    /**
    *   @brief  A one argument constructor
    *   @param  numberOfPoints - The number of sampled points
    */
    Line(int numberOfPoints);

    /**
    *   @brief  A two argument constructor
    *   @param  id - The id of the line
    *   @param  numberOfPoints - The number of sampled points
    */
    Line(int id, int numberOfPoints);

    /**
    *   @brief  A virtual destructor
    */
    ~Line();
    /**
    *   @brief  Overloaded assignment operator
    *   @param  obj: The source object of Line class
    *   @return A new copy of the source object
    */
    Line operator=(const Line& obj);

    /**
    *   @brief  Getter function for the id
    *   @return The id of the line
    */
    long int getId() const;

    /**
    *   @brief  Setter function for the id
    *   @param  id - The id of the line
    *   @return 0
    */
    int setId(long int id);

    /**
    *   @brief  Getter function for the number of sampled points
    *   @return The number of sampled points in the line
    */
    int getNumberOfPoints() const;

    /**
    *   @brief  Set the number of points in the line (thereby create a new line)
    *   @param numberOfPoints_: The number of sampled points
    *   @return 0
    */
    int setNumberOfPoints(int numberOfPoints_);

    /**
    *   @brief  Getter function for getting a particular sampled point
    *   @param  index - The index of the point to return
    *   @return The sampled point at index
    */
    Point getPoint(int index) const;

    /**
    *   @brief  Setter function for setting a particular point at a particular index
    *   @param  index - The index of the point to be set
    *   @param  pt - The new sampled point
    *   @return 0
    */
    int setPoint(int index, Point pt);

    /**
    *   @brief  Getter function for the sampled point array
    *   @param  pt - Pointer to the sampled array to return
    *   @return The sampled point array
    */
    int getPointArray(Point* pt) const;

    /**
    *   @brief  Setter function for the sampled point array
    *   @param  numberofPoints - The number of sampled points in the array
    *   @param  ptArray - Pointer to the sampled array
    *   @return 0
    */
    int setPointArray(int numberOfPoints, Point* ptArray);

};

#endif // LINE_H_
