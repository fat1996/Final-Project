#ifndef __LEVEL0_H__
#define __LEVEL0_H__

#include <vector>
#include <string>
#include "level.h"
#include "block.h"

class Level0 : public Level{
	static int curPos; // position in sequence
	std::vector<std::string> sequence; // sequence of blocks from file
 public:
 	Level0(std::string scriptfile);
	~Level0();
	block* getNextBlock() override;
};

#endif 
