#include "ChromaBlade.hpp"
#include "PlayerView.hpp"
#include "GameLogic.hpp"
#include "TileMap.hpp"
#include <cstdio>


ChromaBlade::ChromaBlade() : m_window(sf::VideoMode(WIDTH,HEIGHT,32), "Chromablade - Alpha build", sf::Style::Titlebar | sf::Style::Close)
{
}


void ChromaBlade::init(){
	m_view.setContext(&m_window);

    m_audio.init();

    m_map.loadFromText("../res/tilesets/lightworld.png","../res/level/demolevel_base.csv", sf::Vector2u(16, 16), 50, 38);
    m_overlay.loadFromText("../res/tilesets/lightworld.png","../res/level/demolevel_overlay.csv", sf::Vector2u(16, 16), 50, 38);
	m_window.setVerticalSyncEnabled(true);

    m_processManager.attachProcess(&m_view);
    m_processManager.attachProcess(&m_gameLogic);
    m_processManager.attachProcess(&m_audio);

    m_state = GameState::Title;
}

void ChromaBlade::run(){
	/* Main game loop */
	while(m_view.isOpen()){
		float deltaTime = m_fpsTimer.restart().asSeconds();
        //handleEvents();
        update(deltaTime);
        render();
	}
}

void ChromaBlade::handleEvents() {
}

void ChromaBlade::update(float &deltaTime) {
    int rc;
    switch (m_state) {
        case GameState::Title:
            rc = m_title.update(m_window);
            if (rc == 0) {}
            else if (rc == 1) m_state = GameState::Game;
            else m_window.close();
            break;
        case GameState::Game:
            m_processManager.update(deltaTime);
            break;
    }
}

void ChromaBlade::render() {
    m_window.clear();

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
