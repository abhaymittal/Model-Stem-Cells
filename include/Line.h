#ifndef LINE_H_
#define LINE_H_
#include "Point.h"


class Line
{
private:
    long int id;
    int numberOfPoints;
    Point *point;

public:

    Line();
    Line(int numberOfPoints);
    Line(int id, int numberOfPoints);
    virtual ~Line();

    long int getId() const {
		return id;
	}

	void setId(long int id) {
		this->id = id;
	}

	int getNumberOfPoints() const {
		return numberOfPoints;
	}

    Point getPoint(int index);
    int setPoint(int index, Point pt);

    int Line::getPointArray(Point* pt);
    int setPointArray(int numberOfPoints, Point* ptArray);

};

#endif // LINE_H_
