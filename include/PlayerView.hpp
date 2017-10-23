#ifndef PLAYERVIEW_HPP
#define PLAYERVIEW_HPP

#include <SFML/Graphics.hpp>


class PlayerView{
public:
PlayerView();
	void init();
	void update();
	void setContext(sf::RenderWindow* window);
	void handleEvents(float);
	bool isOpen();
private: //methods

private: //vars and objs
    sf::RenderWindow* targetWindow;
	sf::Sprite character;
	sf::Texture charTexture;
};

#endif
