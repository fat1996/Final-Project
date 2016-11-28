#ifndef _SBLOCK_H_
#define _SBLOCK_H_
#include <iostream>
#include "block.h"

class sblock: public block{
public:
	void initialize(std::string** board) override;
	void clockwise(std::string** board) override;
	void anticlockwise(std::string** board) override;
	void updateBoard(std::string** board) override;
};

#endif
