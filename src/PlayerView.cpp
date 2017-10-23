#include "PlayerView.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdio>

PlayerView::PlayerView() : Process() {
}

/* Initialize player view by loading files and setting initial positions */
void PlayerView::init(){
	// Load texture for character
	if(!charTexture.loadFromFile("../res/Char.png")) {
		// ERROR
	}
	character.setTexture(charTexture);
	character.setPosition(sf::Vector2f(400, 300));

    setState(RUNNING);
}


/* Set the window of the view */
void PlayerView::setContext(sf::RenderWindow* window){
	targetWindow = window;
}


/* Update view. */
void PlayerView::update(float &deltaTime){
}

/* Draw view. */
void PlayerView::draw() {
    targetWindow->draw(character);
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
	// letter ‘A’...
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){

	}
}
