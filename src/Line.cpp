#include "Line.h"

Line::Line() {
	// TODO Auto-generated constructor stub

}

Line::~Line() {
	// TODO Auto-generated destructor stub
}

Line::Line(int numberOfPoints)
{
    this->numberOfPoints=numberOfPoints;
    this->point=new Point[numberOfPoints];
}

Line::Line(int id, int numberOfPoints)
{
    this->id=id;
    this->numberOfPoints=numberOfPoints;
    this->point=new Point[numberOfPoints];
}

Point Line::getPoint(int index)
{
    return point[index];
}

int Line::setPoint(int index, Point pt)
{
    point[index]=pt;
    return 0;
}

Point* Line::getPointArray()
{
    Point *pt;
    pt=new Point[numberOfPoints];
    for(int i=0; i<numberOfPoints; i++)
    {
        pt[i]=point[i];
    }
    return pt;
}

int Line::setPointArray(int numberOfPoints, Point* ptArray)
{
    this->numberOfPoints=numberOfPoints;
    point=new Point[numberOfPoints];
    for(int i=0; i<numberOfPoints; i++)
    {
        point[i]=ptArray[i];
    }
    return 0;
}

