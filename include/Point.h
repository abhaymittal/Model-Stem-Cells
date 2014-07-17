#ifndef POINT_H_
#define POINT_H_


class Point
{
private:
    int x;  /**< @brief The x coordinate value*/
    int y;  /**< @brief The y coordinate value*/
    int z;  /**< @brief The z coordinate value*/

public:

    /**
    *   @brief  Default Constructor
    */
    Point();

    /**
    *   @brief  A three argument constructor
    *   @param  x_ : The x coordinate value
    *   @param  y_ : The y coordinate value
    *   @param  z_ : The z coordinate value
    */
    Point(int x_, int y_, int z_);

    /**
    *   @brief  Getter function for the x coordinate value
    *   @return The x coordinate value
    */
    int getX() const;

    /**
    *   @brief  Setter function for the x coordinate value
    *   @param  x_ : The x coordinate value
    *   @return Nothing
    */
	void setX(int x_);

    /**
    *   @brief  Getter function for the y coordinate value
    *   @return The y coordinate value
    */
	int getY() const;

    /**
    *   @brief  Setter function for the y coordinate value
    *   @param  y_ : The y coordinate value
    *   @return Nothing
    */
	void setY(int y_);

	/**
    *   @brief  Getter function for the z coordinate value
    *   @return The z coordinate value
    */
	int getZ() const;

    /**
    *   @brief  Setter function for the z coordinate value
    *   @param  z_ : The z coordinate value
    *   @return Nothing
    */
	void setZ(int z);

    /**
    *   @brief  Getter function for the varName coordinate value
    *   @param  varName : The name of the coordinate whose value is to be retrieved
    *   @return The value of the varName coordinate
    */
    int getVar(char varName);

    /**
    *   @brief  Setter function for the varName coordinate value
    *   @param  varName : The name of the coordinate whose value is to be set
    *   @param  value : The value to be set
    *   @return 0
    */
    int setVar(char varName, int value);

};

#endif // POINT_H_
