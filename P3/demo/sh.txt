#ifndef SIMULATION_H
#define SIMULATION_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>
#include "world_type.h"

using namespace std;

point_t adjacentPoint(point_t pt, direction_t dir);
// EFFECTS: Returns a point that results from moving one square in the direction "dir" from the point "pt".

direction_t leftFrom(direction_t dir);
// EFFECTS: Returns the direction that results from turning left from the given direction "dir".

direction_t rightFrom(direction_t dir);
// EFFECTS: Returns the direction that results from turnign right from the given direction "dir".

instruction_t getInstruction(const creature_t &creature);
// REQUIRES: location is inside the grid.
//
// EFFECTS: Returns a pointer to the creature at "location" in "grid".

bool inBoundary(const grid_t &grid, const creature_t &creature);

bool canGo(const grid_t &grid, const creature_t &creature);
	
void go(creature_t &creature);

void hop(grid_t &grid, creature_t &creature);

void left(creature_t &creature);

void right(creature_t &creature);

void infect(const grid_t &grid, creature_t &creature);

void ifempty(const grid_t &grid, creature_t &creature);

void ifwall(const grid_t &grid, creature_t &creature);

void ifsame(const grid_t &grid, creature_t &creature);

void ifenemy(const grid_t &grid, creature_t &creature);

void print(unsigned int id, unsigned int ad, const string &name, bool verbose);

void action(grid_t &grid, creature_t &creature, bool verbose);

bool initWorld(world_t &world, const string &speciesFile, const string &creaturesFile);

void simulationCreature(creature_t &creature, grid_t &grid, bool verbose);
// REQUIRES: creature is inside the grid.
//
// MODIFIES: creature, grid, cout.
//
// EFFECTS: Simulate one turn of "creature" and update the creature, the infected creature, and the grid if necessary.
//          The creature programID is always updated. The function also prints to the stdout the procudure.
//          If verbose is true, it prints more information.

void printGrid(const grid_t &grid);	
// MODIFIES: cout.
//
// EFFECTS: print a grid representation of the creature world.

#endif // SIMULATION_H
