#ifndef __LEVEL4_H__
#define __LEVEL4_H__

#include <string>
#include "level.h"
#include "block.h"

class Level4 : public Level{
 public:
 	Level4();
	~Level4();
	block* getNextBlock() override;
};

#endif 
