#include <iostream>
#include <map>
#include "tblock.h"

using namespace std;

map<string, int> tblock::updateRows(map<string, int> returnRows, string** board) {
for(int i=0;i<15;i++){
	for(int j=0;j<11;j++){
		cout<<board[i][j];
	}
	cout<<endl;
}
return returnRows;
}

void tblock::drop(map<string, int> returnRows, string** board) {}

void tblock::fillBlock(string** board){
for(int i=0;i<4;i++){
Coordinate *c=blockCoord[i];
int x=c->getX(c);
int y=c->getY(c);
cout<<"("<<x<<", "<<y<<")"<<endl;
board[x][y]="T";
}
}

void tblock::initialize(){
blockCoord[0]=new Coordinate;
blockCoord[0]->setCoord(0, 0);

blockCoord[1]=new Coordinate;
blockCoord[1]->setCoord(0, 1);

blockCoord[2]=new Coordinate;
blockCoord[2]->setCoord(1, 1);

blockCoord[3]=new Coordinate;
blockCoord[3]->setCoord(0, 2);
}

void tblock::printBlock(){
for(int i=0;i<4;i++){
blockCoord[i]->getCoord(blockCoord[i]);
}
}
