#ifndef __LEVEL2_H__
#define __LEVEL2_H__

#include <string>
#include "level.h"
#include "block.h"

class Level2 : public Level{
 public:
 	Level2();
	~Level2();
	block* getNextBlock() override;
};

#endif 
