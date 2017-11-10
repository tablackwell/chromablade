#include "ChromaBlade.hpp"
#include "PlayerView.hpp"
#include "GameLogic.hpp"

#include <cstdio>
#include <iostream>


/* The game application layer */
ChromaBlade::ChromaBlade() : m_window(sf::VideoMode(WIDTH,HEIGHT,32), "Chromablade - Alpha build", sf::Style::Titlebar | sf::Style::Close)
{
    /* Start on the Title screen. */
    m_state = GameState::Title;
}


void ChromaBlade::init(){
    m_view.setContext(&m_window);
    m_view.setGameLogic(&m_gameLogic);
    m_view.setGameApplication(this);
    m_eventManager.setWindow(&m_window);
  	m_window.setVerticalSyncEnabled(true);

    m_title.setListener(&m_eventManager);

    /* Play music on start. */
    m_audio.init();

    /* Attach PlayerView, GameLogic, and Audio to ProcessManager. */
    m_processManager.attachProcess(&m_view);
    m_processManager.attachProcess(&m_gameLogic);
    m_processManager.attachProcess(&m_audio);
}


/* Main game loop */
void ChromaBlade::run(){
	while(m_window.isOpen()){
        float deltaTime = m_fpsTimer.restart().asSeconds();
        handleInput(deltaTime);
		handleEvents(deltaTime);
        update(deltaTime);
        render();
	}
}


/* Calls playerView to handle player inputs */
void ChromaBlade::handleInput(float deltaTime) {
    m_view.handleInput(deltaTime);
}


/* Update game logic, currently does nothing */
void ChromaBlade::update(float &deltaTime) {
    if (m_state == GameState::Game) {
        //m_processManager.update(deltaTime); // update audio, player view, game logic; could be hard-coded instead
    }
}


/* Calls playerView to render */
void ChromaBlade::render() {
    m_view.draw();
}


/* Set the game state */
void ChromaBlade::setState(GameState state) {
    m_state = state;
}


 /* Get the game state */
GameState ChromaBlade::getState() {
    return m_state;
}


void ChromaBlade::registerListeners() {
    /* Subscribe to events. */
    std::function<void(const EventInterface &event)> closeScreen = std::bind(&ChromaBlade::shutdown, this, std::placeholders::_1);
    const EventListener m_listener = EventListener(closeScreen, 0);
    m_eventManager.addListener(m_listener, EventType::sfmlEvent);

    std::function<void(const EventInterface &event)> changeState = std::bind(&ChromaBlade::updateState, this, std::placeholders::_1);
    const EventListener m_listener1 = EventListener(changeState, 1);
    m_eventManager.addListener(m_listener1, EventType::changeStateEvent);
}


void ChromaBlade::handleEvents(float deltaTime) {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        // Only queue input events to avoid overloading event manager.
        if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed) {
            m_eventManager.queueEvent(event);
        }
    }
    m_eventManager.update(deltaTime);
}


void ChromaBlade::shutdown(const EventInterface &event) {
    const EventInterface *ptr = &event;

    // Convert to SFML inherited class.
    if (const SFMLEvent *sfEvent = dynamic_cast<const SFMLEvent*>(ptr)){
        if (sfEvent->getSFMLEvent().type == sf::Event::Closed) {
            m_window.close();
        }
    }
}

/* Update m_state to game state. */
void ChromaBlade::updateState(const EventInterface &event) {
    const EventInterface *ptr = &event;
    std::cout<<"State change";
    if (const ChangeStateEvent *stateEvent = dynamic_cast<const ChangeStateEvent*>(ptr)){
        m_state = stateEvent->getGameState();
        switch(m_state) {
            case GameState::Title:
                std::cout<<"TITLE";
                break;
            case GameState::Game:
                // TODO: remove Title listener
                m_view.setListener(&m_eventManager);
                std::cout<<"GAME";
                break;
        }
    }
}
