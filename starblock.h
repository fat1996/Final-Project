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
	Coordinate position;
 public:
 	~starBlock();
	void deleteBlock() override;
 	void starBlock();
 	void updateBoard(std::string** board) override;
	void drop(std::map<int, int> returnRows, std::string** board, std::vector<history*> &ongrid) override;
}

#endif
