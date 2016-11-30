#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "block.h"

class Level {
 protected:
	int level;
 public:
 	Level(int level_num);
	virtual ~Level();
	virtual block* getNextBlock() = 0;
};

#endif
