#ifndef PLAYERVIEW_HPP
#define PLAYERVIEW_HPP

#include <SFML/Graphics.hpp>
#include "Process.hpp"
#include "GameLogic.hpp"
#include "TileMap.hpp"


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
	void setCollisionMap(TileMap* m_collisionMap);
	void checkTiles();
private: //methods

private: //vars and objs
  sf::RenderWindow* targetWindow;
	sf::Sprite character;
	sf::RectangleShape debugBox;
	sf::Texture charTexture;
	float speed;
	bool notReleased;
	GameLogic gameLogic;
	TileMap* m_collisionMap;
	sf::View camera;
	void updateCamera();

};

#endif
