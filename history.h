#ifndef _HISTORY_H_
#define _HISTORY_H_
#include "coordinate.h"
#include <iostream>
#include <vector>


class history {
protected:	
	std::vector<Coordinate*> onGrid;  //coordinates of a block present on the grid.	
public:
	~history();
	std::vector<Coordinate*> &accessGrid();
};

#endif
