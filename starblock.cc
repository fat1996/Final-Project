#include <iostream>
#include <vector>
#include "coordinate.h"
#include "starblock.h"
#include "block.h"

using namespace std;

// Constructor that sets type
starBlock::starBlock() : block('*'), level_num{4} {
	position = new Coordinate;
	position->setCoord(3, 6);
}

// Default destructor
StarBlock::~starBlock() {}

// Destructor for dropped starblock
StarBlock::deleteBlock() {
	delete position;
}

void StarBlock::updateBoard(std::string** board);

void StarBlock::drop(std::map<int, int> returnRows, std::string** board, std::vector<history*> &ongrid){
returnRows=updateRows(returnRows, board);
history *h=new history();
vector<Coordinate*> v=h->accessGrid();

int maxRow=3;
for(int i=1;i<=bottomRow-maxRow;i++){

int delta=i;  //delta is what is added to the x-coord to get the new coord of the block
//cout<<"maxRow"<<maxRow<<", Delta: "<<delta<<endl;

int count=0;  
//determine the new coordinates.
Coordinate c;
int x=c->getX(c);
int newX=x+delta;
int y=c->getY(c);  //y-coord stays the same.
//now, we have a new set of coordinates. check if these coordinates are empty. if yes, drop. if not, do the same process for a diff index(i).
if(board[newX][y]==" "){
	++count;
} 

//cout<<"count: "<<count<<endl;
if(count==1){}
else { 
//cout<<"this is where count!=4: "<<i<<endl;
Coordinate c;
int x=c->getX(c);
int y=c->getY(c);
int newX=x+delta-1;
board[x][y]=" ";  //the previous coordinates of the block are set to empty.
c=new Coordinate;
c->setCoord(newX, y);
v.push_back(c);
//cout<<"New coord: "<<newX<<", "<<y<<endl;
break;
}

if(i==bottomRow-maxRow){
Coordinate *c=Position;
int x=c->getX(c);
int y=c->getY(c);
int newX=x+bottomRow-maxRow;
board[x][y]=" ";  //the previous coordinates of the block are set to empty.
c=new Coordinate;
c->setCoord(newX, y);
v.push_back(c);
break;
}
}

h->accessGrid()=v;
h->getLevel()=level;
int size=h->accessGrid().size();
cout<<"SIZE: "<<size<<endl;
ongrid.push_back(h);
cout<<"Drop has been executed. size of array in grid.h"<<ongrid.size()<<endl;
}
