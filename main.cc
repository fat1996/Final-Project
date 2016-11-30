#include <iostream>
#include <string>
#include "block.h"
#include "grid.h"

using namespace std;

// HANDLE BLOCK DESTRUCTOR TO DELETE NEXT BLOCK
int main() {
	grid *g = new grid;
	g->SetBoard(0);
	g->DrawBoard();
	string command;
	while (cin >> command) {
		if (command == "left") {
			g->getCurrentBlock()->left(g->returnBoard());
			g->getCurrentBlock()->updateBoard(g->returnBoard());
			g->DrawBoard();
		} else if (command == "right") {
			 g->getCurrentBlock()->right(g->returnBoard());
			 g->getCurrentBlock()->updateBoard(g->returnBoard());
			 g->DrawBoard();
		} else if (command == "down") {
			 g->getCurrentBlock()->down(g->returnBoard());
			 g->getCurrentBlock()->updateBoard(g->returnBoard());
			 g->DrawBoard();
		} else if (command == "clockwise") {
			 g->getCurrentBlock()->clockwise(g->returnBoard());
			 g->getCurrentBlock()->updateBoard(g->returnBoard());
			 g->DrawBoard();
		} else if (command == "counterclockwise") {
			 g->getCurrentBlock()->anticlockwise(g->returnBoard());
			 g->getCurrentBlock()->updateBoard(g->returnBoard());
			 g->DrawBoard();
		} else if (command == "drop") {
			 g->getCurrentBlock()->drop(g->returnRows(), g->returnBoard());
			 g->getCurrentBlock()->updateBoard(g->returnBoard());
			 g->getNextBlock();
			 g->DrawBoard();
		} else {
			cout << "Invalid command!" << endl;
		}
	}
	delete g;
}
