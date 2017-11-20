#include <ChromaBlade.hpp>

int main(int argc, char** argv){

	if(argc==1){
		printf("Launching ChromaBlade in default mode\n");
		ChromaBlade game;
		game.init();
		game.run();
	}
	else if(argc>=2){
		printf("Launching in DEBUG mode \n");
		ChromaBlade game;
		game.init();
		game.setDebug();
		game.run();
	}
	// Done
	return 0;
}
