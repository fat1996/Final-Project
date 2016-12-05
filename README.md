# QUADRIS
Final project for CS246 Fall 2016 by Simran Kaur and Fatime Taj

Build game by typing 'make;

Command Line Options:
- scriptfile file: generates block based on file
- startlevel x: starts game on level x
- seed x: sets seed as x
- text: runs game in text mode only

Commands:
- left: moves block one unit left
- right: moves block one unit right
- down: moves block one unit down
- clockwise: rotates block 90 degrees clockwise
- counterclockwise: rotates block 90 degrees anticlockwise
- drop: drops current block
- levelup: increases the difficulty level of the game by one 
- leveldown: decreases the diffculty level of the game by one
- norandom file: relevant only during levels 3 and 4, this command makes these levels non-random, instead taking input from the sequence file
- random: relevant only during levels 3 and 4, this command restores randomness in these levels
- sequence file: executes the sequence of commands found in file
- restart: clears the board and starts a new game
