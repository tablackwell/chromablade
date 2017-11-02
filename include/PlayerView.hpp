#ifndef PLAYERVIEW_HPP
#define PLAYERVIEW_HPP

#include <SFML/Graphics.hpp>
#include "Process.hpp"
#include "GameLogic.hpp"


class PlayerView : public Process {
public:
PlayerView();
	void init();
	void update(float &deltaTime);
    void draw();
	void setContext(sf::RenderWindow* window);
	void handleEvents(float);
	bool isOpen();
	void setGameLogic(GameLogic gameLogic);
private: //methods

private: //vars and objs
    sf::RenderWindow* targetWindow;
	sf::Sprite character;
	sf::Texture charTexture;
	float speed;
	bool notReleased;
	GameLogic gameLogic;
};

#endif
