#include <iostream>
#include <vector>
#include "coordinate.h"
#include "starblock.h"
#include "block.h"

using namespace std;

// Constructor that sets type
starBlock::starBlock() : block('*'), level_num{4} {
	position = new Coordinate;
	position->setCoord(3, 6);
}

// Default destructor
StarBlock::~starBlock() {}

// Destructor for dropped starblock
StarBlock::deleteBlock() {
	delete position;
}

void StarBlock::updateBoard(std::string** board);

void StarBlock::drop(std::map<int, int> returnRows, std::string** board, std::vector<history*> &ongrid);
