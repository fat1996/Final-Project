#include "level.h"

using namespace std;

// Level value gettor
int Level::getLevel(){
	return level;
}

// Constructor that initializes the level field
Level::Level(int level_num) : level{level_num} {};

// Destructor
Level::~Level() {}
