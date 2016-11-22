#include <iostream>
#include <map>
#include <string>

using namespace std;

// still need to consider norandom, sequence, and random

string scriptfile;
bool textOnly = false;
int level = 0;
// int seed = ???
int repeat = 1;

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


// Interprets command line input
void executeCommandLine(int argc, char *argv[]) {
	for (int i = 0; i < argc; i++) {
		string option = argv[i];
		if (option == "-text") {
			textOnly = true;
		}
		else if (option == "-seed") {
			i++;
			seed = atoi(argv[i]);
		}
		else if (option == "-scriptfile") {
			i++;
			scriptfile = argv[i];
		}
		else if (option == "-startlevel") {
			i++;
			level = atoi(argv[i]);
		}
	}
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
	for (auto &it : commandMap) {
		string tmp = it.first;
		tmp = tmp.substr(0, command.length());
		if (tmp == command) {
			return it.second;
		}
	}
	return "invalid command";
}

int main(int argc, char *argv[]) {
	createCommandMap();
	executeCommandLine();

	// seed things ???

	// initialize game 

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
		}
		else {
			setRepeat(command);
			command = determineCommand(command);
			while (repeat != 0) {
				repeat--;
				if (command == "left") {
					// execute left
				}
				else if (command == "right") {
					// execute right
				}
				else if (command == "down") {
					// execute down
				}
				else if (command == "clockwise") {
					// execute CW
				}
				else if (command == "counterclockwise") {
					// execute CCW
				}
				else if (command == "drop") {
					// execute drop or new game if no more moves
				}
				else if (command == "levelup") {
					// execute levelup
				}
				else if (command == "leveldown") {
					// execute leveldown
				}
				else if (command == "hint") {
					// execute hint
				}
				else if (command == "restart") {
					// rexecute restart
				}
				else if (command == "invalid command") {
					cout << "Please enter a valid command" << endl;
				}
			}
			// reset repeat
			repeat = 1;
		}
	}
}



