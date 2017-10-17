#include <ChromaBlade.hpp>

ChromaBlade::ChromaBlade() : window(sf::VideoMode(800,600,32), "ChromaBlade - Alpha build",sf::Style::Titlebar | sf::Style::Close)
{

}

/* Main game loop */
void ChromaBlade::run(){

  while(view.isOpen()){
    float deltaTime = fpsTimer.restart().asSeconds();
    view.update();
    view.handleEvents();
    gameLogic.update(deltaTime);
  }
}

void ChromaBlade::init(){
  view.setContext(&window);
}
