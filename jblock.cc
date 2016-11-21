#include <iostream>
#include <map>
#include <string>
#include "coordinate.h"
#include "jblock.h"

const int bottomRow=14;

using namespace std;

void jblock::drop(map<string, int> returnCells, map<string, int> returnRows, string** board) {
//1. Check if the bottom-most row is completely empty.
//2. If yes, drop.
//3. If no, 1st calculate what the new coordinates of the dropped block will be if it drops.
//4. for the new coord, check if those cells are empty or not and whether the block can fit.
//5. If yes, drop.
//6. If not, start checking upper rows.

//Iterate through the map of rows, to check if the bottommost row is empty or not.
for(map<string, int>::iterator it=returnRows.begin(); it!=returnRows.end(); ++it){
string rowIndex=to_string(bottomRow);
if(returnRows[rowIndex]==0){
cout<<"The bottom most row is completely empty."<<endl;
int maxRow=0;
for(int i=0;i<4;i++)
{
Coordinate *c=blockCoord[i];
int x=c->getX(c);
if(x>maxRow){
maxRow=x;
}
}
int delta=bottomRow-maxRow;
cout<<"Delta: "<<delta<<endl;

//set the new coordinates.
for(int j=0;j<4;j++){
Coordinate *c=blockCoord[j];
int x=c->getX(c);
int newX=x+delta;
int y=c->getY(c);  //y-coord stays the same.
board[x][y]=" ";
blockCoord[j]=new Coordinate;
blockCoord[j]->setCoord(newX, y);
}
break;
}
else {
cout<<"The bottom most is completely filled."<<endl;
}
}
}

void jblock::fillBlock(string** board){
for(int i=0;i<4;i++){
Coordinate *c=blockCoord[i];
int x=c->getX(c);
int y=c->getY(c);
cout<<"("<<x<<", "<<y<<")"<<endl;
board[x][y]="J";
}
}

void jblock::initialize(){
cout<<"Initializing jblock"<<endl;
blockCoord[0]=new Coordinate;
blockCoord[0]->setCoord(0, 0);
blockCoord[1]=new Coordinate;
blockCoord[1]->setCoord(1, 0);
blockCoord[2]=new Coordinate;
blockCoord[2]->setCoord(1, 1);
blockCoord[3]=new Coordinate;
blockCoord[3]->setCoord(1, 2);
}

void jblock::printBlock(){
for(int i=0;i<4;i++){
blockCoord[i]->getCoord(blockCoord[i]);
}
}
