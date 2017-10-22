#include <ChromaBlade.hpp>

ChromaBlade::ChromaBlade() : m_window(sf::VideoMode(WIDTH,HEIGHT,32), "Chromablade - Alpha build", sf::Style::Titlebar | sf::Style::Close)
{
	// initialize view
	// initialize game logic
}


void ChromaBlade::init(){
	m_view.setContext(&m_window);

	m_map;
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
		//view.update();

		m_window.clear();
		m_window.draw(m_map);
		m_window.display();
		m_gameLogic.update(deltaTime);
		m_view.handleEvents();
	}
}
