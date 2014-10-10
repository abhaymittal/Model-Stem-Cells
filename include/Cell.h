/**
*   @class  Cell
*   @brief  Class representing a cell
*   @author Abhay Mittal
*   @author Pratik Varshney
*/

#ifndef CELL_H
#define CELL_H

#include "Point.h"


class Cell
{
private:
    long int id;        /**<The id of cell*/
    Point centroid;     /**<The centroid of the cell*/
    int radius;         /**<The radius of the cell*/
    int senseRadius;    /**<The sensing radius of the cell*/
    float eCadherin;    /**<A protein named ECadherin*/
    float EB;           /**<Denotes ECadherin-Beta Cadherin*/
    bool geneticCode[3];/**<An array of genetic code*/
    int age;            /**<The age of cell*/

public:

    /** Default constructor */
    Cell();


    /** Default destructor */
    virtual ~Cell();

    /**
    *   @brief  Getter function for the cell ID
    *   @return cell id
    */
    long int getId() const;

    /**
    *   @brief  Setter function for the cell ID
    *   @param  id_ : the cell id
    *   @return 0
    */
    int setId(long id_);

    /**
    *   @brief  Getter function for the cell radius
    *   @return radius of the cell
    */
    int getRadius() const;

    /**
    *   @brief  Setter function for the radius of the cell
    *   @param  radius_ : The radius of cell
    *   @return 0
    */
    int setRadius(int radius_);

    /**
    *   @brief  Getter function for the sensing radius of the cell
    *   @return sensing radius of the cell
    */
    int getSenseRadius() const;

    /**
    *   @brief  Setter function for the sensing radius
    *   @param  senseRadius_ : The sensing radius of the cell
    *   @return 0
    */
    int setSenseRadius(int senseRadius_);

    /**
    *   @brief  Getter function for the position of cell centroid
    *   @return Position of the centroid of the cell
    */
    Point getCentroid() const;

    /**
    *   @brief  Setter function for the position of centroid of the cell
    *   @param  centroid_ : The centroid position
    *   @return 0
    */
    int setCentroid(Point centroid_);

    /**
    *   @brief  Getter function for ECadherin value
    *   @return ECadherin value
    */
    float getECadherin() const;

    /**
    *   @brief  Setter function for ECadherin value
    *   @param  eCadherin_ : The ECadherin value
    *   @return 0
    */
    int setECadherin(float eCadherin_);

    /**
    *   @brief  Getter function for ECadherin-Beta Catenin value
    *   @return ECadherin-Beta Catenin value
    */
    float getEB() const;

    /**
    *   @brief  Setter function for the ECadherin-Beta Catenin value
    *   @param  EB_ : The ECadherin-Beta Catenin value
    *   @return 0
    */
    int setEB(float EB_);

    /**
    *   @brief  Getter function for genetic code array
    *   @param[out] The genetic code array
    *   @return 0
    */
    int getGeneticCode(bool *gCode) const;

    /**
    *   @brief  Getter function for genetic code value at particular index
    *   @param  index : The index value of the genetic code to be retrieved
    *   @return GeneticCode[index]
    */
    bool getGeneticCode(int index) const;


    /**
    *   @brief  Setter function for genetic code array
    *   @param  The genetic code array
    *   @return 0
    */
    int setGeneticCode(bool *gCode);

    /**
    *   @brief  Setter function for genetic code value at particular index
    *   @param  index : The index of the genetic code to be set
    *   @param  gC : The new value of genetic code
    *   @return 0
    */
    int setGeneticCode(int index,bool gC);

    /**
    *   @brief  Getter function for age of cell
    *   @return  the age of cell
    */
    int getAge();

    /**
    *   @brief  Setter function for age of cell
    *   @param  age_ : The new age of cell
    *   @return 0
    */
    int setAge(int age_);

    /**
    *   @brief  Age incrementer of cell.
    *   @return  New age
    */
    int incrementAge();

};

#endif // CELL_H
