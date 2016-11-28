#ifndef _JBLOCK_H_
#define _JBLOCK_H_
#include <iostream>
#include "block.h"

class jblock: public block{
public:
	void initialize(std::string** board) override;
	void clockwise(std::string** board) override;
	void anticlockwise(std::string** board) override;
	void updateBoard(std::string** board) override;
};
#endif
