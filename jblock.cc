#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include "coordinate.h"
#include "jblock.h"

//const int bottomRow=14;
using namespace std;

jblock::~jblock(){
for(int i=0;i<4;i++){
delete blockCoord[i];
}
}

int jblock::lowestRow(map<string, int> returnRows){
int row=0;
int emptyRows=0;
int pfRows=0;

for(map<string, int>::iterator it=returnRows.begin(); it!=returnRows.end(); it++){
cout<<"Row: "<<it->first<<", "<<it->second<<endl;

int index;
string s=it->first;
stringstream ss(s);
ss>>index;
cout<<"EmptyRows: "<<index<<endl;

if(it->second==0){
if(emptyRows<index) emptyRows=index;
}
else if(it->second==1){
if(pfRows<index) pfRows=index;
}
}

cout<<"emptyRows: "<<emptyRows<<", pfRows: "<<pfRows<<endl;

if(emptyRows>pfRows){
row=emptyRows;
}
else{
row=pfRows;
}
cout<<"Returning: "<<row<<endl;
return row;
}

map<string, int> jblock::updateRows(map<string, int> returnRows, string** board) {
for(int i=0;i<15;i++){
int count=0;
for(int j=0;j<11;j++){
if(board[i][j]==" ")
{
++count;
}		
}
cout<<"Row: "<<i<<", count: "<<count<<endl;
if(count==0){  //all the cells are completely filled.
returnRows[to_string(i)]=2;  //not empty.
}
else if(count==11){
returnRows[to_string(i)]=0;
}
else{
returnRows[to_string(i)]=1;
}
}
return returnRows;
}

//the bottom-most row is the one with the highest index.
void jblock::drop(map<string, int> returnRows, string** board) {
int bottomRow=lowestRow(updateRows(returnRows, board));
cout<<"bottomRow: "<<bottomRow<<endl;


//Iterate through the map of rows, to check if the bottommost row is empty or not.
for(int i=bottomRow;i>=0;i--) 
{
string index=to_string(i);
cout<<"Index: "<<index<<endl;
if(returnRows[index]==1)  //not completely filled.
{
cout<<"Row "<<i<<" is not completely filled."<<endl;
int maxRow=0;

//this determines the lowest row of the block.
for(int i=0;i<4;i++)
{
Coordinate *c=blockCoord[i];
int x=c->getX(c);
if(x>maxRow){
maxRow=x;
}
}

int delta=bottomRow-maxRow;  //delta is what is added to the x-coord to get the new coord of the block
cout<<"Delta: "<<delta<<endl;
  
//determine the new coordinates.
for(int j=0;j<4;j++){
Coordinate *c=blockCoord[j];
int x=c->getX(c);
int newX=x+delta;
int y=c->getY(c);  //y-coord stays the same.
if(board[newX][y]==" "){ }
else {
	break;
}
if(j==3){   //all 4 cells are empty.
cout<<"Index: "<<x<<", "<<y<<" set to empty"<<endl;	
board[x][y]=" ";  //the previous coordinates of the block are set to empty.
	blockCoord[j]=new Coordinate;
	blockCoord[j]->setCoord(newX, y);
}
}
}

else if(returnRows[to_string(i)]==2)  //completely filled.
{
cout<<"Row "<<i<<" is completely filled."<<endl;
}

else {  //completely empty(0).
cout<<"Row "<<i<<" is completely empty."<<endl;
int maxRow=0;

//this determines the lowest row of the block.
for(int i=0;i<4;i++)
{
Coordinate *c=blockCoord[i];
int x=c->getX(c);
if(x>maxRow){
maxRow=x;
}
}


int delta=bottomRow-maxRow;  //delta is what is added to the x-coord to get the new coord of the block
cout<<"Delta: "<<delta<<endl;

//set the new coordinates.
for(int j=0;j<4;j++){
Coordinate *c=blockCoord[j];
int x=c->getX(c);
int newX=x+delta;
int y=c->getY(c);  //y-coord stays the same.
board[x][y]=" ";  //the previous coordinates of the block are set to empty.
blockCoord[j]=new Coordinate;
blockCoord[j]->setCoord(newX, y);
}
break;
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
