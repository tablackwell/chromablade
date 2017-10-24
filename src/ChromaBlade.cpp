#include "ChromaBlade.hpp"
#include "PlayerView.hpp"
#include "GameLogic.hpp"
#include "TileMap.hpp"

#include <iostream>


ChromaBlade::ChromaBlade() : m_window(sf::VideoMode(WIDTH,HEIGHT,32), "Chromablade - Alpha build", sf::Style::Titlebar | sf::Style::Close)
{
    init();
}


void ChromaBlade::init(){
	m_view.init();
	m_gameLogic.init();

    m_eventManager.setWindow(&m_window);
	m_view.setContext(&m_window);
    m_map.loadFromText("../res/tileset.png", "../res/level/testlevel.txt", sf::Vector2u(32, 32), 16, 8);

  //	m_map.load("../res/tileset.png", sf::Vector2u(32, 32), level, 16, 8);
  /*const int level[] =
    {
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
        0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
        0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
    };
    */
}

void ChromaBlade::run(){
	/* Main game loop */

	while(m_view.isOpen()){
		float deltaTime = m_fpsTimer.restart().asSeconds();
        sf::Event event;
        if (m_window.waitEvent(event)) {
            m_eventManager.queueEvent(event);
        }
        handleEvents();
        update(deltaTime);
        render();
        /*
		m_view.handleEvents();
		m_gameLogic.update(deltaTime);
		m_window.clear();
        m_title.draw(m_window);
		m_window.display();
        */
//		view.update();
	}
}

void ChromaBlade::handleEvents() {
    m_eventManager.handleEvents();
    m_view.handleEvents();
}

void ChromaBlade::update(float &deltaTime) {
    m_gameLogic.update(deltaTime);
}

void ChromaBlade::render() {
    m_window.clear();

    /* Draw things */
    m_title.draw(m_window);
    m_window.display();
}
