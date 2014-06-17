#ifndef VAR_H
#define VAR_H

/**
*   @class  Var
*   @brief  Class representing a coordinate variable
*   @author Abhay Mittal
*   @author Pratik Varshney
*/
class Var
{
    private:

    char var_name;  /**<The name of the variable coordinate, e.g. - x*/
    int delta;      /**<The delta value of the coordinate of variable*/
    int value;      /**<Current value of the variable*/

    public:

    /**
    *   @brief  Default no argument constructor
    */
    Var()
    {}

    /**
    *   @brief  A three argument constructor for initializing the parameters of variable
    *   @param  var_n the variable coordinate name
    *   @param  del the delta value of the variable coordinate
    *   @param  val the current value of the variable
    */
    Var(int var_n,int del, int val):var_name(var_n),delta(del),value(val)
    {}

    /**
    *   @brief  Getter function for variable coordinate name
    *   @return The name of the variable coordinate
    */
    char get_var_name();

    /**
    *   @brief  Setter function for variable coordinate name
    *   @param  var_x  the new coordinate name of the variable
    *   @return 0
    */
    int set_var_name(char var_x);

    /**
    *   @brief  Getter function for the delta value of the variable coordinate.
    *   @return The delta value of the variable coordinate
    */
    int get_delta();

    /**
    *   @brief  Setter function for the delta value of the variable coordinate
    *   @param  del the new delta value of the coordinate
    *   @return 0
    */
    int set_delta(int del);

    /**
    *   @brief  Getter function for the current value of the variable.
    *   @return The current value of the variable
    */
    int get_value();

    /**
    *   @brief  Setter function for the current value of the variable
    *   @param  val the new value of the variable
    *   @return 0
    */
    int set_value(int val);
};
#endif // VAR_H
