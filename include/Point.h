#ifndef POINT_H_
#define POINT_H_


class Point
{
private:
    int x;
    int y;
    int z;

public:
    Point();
    Point(int _x, int _y, int _z):x(_x), y(_y), z(_z)
    {}
    virtual ~Point();

    Point& operator=(const Point& other);

    int getX() const {
		return x;
	}

	void setX(int x) {
		this->x = x;
	}

	int getY() const {
		return y;
	}

	void setY(int y) {
		this->y = y;
	}

	int getZ() const {
		return z;
	}

	void setZ(int z) {
		this->z = z;
	}


    int getVar(char varName);
    int setVar(char varName, int value);

};

#endif // POINT_H_
