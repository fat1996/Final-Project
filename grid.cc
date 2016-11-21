#include <iostream>
#include <string>
#include "grid.h"

using namespace std;

grid::~grid(){
for(int i=0;i<boardheight;i++)
{
delete [] board[i];
}
delete [] board;
}

map<string, int> grid::returnRows(){
return emptyRows;
}

string** grid::returnBoard(){
return board;
}

void grid::SetBoard(){   //this sets up the initial configuration of the board.
board=new string*[boardheight];

for(int i=0;i<boardheight;i++){
board[i]=new string[boardwidth];
for(int j=0;j<boardwidth;j++){
board[i][j]=" ";
}
string rowIndex=to_string(i);
emptyRows[rowIndex]=0; //0 means empty. The entire row is empty.	
}
}

void grid::DrawBoard(){
cout<<"---------------"<<endl;
for(int i=0;i<boardheight;i++){
for(int j=0;j<boardwidth;j++){
cout<<board[i][j];
}
cout<<endl;
}
cout<<"---------------"<<endl;
}


