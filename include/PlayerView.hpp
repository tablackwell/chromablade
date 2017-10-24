#ifndef PLAYERVIEW_HPP
#define PLAYERVIEW_HPP

#include <SFML/Graphics.hpp>
<<<<<<< HEAD
#include "EventInterface.hpp"
=======
#include "Process.hpp"

>>>>>>> origin/master

class PlayerView : public Process {
public:
    PlayerView();
	void init();
	void update(float &deltaTime);
    void draw();
	void setContext(sf::RenderWindow* window);
	void handleEvents(float);
	bool isOpen();
private: //methods

private: //vars and objs
    sf::RenderWindow* targetWindow;
	sf::Sprite character;
	sf::Texture charTexture;
<<<<<<< HEAD
	void moveEventListener(const EventInterface& moveEvent);
=======
	float speed;
	bool notReleased;
>>>>>>> origin/master
};

#endif
