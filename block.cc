#include <iostream>
#include <vector>
#include "coordinate.h"
#include "block.h"
#include "history.h"

using namespace std;

void block::drop(map<int, int> returnRows, string** board, vector<history*> &ongrid, int level, bool &gameOver) {
	returnRows=updateRows(returnRows, board);
	history *h=new history();
	vector<Coordinate*> v=h->accessGrid();
	int maxRow=0;

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

	if(count==4){}
	else { 
	for(int j=0;j<4;j++){
	Coordinate *c=blockCoord[j];
	int x=c->getX(c);
	int y=c->getY(c);
	int newX=x+delta-1;
	board[x][y]=" ";  //the previous coordinates of the block are set to empty.
	blockCoord[j]=new Coordinate;
	blockCoord[j]->setCoord(newX, y);
	v.push_back(blockCoord[j]);
	}
	break;
	}

	if(i==bottomRow-maxRow){
		for(int j=0;j<4;j++){
	Coordinate *c=blockCoord[j];
	int x=c->getX(c);
	int y=c->getY(c);
	int newX=x+bottomRow-maxRow;
	board[x][y]=" ";  //the previous coordinates of the block are set to empty.
	blockCoord[j]=new Coordinate;
	blockCoord[j]->setCoord(newX, y);
	v.push_back(blockCoord[j]);
	}
		break;
	}
	}

	h->accessGrid()=v;
	h->getLevel()=level;
	ongrid.push_back(h);
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

bool block::updateScore(string **board, map<int, int> emptyRows, vector<history*> &ongrid, int &counter, int &curScore, int &highScore, int curLevel, int &count){
	int i=bottomRow;

	while(i>3){

	if(emptyRows[i]==2){  //row is completely full.

	//you need to look at all the coordinates in row i.
	for(int j=0;j<rightBorder;j++){
	int x=i;
	int y=j;

	//now you need to check if these coordinates exist in the vector of history objects.
	int size=ongrid.size();
	for(int z=0;z<size;z++){
	history *h=ongrid[z];
	vector<Coordinate*> &v=h->accessGrid();
	int vsize=v.size();
	for(int a=0;a<vsize;a++){
		Coordinate *c=v[a];
		int x1=c->getX(c);
		int y1=c->getY(c);
		if(x==x1 && y==y1){
			//cout<<x<<", "<<y<<" exist"<<endl;
			v.erase(v.begin()+a);
		}
	}}}

	int s=ongrid.size();
	int z=0;
	while(z<s){
	history *h=ongrid[z];
	vector<Coordinate*> &v=h->accessGrid();
	int l=h->getLevel();
	int vsize=v.size();
	if(vsize==0){
		delete h;
		ongrid.erase(ongrid.begin()+z);
		curScore=curScore+((l+1)*(l+1));
		++count;
	}
	else{
		++z;
	}
	s=ongrid.size();
	}

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
		vector<Coordinate*> &v=h->accessGrid();
		int small=v.size();
		for(int l=0;l<small;l++){
			Coordinate *c=v[l];
		int x1=c->getX(c);
		int y1=c->getY(c);
		v[l]->setCoord(x1+1, y1);
		}
		h->accessGrid()=v;
	}
	emptyRows=updateRows(emptyRows, board);
	}

	else{
	--i;
	}
	}


	curScore=((curLevel+counter)*(curLevel+counter))+curScore;

	if(highScore<curScore){
		highScore=curScore;
	}

	if(counter>0){
		return true;
	}
	else{
		return false;
	}
}

void block::Heavy(string **board){
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
	for(int i=0;i<=bottomRow;i++){
	int count=0;
	for(int j=0;j<rightBorder;j++){
	if(board[i][j]==" ")
	{
	++count;
	}		
	}
	if(count==0){  //all the cells are completely filled.
	returnRows[i]=2;  //not empty.
	}
	else if(count==rowCap){
	returnRows[i]=0;
	}
	else{
	returnRows[i]=1;
	}
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
		present=true;
		break;
	}
	}
	return present;
}

void block::left(string** board){
	//determine the left-most x-coordinate.
	int minX;
	//determining the leftmost x-coord(the smallest value of x).
	for(int i=0;i<4;i++){
	Coordinate *c=blockCoord[i];
	int x=c->getY(c);  

	if(i==0) minX=x;
	else{
	if(x<minX){
	 minX=x;
	}
	}
	}

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
	}
	}
}

void block::right(string** board){
	//determine the right-most x-coordinate.

	int maxX;
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

	if(maxX==bottomRow){} //move cannot be made.
	else{  //move can be made, but you need to check if the 4 cells of the block can shift down completely.

	int count=0;  
	//determine the new coordinates.
	for(int j=0;j<4;j++){
	Coordinate *c=blockCoord[j];
	int x=c->getX(c);
	int newX=x+1;
	int y=c->getY(c);  //y-coord stays the same.

	bool Present=isPresent(newX, y);  //helper fn called.
	//now, we have a new set of coordinates. check if these coordinates are empty. if yes, drop. if not, do the same process for a diff index(i).
	if(board[newX][y]==" " || Present==true) ++count;
	}

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
	}
}
}
