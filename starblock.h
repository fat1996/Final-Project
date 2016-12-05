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
	void initialize(std::string** board, int level_num, bool &gameOver);
 	void updateBoard(std::string** board) override;
	void clockwise(std::string** board) override;
	void anticlockwise(std::string** board) override;
	virtual void drop(std::map<int, int> returnRows, std::string** board, std::vector<history*> &ongrid, int level, bool &gameOver) override;
};

#endif
