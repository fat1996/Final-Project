#include <iostream>
#include <vector>
#include "coordinate.h"
#include "block.h"
#include "history.h"

using namespace std;

//the bottom-most row is the one with the highest index.
void block::drop(map<int, int> returnRows, string** board, vector<history*> &ongrid, int level) {
returnRows=updateRows(returnRows, board);
history *h=new history();
vector<Coordinate*> v=h->accessGrid();
int maxRow=0;

cout<<"Block was generated on level: "<<level<<endl;

//this determines the lowest row of the block.
for(int i=0;i<4;i++)
{
Coordinate *c=blockCoord[i];
int x=c->getX(c);
if(x>maxRow){
maxRow=x;
} }

//this determines the lowest row of the block.
for(int i=0;i<4;i++)
{
Coordinate *c=blockCoord[i];
int x=c->getX(c);
if(x>maxRow){
maxRow=x;
} }

for(int i=1;i<=bottomRow-maxRow;i++){

int delta=i;  //delta is what is added to the x-coord to get the new coord of the block
//cout<<"maxRow"<<maxRow<<", Delta: "<<delta<<endl;

int count=0;  
//determine the new coordinates.
for(int j=0;j<4;j++){
Coordinate *c=blockCoord[j];
int x=c->getX(c);
int newX=x+delta;
int y=c->getY(c);  //y-coord stays the same.
bool Present=isPresent(newX, y);  //helper fn called.
//now, we have a new set of coordinates. check if these coordinates are empty. if yes, drop. if not, do the same process for a diff index(i).
if(board[newX][y]==" " || Present==true) ++count;
}

//cout<<"count: "<<count<<endl;
if(count==4){}
else { 
//cout<<"this is where count!=4: "<<i<<endl;
for(int j=0;j<4;j++){
Coordinate *c=blockCoord[j];
int x=c->getX(c);
int y=c->getY(c);
int newX=x+delta-1;
board[x][y]=" ";  //the previous coordinates of the block are set to empty.
blockCoord[j]=new Coordinate;
blockCoord[j]->setCoord(newX, y);
v.push_back(blockCoord[j]);
//cout<<"New coord: "<<newX<<", "<<y<<endl;
}
break;
}

if(i==bottomRow-maxRow){
	cout<<"we're at the last possibility"<<endl;
	int size=h->accessGrid().size();
	cout<<"SIZE: "<<size<<endl;
	for(int j=0;j<4;j++){
Coordinate *c=blockCoord[j];
int x=c->getX(c);
int y=c->getY(c);
int newX=x+bottomRow-maxRow;
board[x][y]=" ";  //the previous coordinates of the block are set to empty.
blockCoord[j]=new Coordinate;
blockCoord[j]->setCoord(newX, y);
v.push_back(blockCoord[j]);
//cout<<"New coord: "<<newX<<", "<<y<<endl;
}
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

// Constructor 
block::block(char c) {
	type = c;
}

// Typer gettor
char block::getType() {
	return type;
}

// Default destructor used for next block
block::~block() {}

// Destructor for initialized block
void block::deleteBlock() { 
	for(int i=0 ; i<4; i++) {
		delete blockCoord[i];
	}
}

bool block::updateScore(string **board, map<int, int> emptyRows, vector<history*> ongrid, int &counter, int &curScore, int &highScore, int curLevel, int &count){
cout<<"Drop has been executed. Check if any rows are completely filled and update grid."<<endl;
cout<<"CURSCORE: "<<curScore<<endl;
cout<<"blocks cleared: "<<count<<endl;
cout<<"size of ongrid vector: "<<ongrid.size()<<endl;

cout<<"BEFORE: "<<endl;
int s=ongrid.size();
for(int z=0;z<s;z++){
history *h=ongrid[z];
vector<Coordinate*> v=h->accessGrid();
int vsize=v.size();
cout<<"Size of vector: "<<vsize<<endl;
cout<<"Coordinates: "<<endl;
for(int a=0;a<vsize;a++){
	Coordinate *c=v[a];
	int x=c->getX(c);
	int y=c->getY(c);
		cout<<x<<", "<<y<<endl;
	}
}

for(int i=bottomRow;i>=1;i--){

if(emptyRows[i]==2){  //row is completely full.
cout<<"Row: "<<i<<" is full."<<endl;

//you need to look at all the coordinates in row i.
for(int j=0;j<rightBorder;j++){
int x=i;
int y=j;
//cout<<"Coordinate "<<j<<" of row "<<i<<": "<<x<<", "<<y<<endl;

//now you need to check if these coordinates exist in the vector of history objects.
int size=ongrid.size();
for(int z=0;z<size;z++){
history *h=ongrid[z];
vector<Coordinate*> v=h->accessGrid();
int vsize=v.size();
//cout<<"Orig size: "<<vsize<<endl;
for(int a=0;a<vsize;a++){
	Coordinate *c=v[a];
	int x1=c->getX(c);
	int y1=c->getY(c);
	if(x==x1 && y==y1){
		cout<<x<<", "<<y<<" exist"<<endl;
		v.erase(v.begin()+a);
	}}
h->accessGrid()=v;
cout<<"New size: "<<h->accessGrid().size()<<endl;
}}

cout<<"VECTOR HAS BEEN UPDATED."<<endl;
int size=ongrid.size();
for(int z=0;z<size;z++){
history *h=ongrid[z];
vector<Coordinate*> v=h->accessGrid();
int l=h->getLevel();
int vsize=v.size();
if(vsize==0){  //a block disappears.
	cout<<"a block disappears."<<endl;
	cout<<"SIZE BEFORE: "<<ongrid.size()<<endl;
	//this is where score gets updated.
	ongrid.erase(ongrid.begin()+z);
	curScore=curScore+((l*l)+1);
	//cout<<"curscore after clearing a block: "<<curScore<<endl;
	++count;
	cout<<"NEW SIZE OF ONGRID: "<<ongrid.size()<<endl;
	cout<<"COUNT: "<<count<<endl;
}
else {
	//cout<<"just a line disappears."<<endl;
}
}

cout<<"curScore: "<<curScore<<endl;
cout<<"NEW size of ongrid: "<<ongrid.size()<<endl;
++counter;

//this shifts everthing down.
for(int i1=i;i1>=1;i1--){
	for(int j1=0;j1<rightBorder;j1++){
		int upperRow=i1-1;
		board[i1][j1]=board[upperRow][j1];
	}
}
//you need to shift the vector of history objects down too.shit.
int big=ongrid.size();
for(int k=0;k<big;k++){
	history *h=ongrid[k];
	vector<Coordinate*> v=h->accessGrid();
	int small=v.size();
	for(int l=0;l<small;l++){
		Coordinate *c=v[l];
	int x1=c->getX(c);
	int y1=c->getY(c);
	v[l]->setCoord(x1+1, y1);
	}
	h->accessGrid()=v;
}

break;
}
}

emptyRows=updateRows(emptyRows, board);

cout<<"AFTER: "<<endl;
s=ongrid.size();
for(int z=0;z<s;z++){
history *h=ongrid[z];
vector<Coordinate*> v=h->accessGrid();
int vsize=v.size();
cout<<"Size of vector: "<<vsize<<endl;
cout<<"Coordinates: "<<endl;
for(int a=0;a<vsize;a++){
	Coordinate *c=v[a];
	int x=c->getX(c);
	int y=c->getY(c);
		cout<<x<<", "<<y<<endl;
	}
}

cout<<"Everything has been UPDATED. FINAL LOOK OF THE GRID: "<<endl;
for(int i=0;i<=bottomRow;i++){
	for(int j=0;j<rightBorder;j++){
		cout<<board[i][j];
	}
	cout<<endl;
}

for(int i=0;i<=bottomRow;i++){
	if(emptyRows[i]==2){
		updateScore(board, updateRows(emptyRows, board), ongrid, counter, curScore, highScore, curLevel, count);
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

cout<<"No of lines cleared: "<<counter<<endl;
cout<<"No of blocks cleared: "<<count<<endl;
cout<<"curLevel: "<<curLevel<<", curScore: "<<curScore<<endl;
curScore=((curLevel+counter)*(curLevel+counter))+curScore;

if(highScore<curScore){
	highScore=curScore;
}

cout<<"curScore: "<<curScore<<", highScore: "<<highScore<<endl;
cout<<"NEW size of ongrid: "<<ongrid.size()<<endl;

if(counter>0){
	return true;
}
else{
	return false;
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
//cout<<"Row: "<<i<<", count: "<<returnRows[i]<<endl;
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
	//cout<<x<<", "<<y<<" is already present"<<endl;
	present=true;
	break;
}
}
return present;
}

void block::left(string** board){
//you need to determine the left-most x-coordinate.

int minX;
//int index=0;  //index at which the smallest x is.
//determining the leftmost x-coord(the smallest value of x).
for(int i=0;i<4;i++){
Coordinate *c=blockCoord[i];
int x=c->getY(c);  

if(i==0) minX=x;
else{
if(x<minX){
 minX=x;
//index=i;
}
} }
//cout<<"minX: "<<minX<<", index: "<<index<<endl;

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
//update carriedOver.
int x=carriedOver->getX(carriedOver);
int y=carriedOver->getY(carriedOver);
y=y-1;
carriedOver->setCoord(x, y);
//cout<<"carriedOver has been updated: "<<carriedOver->getX(carriedOver)<<", "<<carriedOver->getY(carriedOver)<<endl;
}
}
}

void block::right(string** board){
//you need to determine the left-most x-coordinate.

int maxX;
//int index=0;
//determining the rightmost x-coord(the largest value of x).
for(int i=0;i<4;i++){
Coordinate *c=blockCoord[i];
int y=c->getY(c);

if(i==0) maxX=y;
else {
if(y>maxX) {
maxX=y;
//index=i;
} } }
//cout<<"maxX: "<<maxX<<", index: "<<index<<endl;

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
int x=carriedOver->getX(carriedOver);
int y=carriedOver->getY(carriedOver);
y=y+1;
carriedOver->setCoord(x, y);
//cout<<"carriedOver has been updated: "<<carriedOver->getX(carriedOver)<<", "<<carriedOver->getY(carriedOver)<<endl;
}
}
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
//cout<<"maxX: "<<maxX<<endl;

if(maxX==bottomRow){} //move cannot be made.
else{  //move can be made, but you need to check if the 4 cells of the block can shift down completely.

int count=0;  
//cout<<"New coordinates: "<<endl;
//determine the new coordinates.
for(int j=0;j<4;j++){
Coordinate *c=blockCoord[j];
int x=c->getX(c);
int newX=x+1;
int y=c->getY(c);  //y-coord stays the same.
//cout<<j<<": "<<newX<<", "<<y<<endl;

bool Present=isPresent(newX, y);  //helper fn called.
//now, we have a new set of coordinates. check if these coordinates are empty. if yes, drop. if not, do the same process for a diff index(i).
if(board[newX][y]==" " || Present==true) ++count;
//cout<<"Count: "<<count<<endl;
}

//cout<<"count: "<<count<<endl;
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
//cout<<"carriedOver has been updated: "<<carriedOver->getX(carriedOver)<<", "<<carriedOver->getY(carriedOver)<<endl;
}}
}



