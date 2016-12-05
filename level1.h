#ifndef __LEVEL1_H__
#define __LEVEL1_H__

#include <string>
#include "level.h"
#include "block.h"

class Level1 : public Level{
 public:
 	Level1();
	~Level1();
	block* getNextBlock() override;
};

#endif 
