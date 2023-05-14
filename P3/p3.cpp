#include "simulation.h"

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
