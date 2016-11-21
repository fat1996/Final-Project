#include <iostream>
#include <string>
#include "grid.h"

using namespace std;

map<string, int> grid::returnCells(){
return cells;
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
string index=to_string(i+j);
cout<<"Index: "<<index<<endl; 
cells[index]=0;  //0 means empty.
}
string rowIndex=to_string(i);
cout<<"Row index is: "<<rowIndex<<endl;
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


