#ifndef __LEVEL3_H__
#define __LEVEL3_H__

#include <string>
#include "level.h"
#include "block.h"

class Level3 : public Level{
 public:
 	Level3();
	~Level3();
	block* getNextBlock() override;
};

#endif 
