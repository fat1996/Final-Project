# Final-Project
<b>Final project for CS246, Fall 2016</b>

By Simran Kaur and Fatima Taj

<b>Description:</b>

As part of our final project for CS246, we designed quadris, a non real-time version of Tetris (the user can take as much time as required to drop a block).

We used object oriented programming principles such as encapsulation, polymorphism, abstraction, as well as design patterns (factory method pattern to generate different blocks at different levels).

<b>Instructions:</b>

Build game by typing 'make'

Run game by typing ./quadris followed by command line options

<b>Command Line Options:</b>

-scriptfile file: generates block based on file

-startlevel x: starts game on level x

-seed x: sets seed as x

-text: runs game in text mode only

Example: ./quadris -text -scriptfile blocks.txt

<b>Commands:</b>

left: moves block one unit left

right: moves block one unit right

down: moves block one unit down

clockwise: rotates block 90 degrees clockwise

counterclockwise: rotates block 90 degrees anticlockwise

drop: drops current block

levelup: increases the difficulty level of the game by one

leveldown: decreases the diffculty level of the game by one

norandom file: relevant only during levels 3 and 4, this command makes these levels non-random, instead taking input from the sequence file

random: relevant only during levels 3 and 4, this command restores randomness in these levels

sequence file: executes the sequence of commands found in file

restart: clears the board and starts a new game

rename oldname newname: renames command oldname to newname

<b>Levels:</b>

0: Takes blocks from sequence.txt or file specified on command line

1: Z and S blocks produced with probability 1/12 each, all other blocks produced with probability 1/6

2: All blocks produced with equal probability

3: Z and S blocks produced with probability 2/9, all other blocks produced with probability 1/9. Blocks are also considered "heavy" meaning each move is followed by a downward shift of one cell.

4: Same as level 3, but star block is dropped if a row is not cleared in 5 moves
