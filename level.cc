#include "level.h"

using namespace std;

int Level::getLevel(){
	return level;
}

Level::Level(int level_num) : level{level_num} {};

Level::~Level() {}
