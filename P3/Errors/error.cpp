#include "simulation.h"

point_t adjacentPoint(point_t pt, direction_t dir) 
// EFFECTS: Returns a point that results from moving one square in the direction "dir" from the point "pt".
{
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
			p.r--;
			return p;
		case SOUTH:
			p.r++;
			return p;
		default:
			return p;
	}
}

direction_t leftFrom(direction_t dir) 
// EFFECTS: Returns the direction that results from turning left from the given direction "dir".
{
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

direction_t rightFrom(direction_t dir) 
// EFFECTS: Returns the direction that results from turnign right from the given direction "dir".
{
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

instruction_t getInstruction(const creature_t &creature) 
// EFFECTS: Returns the current instruction of "creature".
{
	return creature.species->program[creature.programID];
}

creature_t *getCreature(const grid_t &grid, point_t location) 
// REQUIRES: location is inside the grid.
// EFFECTS: Returns a pointer to the creature at "location" in "grid".
{
	return grid.squares[location.r][location.c];
}

bool inBoundary(const grid_t &grid, const creature_t &creature) 
// EFFECTS: Return true, if the square(position) the creature is facing is in boundary.
// 	Otherwise, false.
{
	switch(creature.direction) {
		case EAST:
			if(((unsigned int)creature.location.c + 1) < grid.width) {
				return true;
			}
			else {
				return false;
			}
		case WEST:
			if((creature.location.c - 1) >= 0) {
				return true;
			}
			else {
				return false;
			}
		case NORTH:
			if((creature.location.r - 1) >= 0) {
				return true;
			}
			else {
				return false;
			}
		case SOUTH:
			if(((unsigned int)creature.location.r + 1) < grid.height) {
				return true;
			}
			else {
				return false;
			}
		default:
			return false;
	}
}

bool canGo(const grid_t &grid, const creature_t &creature) 
// EFFECTS: Return true, if the square(position) the creature is facing is in boundary and empty.
// 	Otherwise, false.
{
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
	
void hop(grid_t &grid, creature_t &creature) 
// MODIFIES: grid and creature
// EFFECTS: The creature moves forward as long as the square it is facing is empty. 
//	 If moving forward would put the creature outside the boundaries of the grid or would cause it to land on top of another creature, the hop instruction does nothing.
{
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

void left(creature_t &creature) 
// MODIFIES: creature
// EFFECTS: The creature turns left 90 degrees to face in a new direction.
{
	creature.direction = leftFrom(creature.direction);
	creature.programID++;
	return;
}

void right(creature_t &creature)
// MODIFIES: creature
// EFFECTS: The creature turns right 90 degrees to face in a new direction
{
	creature.direction = rightFrom(creature.direction);
	creature.programID++;
	return;
}

void infect(const grid_t &grid, creature_t &creature) 
// MODIFIES: creature
// EFFECTS: If the square immediately in front of this creature is occupied by a creature of a different species (an “enemy”), that enemy creature is infected to become 
//	 the same as the infecting species. When a creature is infected, it keeps its position and orientation, but changes its internal species indicator and begins 
//	 executing the same program as the infecting creature, starting at step 1. 
//	 If the square immediately in front of this creature is empty, outside the grid, or occupied by a creature of the same species, the infect instruction does nothing.
{
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

void ifempty(creature_t &creature, grid_t &grid, bool verbose) 
// MODIFIES: creature
// EFFECTS: If the square in front of the creature is inside the grid boundary and unoccupied, jump to the certain step.
//	 Otherwise, go on with the next instruction.
{
	if(canGo(grid, creature)) {
		creature.programID = getInstruction(creature).address - 1;
		return simulationCreature(creature, grid, verbose);
	}
	else {
		creature.programID++;
		return simulationCreature(creature, grid, verbose);
	}
}

void ifwall(creature_t &creature, grid_t &grid, bool verbose) 
// MODIFIES: creature
// EFFECTS: If the creature is facing the border of the grid, jump to the certain step.
//	 Otherwise, go on with the next instruction.
{
	if(inBoundary(grid, creature)) {
		creature.programID++;
		return simulationCreature(creature, grid, verbose);
	}
	else {
		creature.programID = getInstruction(creature).address - 1;
		return simulationCreature(creature, grid, verbose);
	}
}

void ifsame(creature_t &creature, grid_t &grid, bool verbose) 
// MODIFIES: creature
// EFFECTS: If the square the creature is facing is occupied by a creature of the same species, jump to the certain step.
//	 Otherwise, go on with the next instruction.
{
	if(inBoundary(grid, creature)) {
		creature_t *temp = getCreature(grid, adjacentPoint(creature.location, creature.direction));
		if((temp == NULL) || (temp->species != creature.species)) {
			creature.programID++;
			return simulationCreature(creature, grid, verbose);
		}
		else {
			creature.programID = getInstruction(creature).address - 1;
			return simulationCreature(creature, grid, verbose);
		}
	}
	else {
		creature.programID++;
		return simulationCreature(creature, grid, verbose);
	}
}

void ifenemy(creature_t &creature, grid_t &grid, bool verbose) 
// MODIFIES: creature
// EFFECTS: If the square the creature is facing is occupied by a creature of an enemy species, jump to the certain step.
//	 Otherwise, go on with the next instruction.
{
	if(inBoundary(grid, creature)) {
		creature_t *temp = getCreature(grid, adjacentPoint(creature.location, creature.direction));
		if((temp == NULL) || (temp->species == creature.species)) {
			creature.programID++;
			return simulationCreature(creature, grid, verbose);
		}
		else {
			creature.programID = getInstruction(creature).address - 1;
			return simulationCreature(creature, grid, verbose);
		}
	}
	else {
		creature.programID++;
		return simulationCreature(creature, grid, verbose);
	}
}

opcode_t stoop(string &op) 
// EFFECTS: Returns opcode corresponds to the given string.
{
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

bool checkValidInst(string &op) 
// EFFECTS: Returns true if the string means valid opcode.
// 	 Otherwise, returns false.
{
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

direction_t stodir(string &dir) 
// EFFECTS: Returns direction corresponds to the given string.
{
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

bool checkValidDir(string &dir) 
// EFFECTS: Returns true if the string means valid direction.
// 	 Otherwise, returns false.
{
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

bool initWorld(world_t &world, const string &speciesFile, const string &creaturesFile) 
// MODIFIES: world
// EFFECTS: Initialize "world" given the species summary file "speciesFile" and the world description file "creaturesFile".
//	 This initializes all the components of "world".
//	 Returns true if initialization is successful.
{

	string speciesList[MAXSPECIES]; // List of species in species file
	
	/* SPECIES */
	ifstream speciesDir;
	speciesDir.open(speciesFile); // Open species file
	try {
		if(speciesDir.fail()) { // Chech whether the file is opened successfully
			ostringstream os;
			os<<"Error: Cannot open file "<<speciesFile<<"!";
			throw os.str();
		}
	}
	catch(string& s) {
		throw s;
	}

	unsigned int numSpecies = 0; // The number of species

	if(speciesDir) { // If there are contents inside the Species Directory

		string dirName; // Directory name (ex. creatures)
		getline(speciesDir, dirName); // Get name of the directory

		while(speciesDir) { 

			string temp; // Current species name
			getline(speciesDir, temp);
			ostringstream os;
			os<<dirName<<"/"<<temp; // Find the directory of species (ex. creatures/hop)
			string directory = os.str();
			
			if(temp == "") { // If there is no species name under the directory, quit the loop (for sure)
				break;
			}

			try {
				if(numSpecies == MAXSPECIES) { // Check if there are more species that the max number of species
					ostringstream os;
					os<<"Error: Too many species!\n"<<"Maximal number of species is "<<MAXSPECIES<<".";
					throw os.str();
				}
			}
			catch(string& s) {
				throw s;
			}

			speciesList[numSpecies] = temp; // Put the name of current species into the list

			ifstream species;
			species.open(directory); // Open species file
			try {
				if(species.fail()) { // Check whether the file is opened successfully
					ostringstream os;
					os<<"Error: Cannot open file "<<directory<<"!";
					throw os.str();
				}
			}
			catch(string& s) {
				throw s;
			}


			if(species) { // If there are contents inside the species file

				world.species[numSpecies].name = temp; // Record the species in world

				unsigned int programSize = 0; // The size of program
				string program;

				while(species) {

					getline(species, program);
					if(program == "") { // If there is no program under the species file, quit the loop
						break;
					}

					if(species) {

						try {
							if(programSize == MAXPROGRAM) { // Check if there are more programs than the max number of program
								ostringstream os;
								os<<"Error: Too many instructions for species "<<temp<<"!\n"<<"Maximal number of instructions is "<<MAXPROGRAM<<".";
								throw os.str();
							}
						}
						catch(string& s) {
							throw s;
						}

						string op; // op_code of the program
						unsigned int ad; // targeted address of program
						istringstream is_s;
						is_s.str(program);
						is_s>>op>>ad;

						try {
							if(!checkValidInst(op)) { // If op is not a valid op_code
								ostringstream os;
								os<<"Error: Instruction "<<op<<" is not recognized!";
								throw os.str();
							}
						}
						catch(string& s) {
							throw s;
						}

						world.species[numSpecies].program[programSize].op = stoop(op); // Assign op_code
						world.species[numSpecies].program[programSize].address = ad; // Assigne address

						programSize++; // now there is one more program
					}	
				}
				
				world.species[numSpecies].programSize = programSize;
			}

			species.close(); // close the current species file
			
			numSpecies++; // now there is one more program
		}
		
		world.numSpecies = numSpecies; // Since the index of species starts from 0, real number of species should be +1;
	}

	speciesDir.close(); // close the species directory file
	
	/*********** CREATURES ***********/
	unsigned int numCreatures = 0; // The number of creatures

	ifstream creatures;
	creatures.open(creaturesFile); // Open creatures file which gives basic information of world and creatures 
	try {
		if(creatures.fail()) { // Check whether the creature file is opened successfully
			ostringstream os;
			os<<"Error: Cannot open file "<<creaturesFile<<"!";
			throw os.str();
		}
	}
	catch(string& s) {
		throw s;
	}

	if(creatures) { // If there are contents in creature file

		string height;
		string width;
		getline(creatures, height);
		getline(creatures, width);
		unsigned int h = stoi(height);
		unsigned int w = stoi(width);
		try {
			if(h > MAXHEIGHT) { // Check the given height is valid
				ostringstream os;
				os<<"Error: The grid height is illegal!";
				throw os.str();
			}
		}
		catch(string& s) {
			throw s;
		}
		try {
			if(w > MAXWIDTH) { // Check the given width is valid
				ostringstream os;
				os<<"Error: The grid width is illegal!";
				throw os.str();
			}
		}
		catch(string& s) {
			throw s;
		}
		world.grid.height = h; // Initialize the height of world
		world.grid.width = w; // Initialize the width of world

		// Initialize the grid
		for(unsigned int i = 0; i < h; i++) {
			for(unsigned int j = 0; j < w; j++) {
				world.grid.squares[i][j] = NULL;
			}
		}

		while(creatures) {

			string temp;
			getline(creatures, temp);
			
			if(temp == "") { // If there is no more creature, quit the loop
				break;
			}

			try {
				if(numCreatures == MAXCREATURES) { // Check if there are more creatures than the maximum number of creature
					ostringstream os;
					os<<"Error: Too many creatures!\n"<<"Maximal number of creatures is "<<MAXCREATURES<<".";
					throw os.str();
				}
			}
			catch(string& m) {
				throw m;
			}

			if(creatures) { // If there is species

				string speciesTemp;
				string directionTemp;
				unsigned int r;
				unsigned int c;
				istringstream is_c;
				is_c.str(temp);
				is_c>>speciesTemp>>directionTemp>>r>>c;

				try { // Check whether the creatures is located in valid position
					if((r >= h) || (r < 0) || (c >= w) || (c < 0)) {
						ostringstream os;
						os<<"Error: Creature ("<<speciesTemp<<" "<<directionTemp<<" "<<r<<" "<<c<<") is out of bound!\n"<<"The grid size is "<<h<<"-by-"<<w<<".";
						throw os.str();
					}
				}
				catch(string& s) {
					throw s;
				}

				try { // Check whether the species of creature is valid
					int flag = 0;
					for(unsigned int i = 0; i < world.numSpecies; i++) {
						if(speciesTemp == speciesList[i]) {
							flag = 1;
							//cout<<"speciesTemp: "<<speciesTemp<<endl;
							//cout<<"speciesList["<<i<<"] :"<<speciesList[i]<<endl;
							//cout<<"world.numSpecies: "<<world.numSpecies<<endl;
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

				try { // Check whether the creature is directed to valid direction
					if(!checkValidDir(directionTemp)) {
						ostringstream os;
						os<<"Error: Direction "<<directionTemp<<" is not recognized!";
						throw os.str();
					}
				}
				catch(string& s) {
					throw s;
				}
					
				// Now all of the conditions for the creature itself is valid

				// Initialize the location of the creature
				world.creatures[numCreatures].location.r = r;
				world.creatures[numCreatures].location.c = c;

				world.creatures[numCreatures].direction = stodir(directionTemp); // Initialize the direction
				
				for(unsigned int a = 0; a < numSpecies; a++) { // Initialize the species
					if(speciesTemp == world.species[a].name) {
						world.creatures[numCreatures].species = &world.species[a];
					}
				}

				world.creatures[numCreatures].programID = 0; // Initialize the program ID (index of program)

				try { // Check whether two creatures are overlapped on the same poistion
					if(world.grid.squares[r][c] != NULL) {
						ostringstream os;
						os<<"Error: Creature ("<<speciesTemp<<" "<<directionTemp<<" "<<r<<" "<<c<<") overlaps with creature ("<<world.grid.squares[r][c]->species->name<<" "<<directName[world.grid.squares[r][c]->direction]<<" "<<r<<" "<<c<<")!";
						throw os.str();
					}
				}
				catch(string& s) {
					throw s;
				}

				world.grid.squares[r][c] = &world.creatures[numCreatures]; // Place the creature on the grid
				
				numCreatures++; // now there are one more creature
			}
		}

		world.numCreatures = numCreatures;	
	}

	return true; // Initialize the world successfully!
}

void printEnd(unsigned int id, const string &name) 
// MODIFIES: cout
// EFFECTS: prints the progress of instructions - which end the round.
{
	cout<<"Instruction "<<id<<": "<<name<<endl;
}

void printCont(unsigned int id, unsigned int ad, const string &name)
// MODIFIES: cout
// EFFECTS: prints the progress of instructions - which continue the round.
{
	cout<<"Instruction "<<id<<": "<<name<<" "<<ad<<endl;
}

void simulationCreature(creature_t &creature, grid_t &grid, bool verbose) 
// REQUIRES: creature is inside the grid.
// MODIFIES: creature, grid, cout.
// EFFECTS: Simulate one turn of "creature" and update the creature, the infected creature, and the grid if necessary.
//           The creature programID is always updated. The function also prints to the stdout the procudure.
//           If verbose is true, it prints more information.
{
	instruction_t temp = getInstruction(creature);
	switch(temp.op) {
		case HOP:
			if(verbose) {
				printEnd((creature.programID + 1),  opName[temp.op]);
			}
			else {
				cout<<" "<<opName[temp.op]<<endl;
			}
			return hop(grid, creature);
		case LEFT:
			if(verbose) {
				printEnd((creature.programID + 1),  opName[temp.op]);
			}
			else {
				cout<<" "<<opName[temp.op]<<endl;
			}
			return left(creature);
		case RIGHT:
			if(verbose) {
				printEnd((creature.programID + 1),  opName[temp.op]);
			}
			else {
				cout<<" "<<opName[temp.op]<<endl;
			}
			return right(creature);
		case INFECT:
			if(verbose) {
				printEnd((creature.programID + 1),  opName[temp.op]);
			}
			else {
				cout<<" "<<opName[temp.op]<<endl;
			}
			return infect(grid, creature);
		case IFEMPTY:
			if(verbose) {
				printCont((creature.programID + 1), temp.address, opName[temp.op]);
			}
			return ifempty(creature, grid, verbose);
		case IFWALL:
			if(verbose) {
				printCont((creature.programID + 1), temp.address, opName[temp.op]);
			}
			return ifwall(creature, grid, verbose);
		case IFSAME:
			if(verbose) {
				printCont((creature.programID + 1), temp.address, opName[temp.op]);
			}
			return ifsame(creature, grid, verbose);
		case IFENEMY:
			if(verbose) {
				printCont((creature.programID + 1), temp.address, opName[temp.op]);
			}
			return ifenemy(creature, grid, verbose);
		case GO:
			if(verbose) {
				printCont((creature.programID + 1), temp.address, opName[temp.op]);
			}
			creature.programID = getInstruction(creature).address - 1;
			return simulationCreature(creature, grid, verbose);
		default:
			return;
	}
}

void printGrid(const grid_t &grid) 
// MODIFIES: cout
// EFFECTS: print a grid representation of the creature world.
{
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
				string s = temp->species->name.substr(0, 2);
				cout<<s<<"_"<<directShortName[temp->direction]<<" ";
			}
		}
		cout<<endl;
	}
			
}	

int main(int argc, char *argv[]) {
	
	/***************************************/
	/******* Error Checking Process ********/
	/***************************************/

	// Check whether there are some missing essential arguments
	if(argc < 4) {  // If missing, error!
		cout<<"Error: Missing arguments!"<<endl;
		cout<<"Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]"<<endl;
		return 0;
	}

	// Check whether the number of simulation is negative
	if(stoi(argv[3]) < 0) { // If negative, error!
		cout<<"Error: Number of simulation rounds is negative!"<<endl;
		return 0;
	}

	/***************************************/
	/******** Initializing Process *********/
	/***************************************/

	// Initialize WORLD
	world_t world; 
	try {
		initWorld(world, argv[1], argv[2]);
	}
	catch(string& s) {
		cout<<s<<endl;
		return 0;
	}
	
	unsigned int rounds = stoi(argv[3]); // Initialize the number of ROUNDS

	// Initialize VERBOSE
	bool verbose = false;
	if(argc > 4) {
		if(strcmp(argv[4], "verbose") == 0 || strcmp(argv[4], "v") == 0) { // If there is [v|verbose] argument, verbose is true. Otherwise false.
			verbose = true;
		}
	}

	/***************************************/
	/******** Initiating Simulation ********/
	/***************************************/

	cout<<"Initial state"<<endl; // Initial state
	printGrid(world.grid);
	
	for(unsigned int i = 1; i <= rounds; i++) { // Begins each round
		cout<<"Round "<<i<<endl;
		for(unsigned int j = 0; j < world.numCreatures; j++) {
			cout<<"Creature ("<<world.creatures[j].species->name<<" "<<directName[world.creatures[j].direction]<<" "<<world.creatures[j].location.r<<" "<<world.creatures[j].location.c<<") takes action:";
			if(verbose) {
				cout<<endl;
			}
			simulationCreature(world.creatures[j], world.grid, verbose);
			if(verbose) { // Mapping for verbose
				printGrid(world.grid);
			}
		}
		if(!verbose) { // Mapping for not verbose
			printGrid(world.grid);
		}
	
	}

	return 0; // FINISH
}
