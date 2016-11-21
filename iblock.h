#ifndef _IBLOCK_H_
#define _IBLOCK_H_
#include <iostream>
#include "block.h"

class iblock: public block {
public:
void initialize() override;
};

#endif
