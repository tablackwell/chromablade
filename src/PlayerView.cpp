#include "PlayerView.hpp"
#include "GameState.hpp"
#include "ChromaBlade.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdio>
#include <tuple>
#include <iostream>


#define SPEED 200.f

PlayerView::PlayerView() : Process() {
    init();
}

/* Initialize player view by loading files and setting initial positions */
void PlayerView::init(){

    // Load title screen.
    m_title.init();

    // Load map and overlay of sample room
     m_map.loadFromText("../res/tilesets/lightworld.png","../res/level/demolevel_base.csv", sf::Vector2u(16, 16), 50, 38);
     m_overlay.loadFromText("../res/tilesets/lightworld.png","../res/level/demolevel_overlay.csv", sf::Vector2u(16, 16), 50, 38);

	// Load texture for character
	if(!m_charTexture.loadFromFile("../res/Char.png")) {
		// ERROR
	}
	m_character.setTexture(m_charTexture);
	m_character.setPosition(sf::Vector2f(180, 210));
	m_character.setScale(1.f,1.f);
    setState(Process::RUNNING);
    m_speed = SPEED;
}


/* Set the window of the view */
void PlayerView::setContext(sf::RenderWindow* window){
	m_window = window;
}


/* Link the game logic with player view */
void PlayerView::setGameLogic(GameLogic* gameLogic) {
    m_gameLogic = gameLogic;
}


/* Link the game application with player view, so that we can check game state. */
void PlayerView::setGameApplication(ChromaBlade* game) {
    m_game = game;
}


/* Handle user inputs */
void PlayerView::handleInput(float deltaTime) {
    // First check game state
    GameState state = m_game->getState();
    switch(state) {
        case GameState::Title:
            int rc;
            rc = m_title.update(*m_window);
            // Moved the cursor
            if (rc == 0) {}
            // Selected Play
            else if (rc == 1) m_game->setState(GameState::Game);
            // Selected Exit
            else m_window->close();
            break;
        case GameState::Game:
            sf::Event event;
            while(m_window->pollEvent(event)){
                // Close window
                if(event.type == sf::Event::Closed){
                    m_window->close();
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                m_character.move(-m_speed * deltaTime, 0.f);
                m_gameLogic->setCharPosition(std::make_tuple(m_character.getPosition().x, m_character.getPosition().y));
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                m_character.move(m_speed * deltaTime, 0.f);
                m_gameLogic->setCharPosition(std::make_tuple(m_character.getPosition().x, m_character.getPosition().y));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                m_character.move(0.f, -m_speed * deltaTime);
                m_gameLogic->setCharPosition(std::make_tuple(m_character.getPosition().x, m_character.getPosition().y));
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                m_character.move(0.f, m_speed * deltaTime);
                m_gameLogic->setCharPosition(std::make_tuple(m_character.getPosition().x, m_character.getPosition().y));
            }
          break;
    }
}


/* Render */
void PlayerView::draw() {
    m_window->clear();
    GameState state = m_game->getState();
    // Render the content depending on the game state
    switch(state) {
        case GameState::Title:
            m_title.draw(*m_window);
            break;
        case GameState::Game:
            m_window->draw(m_map);
            m_window->draw(m_overlay);
            m_window->draw(m_character);
            break;
    }
    m_window->display();
}


/* Check if the window is open */
bool PlayerView::isOpen(){
	return m_window->isOpen();
}

///////////////////////// event related methods

/* Update view. */
void PlayerView::update(float &deltaTime){
    // currently does nothing, used by processManager
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

        float deltaTime = event.getDeltaTime();
        std::cout<<"Moving: "<<(m_speed * deltaTime);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            m_character.move(-m_speed * deltaTime, 0.f);
            m_gameLogic->setCharPosition(std::make_tuple(m_character.getPosition().x, m_character.getPosition().y));
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            m_character.move(m_speed * deltaTime, 0.f);
            m_gameLogic->setCharPosition(std::make_tuple(m_character.getPosition().x, m_character.getPosition().y));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            m_character.move(0.f, -m_speed * deltaTime);
            m_gameLogic->setCharPosition(std::make_tuple(m_character.getPosition().x, m_character.getPosition().y));
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            m_character.move(0.f, m_speed * deltaTime);
            m_gameLogic->setCharPosition(std::make_tuple(m_character.getPosition().x, m_character.getPosition().y));
        }
    }
}
