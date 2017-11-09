#include "ChromaBlade.hpp"

#include <cstdio>
#include <iostream>


ChromaBlade::ChromaBlade() : m_window(sf::VideoMode(WIDTH,HEIGHT,32), "Chromablade - Alpha build", sf::Style::Titlebar | sf::Style::Close)
{
}


void ChromaBlade::init(){
    m_view.setContext(&m_window);
    m_eventManager.setWindow(&m_window);
    m_title.setWindow(&m_window);
  	m_view.setGameLogic(m_gameLogic);

    /* Load title screen. */
    m_title.init();
  
    /* Subscribe to events. */
    std::function<void(const EventInterface &event)> closeScreen = std::bind(&ChromaBlade::shutdown, this, std::placeholders::_1);
    const EventListener m_listener = EventListener(closeScreen, 0);
    m_eventManager.addListener(m_listener, EventType::sfmlEvent);
    
    std::function<void(const EventInterface &event)> changeState = std::bind(&ChromaBlade::updateState, this, std::placeholders::_1);
    const EventListener m_listener1 = EventListener(changeState, 1);
    m_eventManager.addListener(m_listener1, EventType::changeStateEvent);
    
    m_title.setListener(&m_eventManager);

    /* Play music on start. */
    m_audio.init();

    /* Load sample game room. */
    m_map.loadFromText("../res/tilesets/lightworld.png","../res/level/demolevel_base.csv", sf::Vector2u(16, 16), 50, 38);
    m_overlay.loadFromText("../res/tilesets/lightworld.png","../res/level/demolevel_overlay.csv", sf::Vector2u(16, 16), 50, 38);
	m_window.setVerticalSyncEnabled(true);

    /* Attach PlayerView, GameLogic, and Audio to ProcessManager. */
    m_processManager.attachProcess(&m_view);
    m_processManager.attachProcess(&m_gameLogic);
    m_processManager.attachProcess(&m_audio);

    /* Start on the Title screen. */
    m_state = GameState::Title;
}

void ChromaBlade::run(){
	/* Main game loop */
	while(m_window.isOpen()){
        float deltaTime = m_fpsTimer.restart().asSeconds();
		handleEvents(deltaTime);
        //update(deltaTime);
        render();
	}
}

void ChromaBlade::handleEvents(float deltaTime) {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        // Only queue input events to avoid overloading event manager.
        if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed) {
            m_eventManager.queueEvent(event, deltaTime);
        }
    }
    
    m_eventManager.update();
}

void ChromaBlade::update(float &deltaTime) {
    /* Naive switch to handle game state transitions. */
    switch (m_state) {
        case GameState::Title:
            break;
        case GameState::Game:
            m_processManager.update(deltaTime);
            break;
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


void ChromaBlade::render() {
    m_window.clear();

    /* Naive switch to handle game state transitions. */
    /* Draw things */
    switch(m_state) {
        case GameState::Title:
            m_title.draw(m_window);
            break;
        case GameState::Game:
            m_window.draw(m_map);
            m_window.draw(m_overlay);
            m_view.draw();
            break;
    }
    m_window.display();
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
