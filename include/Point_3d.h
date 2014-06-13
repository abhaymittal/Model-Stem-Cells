#ifndef POINT_3D_H
#define POINT_3D_H

/**
* @class    Point_3d
* @brief    Class representing a three dimensional point
* @author   Abhay Mittal
* @author   Pratik Varshney
*/
class Point_3d
{
    private:
    int x;  /**< x-coordinate value of the point*/
    int y;  /**< y-coordinate value of the point*/
    int z;  /**< z-coordinate value of the point*/

    public:
    /**
    * @brief    The default no-arg constructor
    */
    Point_3d(){}

    /**
    *   @brief  A three argument constructor for setting the initial coordinates
    *   @param _x is the x-coordinate value
    *   @param _y is the y-coordinate value
    *   @param _z is the z-coordinate value
    */
    Point_3d(int _x,int _y, int _z):x(_x),y(_y),z(_z)
    {}

    /**
    * @brief    getter function for x-coordinate
    * @return   x-coordinate value
    */
    int get_x();

    /**
    * @brief    getter function for y-coordinate
    * @return   y-coordinate value
    */
    int get_y();

    /**
    * @brief    getter function for z-coordinate
    * @return   z-coordinate value
    */
    int get_z();

    /**
    * @brief    getter function for any one of the three coordinates
    * @param    var_name the name of the dimension ==> x, y or z
    * @return   the coordinate value
    */
    int get_var(char var_name);

    /**
    * @brief    setter function for x-coordinate
    * @param    xval the new value for the x-coordinate
    * @return   0
    */
    int set_x(int xval);

    /**
    * @brief    setter function for y-coordinate
    * @param    yval the new value for the y-coordinate
    * @return   0
    */
    int set_y(int yval);

    /**
    * @brief    setter function for z-coordinate
    * @param    zval the new value for the z-coordinate
    * @return   0
    */
    int set_z(int zval);

    /**
    * @brief    setter function for any one of the three coordinates
    * @param    var_name the name of the dimension ==> x, y or z
    * @param    val the new value of the dimension var_name
    * @return   0
    */
    int set_var(char var_name, int val);

};

#endif // POINT_3D_H
