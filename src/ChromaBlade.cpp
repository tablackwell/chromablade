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

    m_map.loadFromText("../res/tilesets/lightworld.png","../res/level/demolevel_base.csv", sf::Vector2u(16, 16), 50, 38);
    m_overlay.loadFromText("../res/tilesets/lightworld.png","../res/level/demolevel_overlay.csv", sf::Vector2u(16, 16), 50, 38);

    m_processManager.attachProcess(&m_view);
    m_processManager.attachProcess(&m_gameLogic);
}

void ChromaBlade::run(){
	/* Main game loop */

	while(m_view.isOpen()){
		float deltaTime = m_fpsTimer.restart().asSeconds();
        handleEvents();
        update(deltaTime);
        render();
	}
}

void ChromaBlade::handleEvents() {
    m_view.handleEvents();
}

void ChromaBlade::update(float &deltaTime) {
    m_processManager.update(deltaTime);
    //m_gameLogic.update(deltaTime);
}

void ChromaBlade::render() {
    m_window.clear();

    /* Draw things */
    m_title.draw(m_window);
    //m_view.draw();

    /* Demo Level Code*/
    //m_window.draw(m_map);
    //m_window.draw(m_overlay);
    m_window.display();
}
