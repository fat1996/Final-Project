#include <iostream>
#include <string>
#include <map>

const int boardheight=15;
const int boardwidth=11;

class grid {
	std::string **board;
	std::map<std::string, int> emptyRows;  //keeps track of which rows are completely filled and which are partially filled.
	std::map<std::string, int> cells;  //string=co-ordinates of each cell. int=0(empty) or 1(filled). To keep track of which cells are empty or not.

public:
	void SetBoard();   //this sets up the initial configuration of the board.
	void DrawBoard();
	std::string** returnBoard();  //returns the private member, board.
	std::map<std::string, int> returnCells(); //returns the private member, cells.
	std::map<std::string, int> returnRows();  //returns the private member, emptyRows.
};

