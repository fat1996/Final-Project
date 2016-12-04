#include "history.h"

using namespace std;

vector<Coordinate*> &history::accessGrid(){
	return onGrid;
}

int &history::getLevel(){
	return level;
}

history::~history(){
	delete this;
}
