#include "ChromaBlade.hpp"
#include "PlayerView.hpp"
#include "GameLogic.hpp"
#include "TileMap.hpp"


ChromaBlade::ChromaBlade() : m_window(sf::VideoMode(WIDTH,HEIGHT,32), "Chromablade - Alpha build", sf::Style::Titlebar | sf::Style::Close)
{
    init();
}


void ChromaBlade::init(){
	m_view.init();
	m_gameLogic.init();

	m_view.setContext(&m_window);

	m_map.loadFromText("../res/tilesets/lightworld.png","../res/level/demolevel_base.csv", sf::Vector2u(16, 16), 50, 38);
	m_overlay.loadFromText("../res/tilesets/lightworld.png","../res/level/demolevel_overlay.csv", sf::Vector2u(16, 16), 50, 38);
	m_window.setVerticalSyncEnabled(true);
}

void ChromaBlade::run(){
	/* Main game loop */
	while(m_view.isOpen()){
		float deltaTime = m_fpsTimer.restart().asSeconds();
        handleEvents(deltaTime);
//        update(deltaTime);
        render();
        /*
		m_view.handleEvents();
		m_gameLogic.update(deltaTime);
		m_window.clear();
        m_title.draw(m_window);
		m_window.display();
        */
		m_view.update();
	}
}

void ChromaBlade::handleEvents(float deltaTime) {
    m_view.handleEvents(deltaTime);
}

void ChromaBlade::update(float &deltaTime) {
    m_gameLogic.update(deltaTime);
}

void ChromaBlade::render() {
    m_window.clear();

    /* Draw things */
//    m_title.draw(m_window);

    /* Demo Level Code*/
    m_window.draw(m_map);
    m_window.draw(m_overlay);
//    m_window.display();
}
