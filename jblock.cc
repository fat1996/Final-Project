#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include "coordinate.h"
#include "jblock.h"

const int bottomRow=14;
const int leftBorder=0;
const int rightBorder=11;
using namespace std;

//helper fn for drop and down.
//when you calculate a new set of coordinates, you have to see if those new coordinates are already the old coordinates of the block(in cases of overlap).
//this function returns true if the new coordinates have an overlap with the old coordinates of the block.
bool jblock::isPresent(int x, int y){
bool present=false;
for(int i=0;i<4;i++){
Coordinate *c=blockCoord[i];
	int x1=c->getX(c);
	int y1=c->getY(c);
	if(x==x1 && y==y1){
	cout<<x<<", "<<y<<" is already present"<<endl;
	present=true;
	break;
}
}
return present;
}

jblock::~jblock(){
for(int i=0;i<4;i++){
delete blockCoord[i];
}
}

void jblock::left(string** board){
//you need to determine the left-most x-coordinate.

int minX;
int index=0;  //index at which the smallest x is.
//determining the leftmost x-coord(the smallest value of x).
for(int i=0;i<4;i++){
Coordinate *c=blockCoord[i];
int x=c->getY(c);  

if(i==0) minX=x;
else{
if(x<minX){
 minX=x;
index=i;
}
} }
cout<<"minX: "<<minX<<", index: "<<index<<endl;

if(minX==leftBorder){} //move cannot be made. 
else{  
Coordinate *c=blockCoord[index];  
int x=c->getX(c);
int y=c->getY(c);
y=y-1;
if(board[x][y]==" "){   //perfect fit.
for(int i=0;i<4;i++){
Coordinate *c=blockCoord[i];
int x=c->getX(c);
int y=c->getY(c);
board[x][y]=" ";
y=y-1;
blockCoord[i]=new Coordinate;
blockCoord[i]->setCoord(x, y);
}
}
}
}

void jblock::right(string** board){
//you need to determine the left-most x-coordinate.

int maxX;
int index=0;
//determining the rightmost x-coord(the largest value of x).
for(int i=0;i<4;i++){
Coordinate *c=blockCoord[i];
int y=c->getY(c);

if(i==0) maxX=y;
else{
if(y>maxX) {
maxX=y;
index=i;
} } }
cout<<"maxX: "<<maxX<<", index: "<<index<<endl;

if(maxX==rightBorder){} //move cannot be made.
else{  //move can be made, but you need to check if the cell next to the rightmost edge of the block is empty or not.
Coordinate *c=blockCoord[index];  //replace with a const.
int x=c->getX(c);
int y=c->getY(c);
y=y+1;

if(board[x][y]==" "){
cout<<"We have a perfect fit!"<<endl;
//new coordinates created.
for(int i=0;i<4;i++){
Coordinate *c=blockCoord[i];
int x=c->getX(c);
int y=c->getY(c);
board[x][y]=" ";
y=y+1;
blockCoord[i]=new Coordinate;
blockCoord[i]->setCoord(x, y);
}}}}

void jblock::down(string** board){
//you need to determine the bottom-most x-coordinate.

int maxX;
//int index=0;
//determining the bottommost x-coord(the largest value of x).
for(int i=0;i<4;i++){
Coordinate *c=blockCoord[i];
int y=c->getY(c);

if(i==0) maxX=y;
else{
if(y>maxX) {
maxX=y;
//index=i;
} } }
cout<<"maxX: "<<maxX<<endl;

if(maxX==bottomRow){} //move cannot be made.
else{  //move can be made, but you need to check if the 4 cells of the block can shift down completely.
	//this will invoke isPresent as well.

//int delta=i-maxRow;  //delta is what is added to the x-coord to get the new coord of the block
//cout<<"maxRow"<<maxRow<<", Delta: "<<delta<<endl;

int count=0;  
cout<<"New coordinates: "<<endl;
//determine the new coordinates.
for(int j=0;j<4;j++){
Coordinate *c=blockCoord[j];
int x=c->getX(c);
int newX=x+1;
int y=c->getY(c);  //y-coord stays the same.
cout<<j<<": "<<newX<<", "<<y<<endl;

bool Present=isPresent(newX, y);  //helper fn called.
//now, we have a new set of coordinates. check if these coordinates are empty. if yes, drop. if not, do the same process for a diff index(i).
if(board[newX][y]==" " || Present==true) ++count;
cout<<"Count: "<<count<<endl;
}

cout<<"count: "<<count<<endl;
if(count==4){   //If count==4(perfect fit), then you have to set the new co-ordinates.
for(int j=0;j<4;j++){
Coordinate *c=blockCoord[j];
int x=c->getX(c);
int y=c->getY(c);
int newX=x+1;
board[x][y]=" ";  //the previous coordinates of the block are set to empty.
blockCoord[j]=new Coordinate;
blockCoord[j]->setCoord(newX, y);
}}}}


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
returnRows=updateRows(returnRows, board);

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
} }

int delta=i-maxRow;  //delta is what is added to the x-coord to get the new coord of the block
cout<<"maxRow"<<maxRow<<", Delta: "<<delta<<endl;

int count=0;  
cout<<"New coordinates: "<<endl;
//determine the new coordinates.
for(int j=0;j<4;j++){
Coordinate *c=blockCoord[j];
int x=c->getX(c);
int newX=x+delta;
int y=c->getY(c);  //y-coord stays the same.
cout<<j<<": "<<newX<<", "<<y<<endl;

bool Present=isPresent(newX, y);  //helper fn called.
//now, we have a new set of coordinates. check if these coordinates are empty. if yes, drop. if not, do the same process for a diff index(i).
if(board[newX][y]==" " || Present==true) ++count;
cout<<"Count: "<<count<<endl;
}

cout<<"count: "<<count<<endl;
if(count==4){
//If count==3(perfect fit), then you have to set the new co-ordinates.
for(int j=0;j<4;j++){
Coordinate *c=blockCoord[j];
int x=c->getX(c);
int y=c->getY(c);
int newX=x+delta;
board[x][y]=" ";  //the previous coordinates of the block are set to empty.
blockCoord[j]=new Coordinate;
blockCoord[j]->setCoord(newX, y);
}
break;
}

}

else if(returnRows[to_string(i)]==2)  //completely filled.
{
cout<<"Row "<<i<<" is completely filled."<<endl;
}


/*******************************************************************************************/
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
int delta=i-maxRow;  //delta is what is added to the x-coord to get the new coord of the block
cout<<"Delta: "<<delta<<endl;

cout<<"Previous coord: "<<endl;
//set the new coordinates.
for(int j=0;j<4;j++){
Coordinate *c=blockCoord[j];
int x=c->getX(c);
int newX=x+delta;
int y=c->getY(c);  //y-coord stays the same.
cout<<j<<": "<<x<<", "<<y<<endl;
board[x][y]=" ";  //the previous coordinates of the block are set to empty.
blockCoord[j]=new Coordinate;
blockCoord[j]->setCoord(newX, y);
}
break;
}
/*******************************************************************************************/
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
