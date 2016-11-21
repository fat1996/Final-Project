#include <iostream>
#include <string>
#include "block.h"
#include "grid.h"
#include "jblock.h"

using namespace std;

int main(){
grid g;
g.SetBoard();
jblock *b1=new jblock;
b1->initialize();
b1->printBlock();
b1->fillBlock(g.returnBoard());
g.DrawBoard();
b1->drop(g.returnCells(), g.returnRows(), g.returnBoard());
b1->printBlock();
b1->fillBlock(g.returnBoard());
g.DrawBoard();
}


