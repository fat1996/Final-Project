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
// #include "starblock.h"

using namespace std;

// Constructor
Level4::Level4() : Level(4) {}

// Destructor
Level4::~Level4() {}

// Returns new block
block* Level4::getNextBlock() {
	int randomNum = rand() % 9 + 1;
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
	} else if (randomNum == 6 || randomNum == 7) {
		return new sblock;
	} else {
		return new zblock;
	}
}
