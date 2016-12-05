#ifndef _COORDINATE_H_
#define _COORDINATE_H_

class Coordinate {
int xCoord;
int yCoord;

public:
	Coordinate setCoord(int x, int y);
	~Coordinate();
	void getCoord(Coordinate *c);
	int getX(Coordinate *c);
	int getY(Coordinate *c);
};
#endif
