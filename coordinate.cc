#include <iostream>
#include "coordinate.h"

using namespace std;

Coordinate Coordinate::setCoord(int x, int y){
xCoord=x;
yCoord=y;
return *this;
}

void Coordinate::getCoord(Coordinate *c){
int x=c->xCoord;
int y=c->yCoord;

cout<<"The co-ordinates are: "<<x<<", "<<y<<endl;
}

int Coordinate::getX(Coordinate *c){
return c->xCoord;
}

int Coordinate::getY(Coordinate *c){
return c->yCoord;
}
