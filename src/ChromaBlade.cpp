#include "ChromaBlade.hpp"
#include "PlayerView.hpp"
#include "GameLogic.hpp"

#include <cstdio>
#include <iostream>


/* The game application layer */
ChromaBlade::ChromaBlade() : m_window(sf::VideoMode(WIDTH,HEIGHT,32), "Chromablade - Alpha build", sf::Style::Titlebar | sf::Style::Close)
{
    /* Starts on the Title screen. */
    m_state = GameState::Title;

    m_gameLogic.setGameApplication(this);
    m_view.setGameLogic(&m_gameLogic);
    m_view.setContext(&m_window);
    m_view.setGameApplication(this);
    m_eventManager.setWindow(&m_window);
    m_window.setVerticalSyncEnabled(true);
}


void ChromaBlade::init(){
    m_gameLogic.init();
    m_view.init();

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
        update(deltaTime);
        handleEvents(deltaTime);
        render();
	}
}


/* Calls playerView to handle player inputs */
void ChromaBlade::handleInput(float deltaTime) {
    m_view.handleInput(deltaTime);
}


/* Updates game logic */
void ChromaBlade::update(float &deltaTime) {
    if (m_state == GameState::Game) {
        //m_processManager.update(deltaTime); // update audio, player view, game logic; could be hard-coded instead
        // TODO: update game logic here
    }
}


/* Processes events in eventManager */
void ChromaBlade::handleEvents(float deltaTime) {
    m_eventManager.update(deltaTime);
}


/* Calls playerView to render */
void ChromaBlade::render() {
    m_view.draw();
}


/* Sets the game state */
void ChromaBlade::setState(GameState state) {
    m_state = state;
}


 /* Gets the game state */
GameState ChromaBlade::getState() {
    return m_state;
}


/* Allows other components to register listeners */
void ChromaBlade::registerListener(EventListener listener, EventType eventType) {
    m_eventManager.addListener(listener, eventType);
}


/* Allows other components to queue events */
void ChromaBlade::queueEvent(EventInterface *event) {
    m_eventManager.queueEvent(event);
}
