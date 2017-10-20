#include <ChromaBlade.hpp>

ChromaBlade::ChromaBlade() : window(sf::VideoMode(800,600,32), "Chromablade - Alpha build", sf::Style::Titlebar | sf::Style::Close)
{

}


void ChromaBlade::init(){
	view.setContext(&window);
}


void ChromaBlade::run(){
	/* Main game loop */
	while(view.isOpen()){
		float deltaTime = fpsTimer.restart().asSeconds();
		view.update();
		view.handleEvents();
		gameLogic.update(deltaTime);
	}
}


