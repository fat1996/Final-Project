#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include "level.h"
#include "level1.h"
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
Level1::Level1() : Level(1) {}

// Destructor
Level1::~Level1() {}

// Returns next block
block* Level1::getNextBlock() {
	int randomNum = rand() % 12 + 1; // Generates number from 1-12
	if (randomNum == 1 || randomNum == 2) {
		// 1/6 chance
		return new iblock;
	} else if (randomNum == 3 || randomNum == 4) {
		// 1/6 chance
		return new jblock;
	} else if (randomNum == 5 || randomNum == 6) {
		// 1/6 chance
		return new lblock;
	} else if (randomNum == 7 || randomNum == 8) {
		// 1/6 chance
		return new tblock;
	} else if (randomNum == 9 || randomNum == 10) {
		// 1/6 chance
		return new oblock;
	} else if (randomNum == 11) {
		// 1/12 chance
		return new sblock;
	} else {
		// 1/12 chance
		return new zblock;
	}
}
