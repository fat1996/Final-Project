#include <iostream>
#include <map>
#include "iblock.h"
#include "block.h"

using namespace std;

// Constructor that sets type
iblock::iblock() : block('I') {}

void iblock::clockwise(string** board){
cout<<"Current state of block: "<<state<<endl;

if(state==1){
cout<<"Current coordinates: "<<endl;
Coordinate *c=blockCoord[0];
int x=c->getX(c);
int y=c->getY(c);
for(int i=1;i<4;i++){
Coordinate *d=blockCoord[i];
int x1=d->getX(d);
int y1=d->getY(d);
if(x1<x && y1<y){
x=x1;
y=y1;
}
}
cout<<"Carried over: "<<x<<", "<<y<<endl;
carriedOver->setCoord(x, y);   //lowest x, lowest y.

//you know what the new set of coordinates are going to be.
//1st, check if those blocks are empty.
if((board[x][y]==" " || isPresent(x, y)==true) && 
	(board[x+1][y]==" " || isPresent(x+1, y)==true) && 
	(board[x+2][y]==" " || isPresent(x+2, y)==true) && 
	(board[x+3][y]==" " || isPresent(x+3, y)==true)){
for(int j=0;j<4;j++){
Coordinate *c=blockCoord[j];
int x=c->getX(c);
int y=c->getY(c);
board[x][y]=" ";  //the previous coordinates of the block are set to empty.
}
blockCoord[0]->setCoord(x, y);
blockCoord[1]->setCoord(x+1, y);
blockCoord[2]->setCoord(x+2, y);
blockCoord[3]->setCoord(x+3, y);
state=2;
}
}

else if(state==2){
int x=carriedOver->getX(carriedOver);
int y=carriedOver->getY(carriedOver);

cout<<"State: "<<state<<", carriedOver: "<<x<<", "<<y<<endl;

//you know what the new set of coordinates are going to be.
//1st, check if those blocks are empty.
if((board[x][y]==" " || isPresent(x, y)==true) && 
	(board[x][y+1]==" " || isPresent(x, y+1)==true) && 
	(board[x][y+2]==" " || isPresent(x, y+2)==true) && 
	(board[x][y+3]==" " || isPresent(x, y+3)==true)){
for(int j=0;j<4;j++){
Coordinate *c=blockCoord[j];
int x=c->getX(c);
int y=c->getY(c);
board[x][y]=" ";  //the previous coordinates of the block are set to empty.
}
blockCoord[0]->setCoord(x, y);
blockCoord[1]->setCoord(x, y+1);
blockCoord[2]->setCoord(x, y+2);
blockCoord[3]->setCoord(x, y+3);
state=1;
}
}
//call heavy function after every move.
this->Heavy(board);
}

void iblock::anticlockwise(string** board){
if(state==1){  //call cw 3 times.
	this->clockwise(board);
}
else if(state==2){  
	this->clockwise(board);
}
//call heavy function after every move.
this->Heavy(board);
}

void iblock::updateBoard(string** board){
for(int i=0;i<4;i++){
Coordinate *c=blockCoord[i];
int x=c->getX(c);
int y=c->getY(c);
cout<<"("<<x<<", "<<y<<")"<<endl;
board[x][y]="I";
}
}

void iblock::initialize(string** board, int level_num){

state=1;  //don't change. default state.
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
blockCoord[2]->setCoord(3, 2);

blockCoord[3]=new Coordinate;
blockCoord[3]->setCoord(3, 3);

for(int i=0;i<4;i++){
Coordinate *c=blockCoord[i];
int x=c->getX(c);
int y=c->getY(c);
cout<<"("<<x<<", "<<y<<")"<<endl;
board[x][y]="I";
}
}

