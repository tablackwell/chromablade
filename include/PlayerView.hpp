#ifndef VIEW
#define VIEW
#include <SFML/Graphics.hpp>

class PlayerView{
	public:
		PlayerView();
		void init();
		void update();
		void setContext(sf::RenderWindow* window);
		void handleEvents();
		bool isOpen();
	private: //methods

	private: //vars and objs
		sf::RenderWindow* targetWindow;
};

#endif
