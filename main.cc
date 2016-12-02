#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include "block.h"
#include "grid.h"

using namespace std;

string scriptfile = "sequence.txt";
bool textOnly = false;
int level = 0;
int repeat = 1;
unsigned int seed = time(NULL);

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
	commandMap["restart"] = "restart";
	commandMap["hint"] = "hint";
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
				cout << "File does not exist!" << endl;
				return 1;
			}
			++i;
			scriptfile = tmpScriptfile;
		} else if (option == "-seed") {
			++i;
			int tmpSeed = atoi(argv[i]);
			if (tmpSeed < 0) {
				cout << "Invalid seed value." << endl;
				return 1;;
			}
			++i;
			seed = tmpSeed;
		} else if (option == "-startlevel") {
			++i;
			int tmpLevel = atoi(argv[i]);
			if (tmpLevel < 0 || tmpLevel > 4) {
				cout << "Invalid starting level." << endl;
				return 1;
			}
			++i;
			level = tmpLevel;
		} else {
			cout << "Invalid command line arguments" << endl;
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
		return "invalid command"; 
	} else {
		return commandMatch;
	}
}

// TODO HANDLE BLOCK DESTRUCTOR TO DELETE NEXT BLOCK AND CHECK SEG FAULTS
int main(int argc, char *argv[]) {
	createCommandMap();
	int result = executeCommandLine(argc, argv);
	if (result != 0) {
		return 1;
	}

	srand(seed); // Random seed is set
	grid *g = new grid;
	g->SetBoard(level, scriptfile);
	g->DrawBoard();

	string command;
	while (cin >> command) {
		if (command == "rename") {
			string oldName;
			string newName;
			cin >> oldName;
			cin >> newName;
			for (auto &it : commandMap ) {
				if (it.first == oldName) {
					string tmpCommand = it.second;
					commandMap.erase(oldName); // erases oldName + val from map
					commandMap[newName] = tmpCommand; // adds newName to map
					cout << oldName << " renamed to " << newName << endl;
				}
			}
		} else {
			command = setRepeat(command);
			command = determineCommand(command);
			while (repeat != 0) {
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
			 		g->getCurrentBlock()->drop(g->returnRows(), g->returnBoard());
			 		g->getCurrentBlock()->updateBoard(g->returnBoard());
			 		g->getCurrentBlock()->updateScore(g->returnBoard(), g->getCurrentBlock()->updateRows(g->returnRows(), g->returnBoard()));
			 		g->getNextBlock();
				}
				/* else if (command == "levelup") {
					if (level == 4) {
						cout << "You are at the highest level" << endl;
					}
					else {
						// delete old level object, and get new level object
					}
				} else if (command == "leveldown") {
					if (level == 0) {
						cout << "You are at the lowest level" << endl;
					}
					else {
						// delete old level object, and get new level object
					}
				} else if (command == "norandom") {
					string filename;
					cin >> filename;
					scriptfile = filename;
				} else if (command "random") {
					if (level >= 3) {
						scriptfile = ""
					}
					else {
						cout << "Only relevent in level 3 and 4" << endl;
					}
				} else if (command == "sequence") {
					string commandSeqFile;
					cin >> commandSeqFile;
					// open file, save commands, and run them
				} else if (command == "I") {
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
				} else if (command == "restart") {
					// restart
				} 
				*/ 
				else {
					cout << "Invalid command! Please enter a valid command." << endl;
					break;
				}
			}
			// TODO: Case draws board even if the command is invalid.
			g->DrawBoard();
			// reset repeat
			repeat = 1;
		}
	}
	delete g;
}
