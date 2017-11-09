#ifndef PLAYERVIEW_HPP
#define PLAYERVIEW_HPP

#include <SFML/Graphics.hpp>
#include "EventInterface.hpp"
#include "Process.hpp"
#include "GameLogic.hpp"

class PlayerView : public Process {
public:
    PlayerView();
	void init();
	void update(float &deltaTime);
    void update1(const EventInterface &event);
    void draw();
	void setContext(sf::RenderWindow* window);
    void setListener(EventManager *eventManager);
	void handleEvents();
	bool isOpen();
	void setGameLogic(GameLogic gameLogic);
private: //methods

private: //vars and objs
    EventManager *m_eventManager;
    sf::RenderWindow* targetWindow;
	sf::Sprite character;
	sf::Texture charTexture;
	void moveEventListener(const EventInterface& moveEvent);
	float speed;
	bool notReleased;
	GameLogic gameLogic;
};

#endif
