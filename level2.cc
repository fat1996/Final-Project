#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include "level.h"
#include "level2.h"
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
Level2::Level2() : Level(2) {}

// Destructor
Level2::~Level2() {}

// Returns new block
block* Level2::getNextBlock() {
	int randomNum = rand() % 7 + 1;
	if (randomNum == 1) {
		return new iblock;
	} else if (randomNum == 2) {
		return new jblock;
	} else if (randomNum == 3) {
		return new lblock;
	} else if (randomNum == 4) {
		return new tblock;
	} else if (randomNum == 5) {
		return new oblock;
	} else if (randomNum == 6) {
		return new sblock;
	} else {
		return new zblock;
	}
}
