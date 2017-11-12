#include "PlayerView.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdio>
#include <tuple>
#include <iostream>

#define MAX_SPEED 200.f
#define INIT_SPEED 110.f
#define START_POS sf::Vector2f(196, 235)
//#define ACCELERATION 100.f

PlayerView::PlayerView() : Process() {
    init();
}

/* Initialize player view by loading files and setting initial positions */
void PlayerView::init(){
	// Load texture for character
    if(!m_charTexture.loadFromFile("../res/sprite.png")) {
		// ERROR
	}
    m_character.setTextureRect(sf::IntRect(32, 0, 32, 32));
    
    walkingDown.setSpriteSheet(m_charTexture);
    walkingDown.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingDown.addFrame(sf::IntRect(64, 0, 32, 32));
    walkingDown.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingDown.addFrame(sf::IntRect( 0, 0, 32, 32));
    
    walkingLeft.setSpriteSheet(m_charTexture);
    walkingLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    walkingLeft.addFrame(sf::IntRect(64, 32, 32, 32));
    walkingLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    walkingLeft.addFrame(sf::IntRect( 0, 32, 32, 32));
    
    walkingRight.setSpriteSheet(m_charTexture);
    walkingRight.addFrame(sf::IntRect(32, 64, 32, 32));
    walkingRight.addFrame(sf::IntRect(64, 64, 32, 32));
    walkingRight.addFrame(sf::IntRect(32, 64, 32, 32));
    walkingRight.addFrame(sf::IntRect( 0, 64, 32, 32));
    
    walkingUp.setSpriteSheet(m_charTexture);
    walkingUp.addFrame(sf::IntRect(32, 96, 32, 32));
    walkingUp.addFrame(sf::IntRect(64, 96, 32, 32));
    walkingUp.addFrame(sf::IntRect(32, 96, 32, 32));
    walkingUp.addFrame(sf::IntRect( 0, 96, 32, 32));

    currAnimation = &walkingDown;
    animatedSprite.setPosition(START_POS);

	m_character.setPosition(START_POS);
	m_character.setScale(1.f,1.f);
    setState(Process::RUNNING);
    m_speed = INIT_SPEED;
}


/* Set the window of the view */
void PlayerView::setContext(sf::RenderWindow* window){
	m_targetWindow = window;
}

void PlayerView::setGameLogic(GameLogic gameLogic) {
    this->m_gameLogic = gameLogic;
}


void PlayerView::setListener(EventManager *eventManager) {
//    m_eventManager = eventManager;
//
//    // Create function for listener. Add to event manager.
//    std::function<void(const EventInterface &event)> move = std::bind(&PlayerView::update1, this, std::placeholders::_1);
//    const EventListener m_listener = EventListener(move, 3);
//    m_eventManager->addListener(m_listener, EventType::sfmlEvent);
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
//            m_character.move(0.f, m_speed * deltaTime);
            std::cout<<"Down";
            currAnimation = &walkingDown;
            animatedSprite.move(sf::Vector2f(0.f, m_speed * deltaTime));
            
            m_gameLogic.setCharPosition(std::make_tuple(m_character.getPosition().x, m_character.getPosition().y));
        }
        std::cout<<"Play";
        animatedSprite.play(*currAnimation);
        std::cout<<std::endl;
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
    bool noKeyPressed = true;
    sf::Vector2f moving;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        currAnimation = &walkingLeft;
        moving = sf::Vector2f(-m_speed * deltaTime, 0.f);
	    m_gameLogic.setCharPosition(std::make_tuple(m_character.getPosition().x, m_character.getPosition().y));
        noKeyPressed = false;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        currAnimation = &walkingRight;
	    moving = sf::Vector2f(m_speed * deltaTime, 0.f);
	    m_gameLogic.setCharPosition(std::make_tuple(m_character.getPosition().x, m_character.getPosition().y));
        noKeyPressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        currAnimation = &walkingUp;
	    moving = sf::Vector2f(0.f, -m_speed * deltaTime);
	    m_gameLogic.setCharPosition(std::make_tuple(m_character.getPosition().x, m_character.getPosition().y));
        noKeyPressed = false;
	}
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        currAnimation = &walkingDown;
        moving = sf::Vector2f(0.f, m_speed * deltaTime);
        m_gameLogic.setCharPosition(std::make_tuple(m_character.getPosition().x, m_character.getPosition().y));
        noKeyPressed = false;
    }
    animatedSprite.play(*currAnimation);
    animatedSprite.move(moving);
    
    if (noKeyPressed) {
        animatedSprite.stop();
    }
    noKeyPressed = true;
    
    animatedSprite.update((sf::seconds(deltaTime)));
}

/* Draw view. */
void PlayerView::draw() {
    m_targetWindow->draw(animatedSprite);
}

/* Check if the window is open */
bool PlayerView::isOpen(){
	return m_targetWindow->isOpen();
}


void PlayerView::handleEvents(){
}
