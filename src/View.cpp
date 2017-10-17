#include <View.hpp>

View::View(): window(sf::VideoMode(800,600,32), "ChromaBlade - Alpha build",sf::Style::Titlebar | sf::Style::Close){}


void View::init(){
}

void View::update(){
  window.clear(sf::Color::Black);
  window.display();
}

bool View::isOpen(){
  return window.isOpen();
}

void View::handleEvents(){ //temporarily here for debug purposes
  sf::Event Event;
  while(window.pollEvent(Event))
  {
    // Exit
    if(Event.type == sf::Event::Closed)
      window.close();
  }
}
