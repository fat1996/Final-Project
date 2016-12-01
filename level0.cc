#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "level.h"
#include "level0.h"
#include "block.h"
#include "jblock.h"
#include "lblock.h"
#include "iblock.h"
#include "oblock.h"
#include "tblock.h"
#include "sblock.h"
#include "zblock.h"

using namespace std;

int Level0::curPos = 0;

// Constructor reads blocks from file and stores in sequence vector
Level0::Level0(string scriptfile) : Level(0) {
	ifstream readfile {scriptfile};
	string block;
	while (readfile >> block) {
		sequence.push_back(block);
	}
}

// Destructor
Level0::~Level0() {
	sequence.clear();
}

// Returns new block
block* Level0::getNextBlock() {
	int pos = curPos;
	curPos = (curPos + 1) % sequence.size(); // Repeats blocks in sequence
	if (sequence[pos] == "J") {
		return new jblock;
	} else if (sequence[pos] == "L") {
		return new lblock;
	} else if (sequence[pos] == "I") {
		return new iblock;
	} else if (sequence[pos] == "O") {
		return new oblock;
	} else if (sequence[pos] == "T") {
		return new tblock;
	} else if (sequence[pos] == "S") {
		return new sblock;
	} else if (sequence[pos] == "Z") {
		return new zblock;
	} else {
		cout << "sequence.txt has unexpected value. J-Block created." << endl;
		return new jblock;
	}
}
