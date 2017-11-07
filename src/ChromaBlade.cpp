#include "ChromaBlade.hpp"
#include "PlayerView.hpp"
#include "GameLogic.hpp"
#include "TileMap.hpp"
#include "CollisionMap.hpp"
#include <cstdio>


ChromaBlade::ChromaBlade() : m_window(sf::VideoMode(WIDTH,HEIGHT,32), "Chromablade - Alpha build", sf::Style::Titlebar | sf::Style::Close)
{
}


void ChromaBlade::init(){
	m_view.setContext(&m_window);
	m_view.setGameLogic(m_gameLogic);

    /* Load title screen. */
    m_title.init();

    /* Play music on start. */
    m_audio.init();

    /* Load sample game room. */
    m_map.loadFromText("../res/tilesets/lightworld.png","../res/level/TestLevel/test_base.csv", sf::Vector2u(16, 16), 100, 38);
    m_overlay.loadFromText("../res/tilesets/lightworld.png","../res/level/TestLevel/test_overlay.csv", sf::Vector2u(16, 16),100, 38);
		m_collisionMap.loadFromText("../res/tilesets/lightworld.png","../res/level/TestLevel/test_collisions.csv", sf::Vector2u(16, 16), 100, 38);
		m_view.setCollisionMap(&m_collisionMap); // breaks our rules of encapsulation, only for debug
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
	while(m_view.isOpen()){
		float deltaTime = m_fpsTimer.restart().asSeconds();
        // TODO: integrate EventManager
        //handleEvents();

        update(deltaTime);
        render();
	}
}

void ChromaBlade::handleEvents() {
}

void ChromaBlade::update(float &deltaTime) {
    /* Naive switch to handle game state transitions. */
    int rc;
    switch (m_state) {
        case GameState::Title:
            rc = m_title.update(m_window);
            if (rc == 0) {}
            // Selected Play
            else if (rc == 1) m_state = GameState::Game;
            // Selected Exit
            else m_window.close();
            break;
        case GameState::Game:
            m_processManager.update(deltaTime);
            break;
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
