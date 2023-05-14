#include "simulation.h"

point_t adjacentPoint(point_t pt, direction_t dir) {
	point_t p;
	p.r = pt.r;
	p.c = pt.c;
	switch(dir) {
		case EAST:
			p.c++;
			return p;
		case WEST:
			p.c--;
			return p;
		case NORTH:
			p.r++;
			return p;
		case SOUTH:
			p.r--;
			return p;
		default:
			return p;
	}
}
// EFFECTS: Returns a point that results from moving one square in the direction "dir" from the point "pt".

direction_t leftFrom(direction_t dir) {
	switch(dir) {
		case EAST:
			return NORTH;
		case WEST:
			return SOUTH;
		case NORTH:
			return WEST;
		case SOUTH:
			return EAST;
		default:
			return dir;
	}
}
// EFFECTS: Returns the direction that results from turning left from the given direction "dir".

direction_t rightFrom(direction_t dir) {
	switch(dir) {
		case EAST:
			return SOUTH;
		case WEST:
			return NORTH;
		case NORTH:
			return EAST;
		case SOUTH:
			return WEST;
		default:
			return dir;
	}
}
// EFFECTS: Returns the direction that results from turnign right from the given direction "dir".

instruction_t getInstruction(const creature_t &creature) {
	return creature.species->program[creature.programID];
}
// EFFECTS: Returns the current instruction of "creature".

creature_t *getCreature(const grid_t &grid, point_t location) {
	return grid.squares[location.r][location.c];
}
// REQUIRES: location is inside the grid.
//
// EFFECTS: Returns a pointer to the creature at "location" in "grid".

bool inBoundary(const grid_t &grid, const creature_t &creature) {
	switch(creature.direction) {
		case EAST:
			if(((unsigned int)creature.location.c + 1) < grid.width) {
				return true;
			}
			else {
				return false;
			}
		case WEST:
			if(((unsigned int)creature.location.c - 1) >= 0) {
				return true;
			}
			else {
				return false;
			}
		case NORTH:
			if(((unsigned int)creature.location.r + 1) < grid.height) {
				return true;
			}
			else {
				return false;
			}
		case SOUTH:
			if(((unsigned int)creature.location.r - 1) >= 0) {
				return true;
			}
			else {
				return false;
			}
		default:
			return false;
	}
}

