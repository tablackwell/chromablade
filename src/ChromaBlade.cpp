#include <ChromaBlade.hpp>

ChromaBlade::ChromaBlade()
{
}

/* Main game loop */
void ChromaBlade::run(){
  while(playerView.isOpen()){
    float deltaTime = fpsTimer.restart().asSeconds();
    playerView.update();
    gameLogic.update(deltaTime);
  }
}

void ChromaBlade::init(){
}
