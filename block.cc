#include <iostream>
#include "coordinate.h"
#include "block.h"

block::~block(){
for(int i=0;i<4;i++){
delete blockCoord[i];
}
}
