#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include "block.h"
#include "grid.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "sblock.h"
#include "oblock.h"
#include "zblock.h"
#include "tblock.h"
#include "starblock.h"

using namespace std;

string scriptfile = "sequence.txt";
bool textOnly = false;
int level = 0;
int repeat = 1;
unsigned int seed = time(NULL);

bool randomSeq = true; // random feature for level 3 + 4
vector<string> norandomBlocks;
int norandomPos = 0;

vector<string> commandSeq;
int commandSeqPos = 0;
bool commandSet = false; // sequence feature

int movesWithoutClearingRow = 0;
int hs = 0;  //highscore.
int &highScore = hs;
bool gameOver = false;


// map to keep track of name of command
map<string, string> commandMap;

// initializes commandMap
void createCommandMap() {
        commandMap["left"] = "left";
        commandMap["right"] = "right";
	commandMap["down"] = "down";
	commandMap["clockwise"] = "clockwise";
	commandMap["counterclockwise"] = "counterclockwise";
	commandMap["drop"] = "drop";
	commandMap["levelup"] = "levelup";
	commandMap["leveldown"] = "leveldown";
	commandMap["restart"] = "restart";
}


// Interprets command line input and returns 1 if unsuccessful, 0 is successful
int executeCommandLine(int argc, char *argv[]) {
	if (argc == 1) {
		return 0;
	}
	for (int i = 1; i < argc; i++) {
		string option = argv[i];
		if (option == "-text") {
			++i;
			textOnly = true;
		} else if (option == "-scriptfile") {
			++i;
			string tmpScriptfile = argv[i];
			ifstream filestream{tmpScriptfile};
			if (!filestream.good()) {
				cerr << "File does not exist!" << endl;
				return 1;
			}
			++i;
			scriptfile = tmpScriptfile;
		} else if (option == "-seed") {
			++i;
			int tmpSeed = atoi(argv[i]);
			if (tmpSeed < 0) {
				cerr << "Invalid seed value." << endl;
				return 1;;
			}
			++i;
			seed = tmpSeed;
		} else if (option == "-startlevel") {
			++i;
			int tmpLevel = atoi(argv[i]);
			if (tmpLevel < 0 || tmpLevel > 4) {
				cerr << "Invalid starting level." << endl;
				return 1;
			}
			++i;
			level = tmpLevel;
		} else {
			cerr << "Invalid command line arguments" << endl;
			return 1;
		}
	}
	return 0;
}

// Updates repeat to accurate number
string setRepeat(string command) {
	// Array of characters to look for
	const char arr[10] = {'0', '1', '2', '3', '4', '5', '6' ,'7' ,'8' ,'9'};
	int foundPos = command.find_last_of(arr);
	if (foundPos != -1) {
		// if find_last_of is a success
		repeat = stoi(command.substr(0, foundPos + 1));
		// return command without number of repeats
		return command.erase(0, foundPos + 1);
	}
	// return command if no numbers
	return command;
}

// Determines command entered using minimum letters
string determineCommand(string command) {
	string commandMatch = "";
	int matchCount = 0;
	for (auto &it : commandMap) {
		string tmp = it.first;
		tmp = tmp.substr(0, command.length());
		if (tmp == command) {
			matchCount++;
			commandMatch = it.second;
		}
	}
	if (commandMatch == "" || matchCount > 1) {
		// string entered matched more than one command or no command
		return "invalid command"; 
	} else {
		return commandMatch;
	}
}

// Generates next block in non-random block sequence
block* generateNorandomBlock() {
	int curNorandomPos = norandomPos;
	norandomPos = (curNorandomPos + 1) % norandomBlocks.size(); // repeats sequence
	string block = norandomBlocks[curNorandomPos];
	if (block == "J") {
		return new jblock;
	} else if (block == "I") {
		return new iblock;
	} else if (block == "O") {
		return new oblock;
	} else if (block == "S") {
		return new sblock;
	} else if (block == "T") {
		return new tblock;
	} else if (block == "Z") {
		return new zblock;
	} else {
		return new lblock;
	}
}

