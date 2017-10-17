#include <ChromaBlade.hpp>

ChromaBlade::ChromaBlade()
{
}

/* Main game loop */
void ChromaBlade::run(){

  while(playerView.isOpen()){

    float deltaTime = fpsTimer.restart().asSeconds();
    playerView.update();
    playerView.handleEvents();
    gameLogic.update(deltaTime);

  }
}

void ChromaBlade::init(){

}
