#ifndef _JBLOCK_H_
#define _JBLOCK_H_
#include <iostream>
#include "block.h"

class jblock: public block{
public:
	~jblock();
	void initialize() override;
	void printBlock() override;
	void fillBlock(std::string** board) override;
	void drop(std::map<std::string, int> returnRows, std::string** board) override;
	std::map<std::string, int> updateRows(std::map<std::string, int> returnRows, std::string** board) override;
	int lowestRow(std::map<std::string, int> returnRows);
};
#endif