int main(int argc, char *argv[]) {

	// Initialize command map
	createCommandMap();
	// Run command line
	int result = executeCommandLine(argc, argv);
	if (result != 0) {
		// If command line arguments fail
		return 1;
	}

	srand(seed); // Random seed is set

	// Initialize game
	grid *g = new grid;
	g->SetBoard(level, scriptfile, gameOver);
	g->DrawBoard(level, highScore);

	string command;
	while (cin >> command) {
		if (command == "rename") {
			// Rename oldcommand to newcommand
			string oldName;
			string newName;
			cin >> oldName;
			cin >> newName;
			for (auto &it : commandMap ) {
				if (it.first == oldName) {
					string tmpCommand = it.second;
					commandMap.erase(oldName); // erases oldName + val from map
					commandMap[newName] = tmpCommand; // adds newName to map
					cout << oldName << " has been renamed to " << newName << endl;
				}
			}
		} else {
			command = setRepeat(command); // Determine repeat count
			command = determineCommand(command);
			while (repeat != 0 && !gameOver) {
				// While repeat > 0 or game is not over
				--repeat;
				if (command == "left") {
					g->getCurrentBlock()->left(g->returnBoard());
					g->getCurrentBlock()->updateBoard(g->returnBoard());
				} else if (command == "right") {
			 		g->getCurrentBlock()->right(g->returnBoard());
			 		g->getCurrentBlock()->updateBoard(g->returnBoard());
				} else if (command == "down") {
			 		g->getCurrentBlock()->down(g->returnBoard());
			 		g->getCurrentBlock()->updateBoard(g->returnBoard());
				} else if (command == "clockwise") {
			 		g->getCurrentBlock()->clockwise(g->returnBoard());
			 		g->getCurrentBlock()->updateBoard(g->returnBoard());
				} else if (command == "counterclockwise") {
					g->getCurrentBlock()->anticlockwise(g->returnBoard());
			 		g->getCurrentBlock()->updateBoard(g->returnBoard());
				} else if (command == "drop") {
					vector<history*> &v=g->returnGridList();
					int c=0;
					int d=0;
					int &counter=c;
					int &count=d;
					if (gameOver) {
						cout << "GAME OVER" << endl;
						delete g;
						return 0;
					} else {
						g->getCurrentBlock()->drop(g->returnRows(), g->returnBoard(), v, level, gameOver); 
						g->getCurrentBlock()->updateBoard(g->returnBoard());
						// Cleared determines if a row has been cleared
						bool cleared = g->getCurrentBlock()->updateScore(g->returnBoard(), 
							     g->getCurrentBlock()->updateRows(g->returnRows(), g->returnBoard()),
						             v, counter, g->returnCurScore(), highScore, level, count);		
					        	     g->getCurrentBlock()->updateBoard(g->returnBoard());
						if (gameOver) {
							cout << "GAME OVER" << endl;
							delete g;
							return 0;
						}
						if (level == 4 && !cleared) {
							++movesWithoutClearingRow;
							if (movesWithoutClearingRow == 5) {
								// drop starblock
								StarBlock* star = new StarBlock;
								star->initialize(g->returnBoard(), level, gameOver);
								star->drop(g->returnRows(), g->returnBoard(), v, level, gameOver);
								star->updateBoard(g->returnBoard());
								movesWithoutClearingRow = 0;
							}
						}
			 			if (randomSeq == true) {
							// Blocks are being generated randomly
							g->getNextBlock(gameOver);
						} else {
							// Blocks are being generated using sequence file
							g->setCurrentBlock(g->returnNextBlock(), gameOver);
							g->setNextBlock(generateNorandomBlock());
						}
					}
				} else if (command == "levelup") { 
					if (level == 4) {
						cerr << "Cannot levelup. You are at the highest level." << endl;
					}
					else {
						g->levelUp();
						level++;
					}
				} else if (command == "leveldown") {
					if (level == 0) {
						cerr << "Cannot leveldown. You are at the lowest level." << endl;
					}
					else {
						g->levelDown(scriptfile);
						level--;
					}
				} 
				/*  else if (command == "I") {
					// Destroy current block, and replace with I block, includes rotationState
				} else if (command == "J") {
					// Destroy current block, and replace with J block, includes rotationState
				} else if (command == "L") {
					// Destroy current block, and replace with L block, includes rotationState
				} else if (command == "S") {
					// Destroy current block, and replace with S block, includes rotationState
				} else if (command == "T") {
					// Destroy current block, and replace with T block, includes rotationState
				} else if (command == "O") {
					// Destroy current block, and replace with O block, includes rotationState
				} else if (command == "Z") {
					// Destroy current block, and replace with Z block, includes rotationState
				} */
				else if (command == "restart") {
					// restarts on same level: current and next block remain the same
					delete g;
					grid *g = new grid;
					gameOver = false;
					g->SetBoard(level, scriptfile, gameOver);
				} 
				else {
					// Invalid command
					cerr << "Invalid command! Please enter a valid command." << endl;
					break;
				}
			}
			if (gameOver) { 
				cout << "GAME OVER" << endl;
				delete g;
				return 0;
			}
			if (command == "down" || command == "left" || command == "right" || 
				command == "clockwise" || command == "counterclockwise") {
				// Command causes downward move if block is heavy
				g->getCurrentBlock()->Heavy(g->returnBoard());
				g->getCurrentBlock()->updateBoard(g->returnBoard());
			}
			// Redraw board
			g->DrawBoard(level, highScore);
			// reset repeat
			repeat = 1;
		}
	}
	delete g;
}
