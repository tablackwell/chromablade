#include "PlayerView.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdio>
#include <tuple>
#include <iostream>


#define MAX_SPEED 200.f
#define INIT_SPEED 110.f
//#define ACCELERATION 100.f

PlayerView::PlayerView() : Process() {
    init();
}

/* Initialize player view by loading files and setting initial positions */
void PlayerView::init(){
	// Load texture for character
	if(!m_charTexture.loadFromFile("../res/Char.png")) {
		// ERROR
	}
	m_character.setTexture(m_charTexture);
	m_character.setPosition(sf::Vector2f(180, 210));
	m_character.setScale(1.f,1.f);
    setState(Process::RUNNING);
    m_speed = INIT_SPEED;
}


/* Set the window of the view */
void PlayerView::setContext(sf::RenderWindow* window){
	m_targetWindow = window;
}

void PlayerView::setGameLogic(GameLogic& gameLogic) {
    this->m_gameLogic = gameLogic;
}


void PlayerView::setListener(EventManager *eventManager) {
    m_eventManager = eventManager;
    
    // Create function for listener. Add to event manager.
    std::function<void(const EventInterface &event)> move = std::bind(&PlayerView::update1, this, std::placeholders::_1);
    const EventListener m_listener = EventListener(move, 3);
    m_eventManager->addListener(m_listener, EventType::sfmlEvent);
}


/* Update view. */
void PlayerView::update1(const EventInterface &event) {
    const EventInterface *ptr = &event;
    
    // Convert to SFML inherited class.
    if (const SFMLEvent *sfEvent = dynamic_cast<const SFMLEvent*>(ptr)) {
        
        sf::Event sfmlEvent = sfEvent->getSFMLEvent();
        
        if (sfmlEvent.type == sf::Event::KeyReleased) {
            m_notReleased = false;
        } else if (sfmlEvent.type == sf::Event::KeyPressed) {
            m_notReleased = true;
        }
        
        float deltaTime = event.getDeltaTime();
        std::cout<<"Moving: "<<(m_speed * deltaTime);
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            m_character.move(-m_speed * deltaTime, 0.f);
            m_gameLogic.setCharPosition(std::make_tuple(m_character.getPosition().x, m_character.getPosition().y));
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            m_character.move(m_speed * deltaTime, 0.f);
            m_gameLogic.setCharPosition(std::make_tuple(m_character.getPosition().x, m_character.getPosition().y));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            m_character.move(0.f, -m_speed * deltaTime);
            m_gameLogic.setCharPosition(std::make_tuple(m_character.getPosition().x, m_character.getPosition().y));
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            m_character.move(0.f, m_speed * deltaTime);
            m_gameLogic.setCharPosition(std::make_tuple(m_character.getPosition().x, m_character.getPosition().y));
        }
    }
}


/* Update view. */
void PlayerView::update(float &deltaTime){
	sf::Event event;
	while(m_targetWindow->pollEvent(event)){
		// Close window
		if(event.type == sf::Event::Closed){
			m_targetWindow->close();
		}
		else if(event.type == sf::Event::KeyReleased){
		    m_notReleased = false;
		}
		else if(event.type == sf::Event::KeyPressed){
            m_notReleased = true;
        }
	}
    /*
	if (m_notReleased){
	    if (m_speed <= MAX_SPEED){
	        m_speed += deltaTime * ACCELERATION;
	    }
	}
	else{
	    m_speed = INIT_SPEED;
	}
    */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
	    m_character.move(-m_speed * deltaTime, 0.f);
	    m_gameLogic.setCharPosition(std::make_tuple(m_character.getPosition().x, m_character.getPosition().y));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
	    m_character.move(m_speed * deltaTime, 0.f);
	    m_gameLogic.setCharPosition(std::make_tuple(m_character.getPosition().x, m_character.getPosition().y));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
	    m_character.move(0.f, -m_speed * deltaTime);
	    m_gameLogic.setCharPosition(std::make_tuple(m_character.getPosition().x, m_character.getPosition().y));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
	    m_character.move(0.f, m_speed * deltaTime);
	    m_gameLogic.setCharPosition(std::make_tuple(m_character.getPosition().x, m_character.getPosition().y));
	}
}

/* Draw view. */
void PlayerView::draw() {
    m_targetWindow->draw(m_character);
}

/* Check if the window is open */
bool PlayerView::isOpen(){
	return m_targetWindow->isOpen();
}


void PlayerView::handleInput(float deltaTime){
    // TO DO: move the input handling from chromablade.cpp to here
}
