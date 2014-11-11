#include "Line.h"
#include<iostream>

Line::Line():id(0),numberOfPoints(0),point(NULL) {
}

Line::~Line() {
    delete[] point;
}


Line::Line(int numberOfPoints_):id(0),numberOfPoints(numberOfPoints_),point(NULL) {
    this->point=new Point[numberOfPoints_];
}

Line::Line(int id_, int numberOfPoints_):id(id_),numberOfPoints(numberOfPoints_),point(NULL) {
    this->point=new Point[numberOfPoints_];
}

Line Line::operator=(const Line& obj) {
    Line line(obj.getId(),obj.getNumberOfPoints());
    for(int i=0;i<obj.getNumberOfPoints();i++){
        line.setPoint(i,obj.getPoint(i));
    }
    return line;
}

long int Line::getId() const {
		return id;
	}

int Line::setId(long int id_) {
    this->id = id_;
    return 0;
}

int Line::getNumberOfPoints() const {
    return numberOfPoints;
}

Point Line::getPoint(int index) const
{
    return point[index];
}

int Line::setPoint(int index, Point pt)
{
    point[index].setX(pt.getX());
    point[index].setY(pt.getY());
    point[index].setZ(pt.getZ());
    return 0;
}

int Line::getPointArray(Point* pt) const
{
    pt=new Point[numberOfPoints];
    for(int i=0; i<numberOfPoints; i++)
    {
        pt[i].setX(point[i].getX());
        pt[i].setY(point[i].getY());
        pt[i].setZ(point[i].getZ());
    }
    return 0;
}

int Line::setPointArray(int numberOfPoints, Point* ptArray)
{
    this->numberOfPoints=numberOfPoints;
    point=new Point[numberOfPoints];
    for(int i=0; i<numberOfPoints; i++)
    {
        point[i].setX(ptArray[i].getX());
        point[i].setY(ptArray[i].getY());
        point[i].setZ(ptArray[i].getZ());
    }
    return 0;
}

