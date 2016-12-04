#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include "level.h"
#include "level4.h"
#include "block.h"
#include "jblock.h"
#include "lblock.h"
#include "iblock.h"
#include "oblock.h"
#include "tblock.h"
#include "sblock.h"
#include "zblock.h"

using namespace std;

// Constructor
Level4::Level4() : Level(4) {}

// Destructor
Level4::~Level4() {}

// Returns new block
block* Level4::getNextBlock() {
	int randomNum = rand() % 9 + 1; // Generates number from 1-9
	if (randomNum == 1) {
		// 1/9 chance
		return new iblock;
	} else if (randomNum == 2) {
		// 1/9 chance
		return new jblock;
	} else if (randomNum == 3) {
		// 1/9 chance
		return new lblock;
	} else if (randomNum == 4) {
		// 1/9 chance
		return new tblock;
	} else if (randomNum == 5) {
		// 1/9 chance
		return new oblock;
	} else if (randomNum == 6 || randomNum == 7) {
		// 2/9 chance
		return new sblock;
	} else {
		// 2/9 chance
		return new zblock;
	}
}
