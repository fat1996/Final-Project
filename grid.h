#include <iostream>
#include <string>
#include <map>

const int boardheight=18;
const int boardwidth=11;

class grid {
	std::string **board;
	std::map<std::string, int> emptyRows;  //keeps track of which rows are completely filled and which are partially filled.

public:
	void SetBoard();   //this sets up the initial configuration of the board.
	void DrawBoard();
	std::string** returnBoard();  //returns the private member, board.
	std::map<std::string, int> returnRows();  //returns the private member, emptyRows.
	~grid(); //destructor.
};

