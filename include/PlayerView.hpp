#ifndef PLAYERVIEW_HPP
#define PLAYERVIEW_HPP

#include <SFML/Graphics.hpp>
#include "EventInterface.hpp"

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
	sf::Sprite character;
	sf::Texture charTexture;
	void moveEventListener(const EventInterface& moveEvent);
};

#endif
