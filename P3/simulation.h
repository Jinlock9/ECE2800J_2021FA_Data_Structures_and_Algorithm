#ifndef SIMULATION_H
#define SIMULATION_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>
#include "world_type.h"

using namespace std;

#include "simulation.h"

point_t adjacentPoint(point_t pt, direction_t dir);
// EFFECTS: Returns a point that results from moving one square in the direction "dir" from the point "pt".

direction_t leftFrom(direction_t dir);
// EFFECTS: Returns the direction that results from turning left from the given direction "dir".

direction_t rightFrom(direction_t dir);
// EFFECTS: Returns the direction that results from turnign right from the given direction "dir".

instruction_t getInstruction(const creature_t &creature);
// EFFECTS: Returns the current instruction of "creature".

creature_t *getCreature(const grid_t &grid, point_t location);
// REQUIRES: location is inside the grid.
// EFFECTS: Returns a pointer to the creature at "location" in "grid".

bool inBoundary(const grid_t &grid, const creature_t &creature);
// EFFECTS: Return true, if the square(position) the creature is facing is in boundary.
// 	Otherwise, false.

bool canGo(const grid_t &grid, const creature_t &creature); 
// EFFECTS: Return true, if the square(position) the creature is facing is in boundary and empty.
// 	Otherwise, false.
	
void hop(grid_t &grid, creature_t &creature);
// MODIFIES: grid and creature
// EFFECTS: The creature moves forward as long as the square it is facing is empty. 
//	 If moving forward would put the creature outside the boundaries of the grid or would cause it to land on top of another creature, the hop instruction does nothing.

void left(creature_t &creature);
// MODIFIES: creature
// EFFECTS: The creature turns left 90 degrees to face in a new direction.

void right(creature_t &creature);
// MODIFIES: creature
// EFFECTS: The creature turns right 90 degrees to face in a new direction

void infect(const grid_t &grid, creature_t &creature); 
// MODIFIES: creature
// EFFECTS: If the square immediately in front of this creature is occupied by a creature of a different species (an “enemy”), that enemy creature is infected to become 
//	 the same as the infecting species. When a creature is infected, it keeps its position and orientation, but changes its internal species indicator and begins 
//	 executing the same program as the infecting creature, starting at step 1. 
//	 If the square immediately in front of this creature is empty, outside the grid, or occupied by a creature of the same species, the infect instruction does nothing.

void ifempty(creature_t &creature, grid_t &grid, bool verbose); 
// MODIFIES: creature
// EFFECTS: If the square in front of the creature is inside the grid boundary and unoccupied, jump to the certain step.
//	 Otherwise, go on with the next instruction.

void ifwall(creature_t &creature, grid_t &grid, bool verbose);
// MODIFIES: creature
// EFFECTS: If the creature is facing the border of the grid, jump to the certain step.
//	 Otherwise, go on with the next instruction.

void ifsame(creature_t &creature, grid_t &grid, bool verbose);
// MODIFIES: creature
// EFFECTS: If the square the creature is facing is occupied by a creature of the same species, jump to the certain step.
//	 Otherwise, go on with the next instruction.

void ifenemy(creature_t &creature, grid_t &grid, bool verbose);
// MODIFIES: creature
// EFFECTS: If the square the creature is facing is occupied by a creature of an enemy species, jump to the certain step.
//	 Otherwise, go on with the next instruction.

opcode_t stoop(string &op);
// EFFECTS: Returns opcode corresponds to the given string.

bool checkValidInst(string &op);
// EFFECTS: Returns true if the string means valid opcode.
// 	 Otherwise, returns false.

direction_t stodir(string &dir);
// EFFECTS: Returns direction corresponds to the given string.

bool checkValidDir(string &dir); 
// EFFECTS: Returns true if the string means valid direction.
// 	 Otherwise, returns false.

bool initWorld(world_t &world, const string &speciesFile, const string &creaturesFile);
// MODIFIES: world
// EFFECTS: Initialize "world" given the species summary file "speciesFile" and the world description file "creaturesFile".
//	 This initializes all the components of "world".
//	 Returns true if initialization is successful.

void printEnd(unsigned int id, const string &name);
// MODIFIES: cout
// EFFECTS: prints the progress of instructions - which end the round.

void printCont(unsigned int id, unsigned int ad, const string &name);
// MODIFIES: cout
// EFFECTS: prints the progress of instructions - which continue the round.

void simulationCreature(creature_t &creature, grid_t &grid, bool verbose);
// REQUIRES: creature is inside the grid.
// MODIFIES: creature, grid, cout.
// EFFECTS: Simulate one turn of "creature" and update the creature, the infected creature, and the grid if necessary.
//           The creature programID is always updated. The function also prints to the stdout the procudure.
//           If verbose is true, it prints more information.

void printGrid(const grid_t &grid);
// MODIFIES: cout
// EFFECTS: print a grid representation of the creature world.	

#endif // SIMULATION_H