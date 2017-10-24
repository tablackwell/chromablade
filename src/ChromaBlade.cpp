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
	m_window.setVerticalSyncEnabled(true);

//    m_processManager.attachProcess(&m_view);
//    m_processManager.attachProcess(&m_gameLogic);
//    m_processManager.attachProcess(&m_audio);
}

void ChromaBlade::run(){
	/* Main game loop */
	while(m_view.isOpen()){
		float deltaTime = m_fpsTimer.restart().asSeconds();
        handleEvents(deltaTime);
//        update(deltaTime);
        render();
//        m_window.clear();
//        m_view.draw();
//        m_window.display();
	}
}

void ChromaBlade::handleEvents(float deltaTime) {
    m_view.handleEvents(deltaTime);
}

void ChromaBlade::update(float &deltaTime) {
    m_processManager.update(deltaTime);
}


void ChromaBlade::render() {
    m_window.clear();

    /* Draw things */
//    m_title.draw(m_window);


    /* Demo Level Code*/
    m_window.draw(m_map);
    m_window.draw(m_overlay);
    m_view.draw();
    m_window.display();
}
