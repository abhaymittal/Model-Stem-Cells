#ifndef VAR_H_
#define VAR_H_

/**
*   @class  Var
*   @brief  Class representing a coordinate variable
*   @author Abhay Mittal
*   @author Pratik Varshney
*/
class Var
{
private:
    char varName;    /**<The name of the variable coordinate, e.g. - x*/
    int index;
    int delta;       /**<The delta value of the coordinate of variable*/
    int value;      /**<Current value of the variable*/

public:
    /**
    *   @brief  Default no argument constructor
    */
    Var();

    /**
    *   @brief  A three argument constructor for initializing the parameters of variable
    *   @param  varN the variable coordinate name
    *   @param  del the delta value of the variable coordinate
    *   @param  val the current value of the variable
    */
    Var(int varN, int ind, int del, int val):varName(varN),index(ind),delta(del),value(val)
    {}

    virtual ~Var();

    /**
     *   @brief  Getter function for variable coordinate name
     *   @return The name of the variable coordinate
     */
    char getVarName() const {
      return varName;
    }

    /**
    *   @brief  Setter function for variable coordinate name
    *   @param  varName  the new coordinate name of the variable
    *   @return 0
    */
    void setVarName(char varName) {
      this->varName = varName;
    }

    
    int getIndex() const {
      return index;
    }

    void setIndex(int index) {
      this->index = index;
    }

    /**
    *   @brief  Getter function for the delta value of the variable coordinate.
    *   @return The delta value of the variable coordinate
    */    
    int getDelta() const {
      return delta;
    }

    /**
    *   @brief  Setter function for the delta value of the variable coordinate
    *   @param  delta the new delta value of the coordinate
    *   @return 0
    */
    void setDelta(int delta) {
      this->delta = delta;
    }

    /**
    *   @brief  Getter function for the current value of the variable.
    *   @return The current value of the variable
    */
    int getValue() const {
      return value;
    }

    /**
    *   @brief  Setter function for the current value of the variable
    *   @param  value the new value of the variable
    *   @return 0
    */
    void setValue(int value) {
      this->value = value;
    }
};
#endif // VAR_H_
