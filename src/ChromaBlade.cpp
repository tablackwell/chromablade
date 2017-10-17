#include <ChromaBlade.hpp>

ChromaBlade::ChromaBlade()
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

}
