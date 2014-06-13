#ifndef LINE_3D_H
#define LINE_3D_H
#include "Point_3d.h"

/**
*   @class  Line_3d
*   @brief  Class representing a line in a three dimensional plane
*   @author Abhay Mittal
*   @author Pratik Varshney
*/
class Line_3d
{
    private:
    long id;            /**<The unique id of the line*/
    int no_point;       /**<Number of points sampled in the line*/
    Point_3d *point;    /**<An array consisting of the points sampled*/

    public:

    /**
    *   @brief  A single argument constructor
    *   @param  n_point the number of points in the line
    */
    Line_3d(int n_point);

    /**
    *   @brief  A two argument constructor
    *   @param  _id the unique id of the line
    *   @param  n_point the number of points in the line
    */
    Line_3d(int _id, int n_point);

    /**
    *   @brief  Getter function for the id of the line
    *   @return id of the line
    */
    long get_id();

    /**
    *   @brief  Setter function for the id of the line
    *   @param  _id new id of the line
    *   @return 0
    */
    int set_id(long _id);

    /**
    *   @brief  Getter function for the number of sampled points
    *   @return number of sampled points
    */
    int get_no_point();

    /**
    *   @brief  Setter function for the number of sampled points
    *   @param  _no_point the number of sampled points
    *   @return 0
    */
    int set_no_point(int _no_point);

    /**
    *   @brief  Setter function for setting the value of a particular sampled point
    *   @param  index the index of the sampled point
    *   @param  pt the details of the point
    *   @return 0
    */
    int set_point(int index,Point_3d pt);

    /**
    *   @brief  Getter function for getting the value of a particular sampled point
    *   @param  index the index of the sampled point
    *   @return the details of the point
    */
    Point_3d get_point(int index);

    /**
    *   @brief  Setter function for setting a whole array of sampled points
    *   @param  n_point the number of points in the array
    *   @param  p_array the array of sampled points
    *   @return 0
    */
    int set_point_array(int n_point, Point_3d* p_array);

    /**
    *   @brief  Getter function for retrieving an array of all the sampled points
    *   @return The sampled points array
    */
    Point_3d* get_point_array();

};


#endif // LINE_3D_H
