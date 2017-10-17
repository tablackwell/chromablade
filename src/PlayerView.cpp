#include <PlayerView.hpp>

PlayerView::PlayerView(): window(sf::VideoMode(800,600,32), "ChromaBlade - Alpha build",sf::Style::Titlebar | sf::Style::Close){}


void PlayerView::init(){
}

void PlayerView::update(){
  window.clear(sf::Color::Black);
  window.display();
}

bool PlayerView::isOpen(){
  return window.isOpen();
}

void PlayerView::handleEvents(){ //temporarily here for debug purposes
  sf::Event Event;
  while(window.pollEvent(Event))
  {
    // Exit
    if(Event.type == sf::Event::Closed)
      window.close();
  }
}
