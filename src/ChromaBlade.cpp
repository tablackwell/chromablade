#include <ChromaBlade.hpp>

ChromaBlade::ChromaBlade() : window(sf::VideoMode(WIDTH,HEIGHT,32), "Chromablade - Alpha build", sf::Style::Titlebar | sf::Style::Close)
{
	// initialize view
	// initialize game logic
}


void ChromaBlade::init(){
	view.setContext(&window);
}


void ChromaBlade::run(){
	/* Main game loop */

	//
	TileMap map;
	const int level[] =
    {
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
        0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
        0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
    };

		map.load("../res/tileset.png", sf::Vector2u(32, 32), level, 16, 8);


	while(view.isOpen()){
		float deltaTime = fpsTimer.restart().asSeconds();
		//view.update();

		window.clear();
		window.draw(map);
		window.display();
		gameLogic.update(deltaTime);
		view.handleEvents();
	}
}