bool canGo(const grid_t &grid, const creature_t &creature) {
	if(inBoundary(grid, creature)) {
		if(getCreature(grid, adjacentPoint(creature.location, creature.direction)) == NULL) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}
	
void go(creature_t &creature) {
	creature.programID = getInstruction(creature).address;
	return;
}

void hop(grid_t &grid, creature_t &creature) {
	if(canGo(grid, creature)) {
		point_t temp = adjacentPoint(creature.location, creature.direction);
		grid.squares[temp.r][temp.c] = &creature;
		grid.squares[creature.location.r][creature.location.c] = NULL;
		creature.location = temp;
		creature.programID++;
		return;
	}
	else {
		creature.programID++;
		return;
	}
}

void left(creature_t &creature) {
	creature.direction = leftFrom(creature.direction);
	creature.programID++;
	return;
}

void right(creature_t &creature) {
	creature.direction = rightFrom(creature.direction);
	creature.programID++;
	return;
}

void infect(const grid_t &grid, creature_t &creature) {
	if(inBoundary(grid, creature)) {
		creature_t *temp = getCreature(grid, adjacentPoint(creature.location, creature.direction));
		if((temp == NULL) || (temp->species == creature.species)) {
			creature.programID++;
			return;
		}
		else {
			temp->species = creature.species;
			temp->programID = 0;
			creature.programID++;
			return;
		}
	}
	else {
		creature.programID++;
		return;
	}
}

void ifempty(const grid_t &grid, creature_t &creature) {
	if(canGo(grid, creature)) {
		go(creature);
		return;
	}
	else {
		creature.programID++;
		return;
	}
}

void ifwall(const grid_t &grid, creature_t &creature) {
	if(inBoundary(grid, creature)) {
		creature.programID++;
		return;
	}
	else {
		go(creature);
		return;
	}
}

void ifsame(const grid_t &grid, creature_t &creature) {
	if(inBoundary(grid, creature)) {
		creature_t *temp = getCreature(grid, adjacentPoint(creature.location, creature.direction));
		if((temp == NULL) || (temp->species != creature.species)) {
			creature.programID++;
			return;
		}
		else {
			go(creature);
			return;
		}
	}
	else {
		creature.programID++;
		return;
	}
}

void ifenemy(const grid_t &grid, creature_t &creature) {
	if(inBoundary(grid, creature)) {
		creature_t *temp = getCreature(grid, adjacentPoint(creature.location, creature.direction));
		if((temp == NULL) || (temp->species == creature.species)) {
			creature.programID++;
			return;
		}
		else {
			go(creature);
			return;
		}
	}
	else {
		creature.programID++;
		return;
	}
}

void print(unsigned int id, unsigned int ad, const string &name, bool verbose) {
	if(ad == MAXPROGRAM) {
		if(verbose) {
			cout<<endl;
			cout<<"Instruction "<<id<<": "<<name<<endl;
		}
		else {
			cout<<name<<endl;
		}
	}
	else {
		if(verbose) {
			cout<<endl;
			cout<<"Instruction "<<id<<": "<<name<<" "<<ad<<endl;
		}
		else {
			cout<<name<<endl;
		}
	}
}

opcode_t stoop(string &op) {
	if(op == "hop" || op == "HOP") {
		return HOP;
	}
	else if(op == "left" || op == "LEFT") {
		return LEFT;
	}
	else if(op == "right" || op == "RIGHT") {
		return RIGHT;
	}
	else if(op == "infect" || op == "INFECT") {
		return INFECT;
	}
	else if(op == "ifempty" || op == "IFEMPTY") {
		return IFEMPTY;
	}
	else if(op == "ifwall" || op == "IFWALL") {
		return IFWALL;
	}
	else if(op == "ifsame" || op == "IFSAME") {
		return IFSAME;
	}
	else if(op == "ifenemy" || op == "IFENEMY") {
		return IFENEMY;
	}
	else {
		return GO;
	}
}

bool checkValidInst(string &op) {
	if(op == "hop" || op == "HOP") {
		return true;
	}
	else if(op == "left" || op == "LEFT") {
		return true;
	}
	else if(op == "right" || op == "RIGHT") {
		return true;
	}
	else if(op == "infect" || op == "INFECT") {
		return true;
	}
	else if(op == "ifempty" || op == "IFEMPTY") {
		return true;
	}
	else if(op == "ifwall" || op == "IFWALL") {
		return true;
	}
	else if(op == "ifsame" || op == "IFSAME") {
		return true;
	}
	else if(op == "ifenemy" || op == "IFENEMY") {
		return true;
	}
	else if(op == "go" || op == "GO") {
		return true;
	}
	else {
		return false;
	}
}

direction_t stodir(string &dir) {
	if(dir == "east" || dir == "EAST") {
		return EAST;
	}
	else if(dir == "west" || dir == "WEST") {
		return WEST;
	}
	else if(dir == "north" || dir == "NORTH") {
		return NORTH;
	}
	else {	
		return SOUTH;
	}
}

bool checkValidDir(string &dir) {
	if(dir == "east" || dir == "EAST") {
		return true;
	}
	else if(dir == "west" || dir == "WEST") {
		return true;
	}
	else if(dir == "north" || dir == "NORTH") {
		return true;
	}
	else if(dir == "south" || dir == "SOUTH") {
		return true;
	}
	else {	
		return false;
	}
}

bool initWorld(world_t &world, const string &speciesFile, const string &creaturesFile) {
	string speciesList[MAXSPECIES];
	ifstream speciesDir;
	speciesDir.open(speciesFile);
	try {
		if(speciesDir.fail()) {
			ostringstream os;
			os<<"Error: Cannot open file "<<speciesFile<<"!";
			throw os.str();
		}
	}
	catch(string& s) {
		throw s;
	}
	unsigned int numSpecies = 0;
	if(speciesDir) {
		string dirName;
		getline(speciesDir, dirName);
		int checker0 = 0;
		while(speciesDir) {
			string temp;
			getline(speciesDir, temp);
			ostringstream os;
			os<<dirName<<"/"<<temp;
			string directory = os.str();
			speciesList[numSpecies] = temp;
			ifstream species;
			species.open(directory);
			try {
				if(species.fail()) {
					ostringstream os;
					os<<"Error: Cannot open file "<<directory<<"!";
					throw os.str();
				}
			}
			catch(string& s) {
				throw s;
			}
			if(temp == "") {
				checker0 = 1;
			}
			int checker1 = 0;
			if(species && checker0 == 0) {
				cout<<temp<<endl;
				world.species[numSpecies].name = temp;
				unsigned int programSize = 0;
				string program;
				while(species) {
					getline(species, program);
					if(program == "") {
						checker1 = 1;
					}
					if(species && checker1 == 0) {
						string op;
						unsigned int ad;
						istringstream is_s;
						is_s.str(program);
						is_s>>op>>ad;
						//cout<<op<<endl;
						try {
							if(!checkValidInst(op)) {
								ostringstream os;
								os<<"Error: Instruction "<<op<<" is not recognized!";
								throw os.str();
							}
						}
						catch(string& s) {
							throw s;
						}
						world.species[numSpecies].program[programSize].op = stoop(op);
						world.species[numSpecies].program[programSize].address = ad;
						programSize++;
					}	
					try {
						if(programSize > MAXPROGRAM) {
							ostringstream os;
							os<<"Error: Too many instructions for species "<<temp<<"!\n"<<"Maximal number of instructions is "<<MAXPROGRAM<<".";
							throw os.str();
						}
					}
					catch(string& s) {
						throw s;
					}
				}
				world.species[numSpecies].programSize = programSize;
			}
			species.close();
			numSpecies++;
			try {
				if((numSpecies - 1) > MAXSPECIES) {
					ostringstream os;
					os<<"Error: Too many species!\n"<<"Maximal number of species is "<<MAXSPECIES<<".";
					throw os.str();
				}
			}
			catch(string& s) {
				throw s;
			}
		}
		world.numSpecies = numSpecies - 1;
		cout<<world.numSpecies<<endl;
	}
	speciesDir.close();
	
	for(unsigned int i = 0; i < world.numSpecies; i++) {
		cout<<speciesList[i]<<endl;
		cout<<world.species[i].name<<endl;
	}

	unsigned int numCreatures = 0;
	ifstream creatures;
	creatures.open(creaturesFile);
	try {
		if(creatures.fail()) {
			ostringstream os;
			os<<"Error: Cannot open file "<<creaturesFile<<"!";
			throw os.str();
		}
	}
	catch(string& s) {
		throw s;
	}
	if(creatures) {
		string height;
		string width;
		getline(creatures, height);
		getline(creatures, width);
		unsigned int h = stoi(height);
		unsigned int w = stoi(width);
		try {
			if(h > MAXHEIGHT) {
				ostringstream os;
				os<<"Error: The grid height is illegal!";
				throw os.str();
			}
		}
		catch(string& s) {
			throw s;
		}
		try {
			if(w > MAXWIDTH) {
				ostringstream os;
				os<<"Error: The grid width is illegal!";
				throw os.str();
			}
		}
		catch(string& s) {
			throw s;
		}
		world.grid.height = h;
		world.grid.width = w;
		for(unsigned int i = 0; i < h; i++) {
			for(unsigned int j = 0; j < w; j++) {
				world.grid.squares[i][j] = NULL;
			}
		}
		int checker2 = 0;
		while(creatures) {
			string temp;
			getline(creatures, temp);
			if(temp == "") {
				checker2 = 1;
			}
			if(creatures && checker2 == 0) {
				string speciesTemp;
				string directionTemp;
				unsigned int r;
				unsigned int c;
				istringstream is_c;
				is_c.str(temp);
				is_c>>speciesTemp>>directionTemp>>r>>c;
				cout<<"#"<<numCreatures<<endl;
				cout<<speciesTemp<<" "<<directionTemp<<" "<<r<<" "<<c<<endl;
				try {
					if((r > h) || (r < 0) || (c > w) || (c < 0)) {
						ostringstream os;
						os<<"Error: Creature ("<<speciesTemp<<" "<<directionTemp<<" "<<r<<" "<<c<<") is out of bound!\n"<<"The grid size is "<<h<<"-by-"<<w<<".";
						throw os.str();
					}
				}
				catch(string& s) {
					throw s;
				}
				try {
					int flag = 0;
					for(unsigned int i = 0; i < world.numSpecies; i++) {
						if(speciesTemp == speciesList[i]) {
							flag = 1;
						}
					}
					if(flag == 0) {
						ostringstream os;
						os<<"Error: Species "<<speciesTemp<<" not found!";
						throw os.str();
					}
				}
				catch(string& s) {
					throw s;
				}
				try {
					if(!checkValidDir(directionTemp)) {
						ostringstream os;
						os<<"Error: Direction "<<directionTemp<<" is not recognized!";
						throw os.str();
					}
				}
				catch(string& s) {
					throw s;
				}
				world.creatures[numCreatures].location.r = r;
				world.creatures[numCreatures].location.c = c;
				world.creatures[numCreatures].direction = stodir(directionTemp);
				for(unsigned int a = 0; a < numSpecies; a++) {
					if(speciesTemp == world.species[a].name) {
						world.creatures[numCreatures].species = &world.species[a];
					}
				}
				world.creatures[numCreatures].programID = 0;
				try {
					if(world.grid.squares[r][c] != NULL) {
						ostringstream os;
						os<<"Error: Creature ("<<world.grid.squares[r][c]->species->name<<" "<<directName[world.grid.squares[r][c]->direction]<<r<<" "<<c<<") overlaps with creature ("<<speciesTemp<<" "<<directionTemp<<" "<<r<<" "<<c<<") !";
						throw os.str();
					}
				}
				catch(string& s) {
					throw s;
				}
				*world.grid.squares[r][c] = world.creatures[numCreatures];
				numCreatures++;
			}
			try {
				if(numCreatures > MAXCREATURES) {
					ostringstream os;
					os<<"Error: Too many creatures!\n"<<"Maximal number of creatures is "<<MAXCREATURES<<".";
					throw os.str();
				}
			}
			catch(string& m) {
				throw m;
			}
		}
		world.numCreatures = numCreatures;	
	}
	return true;
}

void simulationCreature(creature_t &creature, grid_t &grid, bool verbose) {
	instruction_t temp = getInstruction(creature);
	switch(temp.op) {
		case HOP:
			print((creature.programID + 1), MAXPROGRAM, opName[temp.op], verbose);
			hop(grid, creature);
			return;
		case LEFT:
			print((creature.programID + 1), MAXPROGRAM, opName[temp.op], verbose);
			left(creature);
			return;
		case RIGHT:
			print((creature.programID + 1), MAXPROGRAM, opName[temp.op], verbose);
			right(creature);
			return;
		case INFECT:
			print((creature.programID + 1), MAXPROGRAM, opName[temp.op], verbose);
			infect(grid, creature);
			return;
		case IFEMPTY:
			print((creature.programID + 1), temp.address, opName[temp.op], verbose);
			ifempty(grid, creature);
			return simulationCreature(creature, grid, verbose);
		case IFWALL:
			print((creature.programID + 1), temp.address, opName[temp.op], verbose);
			ifwall(grid, creature);
			return simulationCreature(creature, grid, verbose);
		case IFSAME:
			print((creature.programID + 1), temp.address, opName[temp.op], verbose);
			ifsame(grid, creature);
			return simulationCreature(creature, grid, verbose);
		case IFENEMY:
			print((creature.programID + 1), temp.address, opName[temp.op], verbose);
			ifenemy(grid, creature);
			return simulationCreature(creature, grid, verbose);
		case GO:
			print((creature.programID + 1), temp.address, opName[temp.op], verbose);
			go(creature);
			return simulationCreature(creature, grid, verbose);
		default:
			return;
	}
}
// REQUIRES: creature is inside the grid.
//
// MODIFIES: creature, grid, cout.
//
// EFFECTS: Simulate one turn of "creature" and update the creature, the infected creature, and the grid if necessary.
//          The creature programID is always updated. The function also prints to the stdout the procudure.
//          If verbose is true, it prints more information.

void printGrid(const grid_t &grid) {
	for(unsigned int i = 0; i < grid.height; i++) {
		for(unsigned int j = 0; j < grid.width; j++) {
			point_t p;
			p.r =i;
			p.c = j;
			creature_t *temp = getCreature(grid, p);
			if(temp == NULL) {
				cout<<"____ ";
			}
			else {
				instruction_t inst = getInstruction(*temp);
				cout<<opName[inst.op][0]<<opName[inst.op][1]<<"_"<<directShortName[temp->direction]<<" ";
			}
		}
		cout<<endl;
	}
			
}	
// MODIFIES: cout.
//
// EFFECTS: print a grid representation of the creature world.
