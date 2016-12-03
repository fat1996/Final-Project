#include <iostream>
#include <map>
#include "oblock.h"

using namespace std;

// Constructor that sets type
oblock::oblock() : block{'O'} {}

void oblock::updateBoard(string** board){
for(int i=0;i<4;i++){
Coordinate *c=blockCoord[i];
int x=c->getX(c);
int y=c->getY(c);
cout<<"("<<x<<", "<<y<<")"<<endl;
board[x][y]="O";
}
}

void oblock::initialize(string** board, int level_num){
state=1;
level=level_num;
//set isHeavy.
if(level_num==0 || level_num==1 || level_num==2){
	isHeavy=false;
}
else {
	isHeavy=true;
}

carriedOver=new Coordinate;
carriedOver->setCoord(0, 0);

blockCoord[0]=new Coordinate;
blockCoord[0]->setCoord(3, 0);

blockCoord[1]=new Coordinate;
blockCoord[1]->setCoord(3, 1);

blockCoord[2]=new Coordinate;
blockCoord[2]->setCoord(4, 0);

blockCoord[3]=new Coordinate;
blockCoord[3]->setCoord(4, 1);

for(int i=0;i<4;i++){
Coordinate *c=blockCoord[i];
int x=c->getX(c);
int y=c->getY(c);
cout<<"("<<x<<", "<<y<<")"<<endl;
board[x][y]="O";
}
}

void oblock::clockwise(string** board){
//call heavy function after every move.
this->Heavy(board);
}

void oblock::anticlockwise(string** board){
//call heavy function after every move.
this->Heavy(board);
}