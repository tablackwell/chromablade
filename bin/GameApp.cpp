#include <ChromaBlade.hpp>


int main(int argc, char** argv){
    ChromaBlade game;
    game.init();
	if(argc==1){
		printf("Launching ChromaBlade in default mode\n");
	}
	else if(argc>=2){
		printf("Launching in DEBUG mode \n");
		game.setDebug();
	}
    game.run();
	// Done
	return 0;
}
