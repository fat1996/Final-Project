#ifndef _LBLOCK_H_
#define _LBLOCK_H_
#include <iostream>
#include "block.h"

class lblock: public block{
public:
	void initialize(std::string** board) override;
	void clockwise(std::string** board) override;
	void anticlockwise(std::string** board) override;
	void updateBoard(std::string** board) override;
};

#endif
