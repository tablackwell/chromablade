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


/* Update game logic */
void ChromaBlade::update(float &deltaTime) {
    if (m_state == GameState::Game) {
        //m_processManager.update(deltaTime); // update audio, player view, game logic; could be hard-coded instead
        // TODO: updat game logic here
    }
}


/* Process events in eventManager */
void ChromaBlade::handleEvents(float deltaTime) {
    m_eventManager.update(deltaTime);
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
