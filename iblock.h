#ifndef _IBLOCK_H_
#define _IBLOCK_H_
#include <iostream>
#include <map>
#include "block.h"

class iblock: public block {
public:
	iblock();
	void initialize(std::string** board, int level_num) override;
	void clockwise(std::string** board) override;
	void anticlockwise(std::string** board) override;
	void updateBoard(std::string** board) override;
};

#endif
