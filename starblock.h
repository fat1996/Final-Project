#ifndef __STARBLOCK_H__
#define __STARBLOCK_H__
#include <iostream>
#include <vector>
#include "coordinate.h"
#include "block.h"
#include "history.h"
#include "string"

class StarBlock : public block {
 protected:
	Coordinate* position;
 public:
 	~StarBlock();
 	StarBlock();
	bool initialize(std::string** board, int level_num);
 	void updateBoard(std::string** board) override;
	void clockwise(std::string** board) override;
	void anticlockwise(std::string** board) override;
	void drop(std::map<int, int> returnRows, std::string** board, std::vector<history*> &ongrid, int level) override;
};

#endif