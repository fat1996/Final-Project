#ifndef _IBLOCK_H_
#define _IBLOCK_H_
#include <iostream>
#include <map>
#include "block.h"

class iblock: public block {
public:
	void initialize() override;
	void printBlock() override;
	void fillBlock(std::string** board) override;
	void drop(std::map<std::string, int> returnRows, std::string** board) override;
	std::map<std::string, int> updateRows(std::map<std::string, int> returnRows, std::string** board)=0;
};

#endif
