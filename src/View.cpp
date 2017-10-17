#include <View.hpp>

View::View(){}

void View::init(){
}

void View::setContext(sf::RenderWindow* window){
  targetWindow = window;
}

void View::update(){
  targetWindow->clear(sf::Color::Black);
  targetWindow->display();
}

bool View::isOpen(){
  return targetWindow->isOpen();
}

void View::handleEvents(){
  sf::Event Event;
  while(targetWindow->pollEvent(Event)){
  // Exit
  if(Event.type == sf::Event::Closed)
    targetWindow->close();
  }
}
