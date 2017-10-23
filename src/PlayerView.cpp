#include "PlayerView.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

PlayerView::PlayerView(){

}

/* Initialize player view by loading files and setting initial positions */
void PlayerView::init(){
	// Load texture for character
	if(!charTexture.loadFromFile("../res/Char.png")) {
		// ERROR
	}
	character.setTexture(charTexture);
	character.setPosition(sf::Vector2f(400, 300));
}


/* Set the window of the view */
void PlayerView::setContext(sf::RenderWindow* window){
	targetWindow = window;
}


/* Redraw the window */
void PlayerView::update(){
	targetWindow->clear(sf::Color::Black);
	targetWindow->draw(character);
	targetWindow->display();
}


/* Check if the window is open */
bool PlayerView::isOpen(){
	return targetWindow->isOpen();
}


void PlayerView::handleEvents(){
	sf::Event event;
	while(targetWindow->pollEvent(event)){
		// Close window
		if(event.type == sf::Event::Closed){
			targetWindow->close();
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){

	}
}
