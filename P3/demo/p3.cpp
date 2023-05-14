#include "simulation.h"

int main(int argc, char *argv[]) {

	if(argc < 5) {
		cout<<"Error: Missing arguments!"<<endl;
		cout<<"Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]"<<endl;
		return 0;
	}
	if(stoi(argv[3]) < 0) {
		cout<<"Error: Number of simulation rounds is negative!"<<endl;
		return 0;
	}

	world_t world;
	
	try {
		initWorld(world, argv[1], argv[2]);
	}
	catch(string& s) {
		cout<<s<<endl;
		return 0;
	}
	
	unsigned int rounds = stoi(argv[3]);

	bool verbose;
	if(strcmp(argv[4], "verbose") == 0 || strcmp(argv[4], "v") == 0) {
		verbose = true;
	}

	for(unsigned int i = 1; i <= rounds; i++) {
		cout<<"Round "<<i<<endl;
		for(unsigned int j = 0; j < world.numCreatures; j++) {
			cout<<"Creature ("<<world.creatures[j].species->name<<" "<<directName[world.creatures[j].direction]<<" "<<world.creatures[j].location.r<<" "<<world.creatures[j].location.c<<") takes action:";
			simulationCreature(world.creatures[j], world.grid, verbose);
		}
		printGrid(world.grid);
	}
}

