#include "PlayerView.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdio>
#include <tuple>

#define MAX_SPEED 200.f
#define INIT_SPEED 110.f
//#define ACCELERATION 100.f

PlayerView::PlayerView() : Process() {
    init();
}

/* Initialize player view by loading files and setting initial positions */
void PlayerView::init(){
	// Load texture for character
	if(!charTexture.loadFromFile("../res/Char.png")) {
		// ERROR
	}
	character.setTexture(charTexture);
	character.setPosition(sf::Vector2f(180, 210));
	character.setScale(1.f,1.f);
    setState(Process::RUNNING);
    speed = INIT_SPEED;
}


/* Set the window of the view */
void PlayerView::setContext(sf::RenderWindow* window){
	targetWindow = window;
}

void PlayerView::setGameLogic(GameLogic gameLogic) {
    this->gameLogic = gameLogic;
}


/* Update view. */
void PlayerView::update(const EventInterface &event) {
    const EventInterface *ptr = &event;
    
    // Convert to SFML inherited class.
    if (const SFMLEvent *sfEvent = dynamic_cast<const SFMLEvent*>(ptr)) {
        
        sf::Event sfmlEvent = sfEvent->getSFMLEvent();
        
        if (sfmlEvent.type == sf::Event::KeyReleased) {
            notReleased = false;
        } else if (sfmlEvent.type == sf::Event::KeyPressed) {
            notReleased = true;
        }
        
        auto key = sfmlEvent.key.code;
        float deltaTime = event.getDeltaTime();
        
        if (key == sf::Keyboard::Left){
            character.move(-speed * deltaTime, 0.f);
            gameLogic.setCharPosition(std::make_tuple(character.getPosition().x, character.getPosition().y));
        } else if (key == sf::Keyboard::Right){
            character.move(speed * deltaTime, 0.f);
            gameLogic.setCharPosition(std::make_tuple(character.getPosition().x, character.getPosition().y));
        }
        
        if (key == sf::Keyboard::Up){
            character.move(0.f, -speed * deltaTime);
            gameLogic.setCharPosition(std::make_tuple(character.getPosition().x, character.getPosition().y));
        } else if (key == sf::Keyboard::Down){
            character.move(0.f, speed * deltaTime);
            gameLogic.setCharPosition(std::make_tuple(character.getPosition().x, character.getPosition().y));
        }
    }
}


/* Update view. */
void PlayerView::update(float &deltaTime){
	sf::Event event;
	while(targetWindow->pollEvent(event)){
		// Close window
		if(event.type == sf::Event::Closed){
			targetWindow->close();
		}
		else if(event.type == sf::Event::KeyReleased){
		    notReleased = false;
		}
		else if(event.type == sf::Event::KeyPressed){
            notReleased = true;
        }
	}
    /*
	if (notReleased){
	    if (speed <= MAX_SPEED){
	        speed += deltaTime * ACCELERATION;
	    }
	}
	else{
	    speed = INIT_SPEED;
	}
    */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
	    character.move(-speed * deltaTime, 0.f);
	    gameLogic.setCharPosition(std::make_tuple(character.getPosition().x, character.getPosition().y));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
	    character.move(speed * deltaTime, 0.f);
	    gameLogic.setCharPosition(std::make_tuple(character.getPosition().x, character.getPosition().y));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
	    character.move(0.f, -speed * deltaTime);
	    gameLogic.setCharPosition(std::make_tuple(character.getPosition().x, character.getPosition().y));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
	    character.move(0.f, speed * deltaTime);
	    gameLogic.setCharPosition(std::make_tuple(character.getPosition().x, character.getPosition().y));
	}
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
}
