#include <ChromaBlade.hpp>
#include <PlayerView.hpp>
#include <GameLogic.hpp>
#include <TileMap.hpp>


ChromaBlade::ChromaBlade() : m_window(sf::VideoMode(WIDTH,HEIGHT,32), "Chromablade - Alpha build", sf::Style::Titlebar | sf::Style::Close)
{
    init();
}


void ChromaBlade::init(){
	m_view.init();
	m_gameLogic.init();
	m_view.setContext(&m_window);

	const int level[] =
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

	m_map.load("../res/tileset.png", sf::Vector2u(32, 32), level, 16, 8);
}

void ChromaBlade::run(){
	/* Main game loop */

	while(m_view.isOpen()){
		float deltaTime = m_fpsTimer.restart().asSeconds();
		m_view.handleEvents();
		m_gameLogic.update(deltaTime);
		m_window.clear();
		m_window.draw(m_map);
		m_window.display();
//		view.update();
	}
}
