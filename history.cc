#include "history.h"

using namespace std;

vector<Coordinate*> &history::accessGrid(){
	return onGrid;
}

int &history::getLevel(){
	return level;
}

history::~history(){
	int size=onGrid.size();
	for(int i=0 ; i<size; i++) {
		delete onGrid[i];
	}
}
