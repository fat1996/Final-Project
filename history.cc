#include "history.h"

using namespace std;

vector<Coordinate*> &history::accessGrid(){
	return onGrid;
}

history::~history(){
	delete this;
}
