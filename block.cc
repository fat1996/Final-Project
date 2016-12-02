#include <iostream>
#include "coordinate.h"
#include "block.h"

using namespace std;

block::~block() { 
	for(int i=0 ; i<4; i++) {
		delete blockCoord[i];
	}
}

void block::updateScore(string **board, map<int, int> emptyRows){
cout<<"Drop has been executed. Check if any rows are completely filled and update grid."<<endl;

for(int i=bottomRow;i>=1;i--){
	cout<<"Row number: "<<i<<", val: "<<emptyRows[i]<<endl;
if(emptyRows[i]==2){  //row is completely full.
cout<<"Row: "<<i<<" is full."<<endl;

for(int i1=i;i1>=1;i1--){
	for(int j1=0;j1<rightBorder;j1++){
		int upperRow=i1-1;
		board[i1][j1]=board[upperRow][j1];
	}
}
break;
}
}

cout<<"the grid has been updated. This is what it looks like: "<<endl;
for(int i=0;i<=bottomRow;i++){
	for(int j=0;j<rightBorder;j++){
		cout<<board[i][j];
	}
	cout<<endl;
}

emptyRows=updateRows(emptyRows, board);


cout<<"emptyRows has been updated. This is what it looks like: "<<endl;
for(int i=0;i<=bottomRow;i++){
	cout<<"Index: "<<i<<", val: "<<emptyRows[i]<<endl;
}

for(int i=0;i<=bottomRow;i++){
	if(emptyRows[i]==2){
		updateScore(board, updateRows(emptyRows, board));
		break;
	}
}

cout<<"Everything has been UPDATED. FINAL LOOK OF THE GRID: "<<endl;
for(int i=0;i<=bottomRow;i++){
	for(int j=0;j<rightBorder;j++){
		cout<<board[i][j];
	}
	cout<<endl;
}
}

void block::Heavy(string **board){
cout<<"This block was generated on level: "<<level<<endl;
if(level>=3){
this->down(board);
}
}

void block::printBlock(){
for(int i=0;i<4;i++){
blockCoord[i]->getCoord(blockCoord[i]);
}
}


map<int, int> block::updateRows(map<int, int> returnRows, string** board) {
cout<<"Function updateRows running"<<endl;
//cout<<"This is what the grid looks like rn: "<<endl;
for(int i=0;i<=bottomRow;i++){
int count=0;
for(int j=0;j<rightBorder;j++){
//cout<<board[i][j];
if(board[i][j]==" ")
{
++count;
}		
}
//cout<<endl;
if(count==0){  //all the cells are completely filled.
returnRows[i]=2;  //not empty.
}
else if(count==rowCap){
returnRows[i]=0;
}
else{
returnRows[i]=1;
}
cout<<"Row: "<<i<<", count: "<<returnRows[i]<<endl;
}
return returnRows;
}

bool block::isPresent(int x, int y){
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

//the bottom-most row is the one with the highest index.
void block::drop(map<int, int> returnRows, string** board) {
returnRows=updateRows(returnRows, board);

cout<<"BOARD: "<<endl;
for(int i=0;i<=bottomRow;i++){
	for(int j=0;j<rightBorder;j++){
		cout<<board[i][j];
	}
	cout<<endl;
}

//Iterate through the map of rows, to check if the bottommost row is empty or not.
for(int i=bottomRow;i>=0;i--) 
{
int index=i;
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

else if(returnRows[i]==2)  //completely filled.
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
//updateRows(returnRows, board);
// emptyRows needs to be updated once the block has been dropped.
}

void block::left(string** board){
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
int count=0;
for(int i=0;i<4;i++){
Coordinate *c=blockCoord[i];
int x=c->getX(c);
int y=c->getY(c);
y=y-1;
if(board[x][y]==" " || isPresent(x, y)==true){
	++count;
}
}

if(count==4){  //perfect fit.
//new coordinates created.
for(int i=0;i<4;i++){
Coordinate *c=blockCoord[i];
int x=c->getX(c);
int y=c->getY(c);
board[x][y]=" ";
y=y-1;
blockCoord[i]->setCoord(x, y);
}
}
//update carriedOver.
int x=carriedOver->getX(carriedOver);
int y=carriedOver->getY(carriedOver);
y=y-1;
carriedOver->setCoord(x, y);
cout<<"carriedOver has been updated: "<<carriedOver->getX(carriedOver)<<", "<<carriedOver->getY(carriedOver)<<endl;
}

}

void block::right(string** board){

//you need to determine the left-most x-coordinate.

int maxX;
int index=0;
//determining the rightmost x-coord(the largest value of x).
for(int i=0;i<4;i++){
Coordinate *c=blockCoord[i];
int y=c->getY(c);

if(i==0) maxX=y;
else {
if(y>maxX) {
maxX=y;
index=i;
} } }
cout<<"maxX: "<<maxX<<", index: "<<index<<endl;

if(maxX==rightBorder){} //move cannot be made.
else {  //move can be made, but you need to check if the cell next to the rightmost edge of the block is empty or not.
int count=0;
for(int i=0;i<4;i++){
Coordinate *c=blockCoord[i];
int x=c->getX(c);
int y=c->getY(c);
y=y+1;
if(y==rightBorder){
	//move cant be made. index out of array. will give segmentation fault.
}
else {
if(board[x][y]==" " || isPresent(x, y)==true){
	++count;
}}}

if(count==4){  //perfect fit.
//new coordinates created.
for(int i=0;i<4;i++){
Coordinate *c=blockCoord[i];
int x=c->getX(c);
int y=c->getY(c);
board[x][y]=" ";
y=y+1;
blockCoord[i]->setCoord(x, y);
}
}
int x=carriedOver->getX(carriedOver);
int y=carriedOver->getY(carriedOver);
y=y+1;
carriedOver->setCoord(x, y);
cout<<"carriedOver has been updated: "<<carriedOver->getX(carriedOver)<<", "<<carriedOver->getY(carriedOver)<<endl;
}
//call heavy function after every move.
//this->Heavy(board);
}

void block::down(string** board){
//you need to determine the bottom-most x-coordinate.

int maxX;
//determining the bottommost x-coord(the largest value of x).
for(int i=0;i<4;i++){
Coordinate *c=blockCoord[i];
int y=c->getX(c);

if(i==0) maxX=y;
else{
if(y>maxX) {
maxX=y;
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
}
//update carriedOver.
int x=carriedOver->getX(carriedOver);
int y=carriedOver->getY(carriedOver);
x=x+1;
carriedOver->setCoord(x, y);
cout<<"carriedOver has been updated: "<<carriedOver->getX(carriedOver)<<", "<<carriedOver->getY(carriedOver)<<endl;
}}
//call heavy function after every move.
//this->Heavy(board);
}



