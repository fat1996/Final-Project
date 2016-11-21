#include <iostream>
#include <string>
#include "block.h"
#include "grid.h"
#include "jblock.h"

using namespace std;

int main(){
grid *g=new grid;
g->SetBoard();
jblock *b1=new jblock;
b1->initialize();
b1->printBlock();
b1->fillBlock(g->returnBoard());
g->DrawBoard();

b1->drop(g->returnRows(), g->returnBoard());
b1->printBlock();
b1->fillBlock(g->returnBoard());
g->DrawBoard();

jblock *b2=new jblock;
b2->initialize();
b2->printBlock();
b2->fillBlock(g->returnBoard());
g->DrawBoard();

b2->drop(g->returnRows(), g->returnBoard());
b2->printBlock();
b2->fillBlock(g->returnBoard());
g->DrawBoard();
delete b1;
delete b2;
delete g;
}


