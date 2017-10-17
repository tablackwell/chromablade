#ifndef PLAYERVIEW
#define PLAYERVIEW
#include <SFML/Graphics.hpp>

class PlayerView{
public:
  PlayerView();
  void update();
  void init();
  void handleEvents();
  bool isOpen();
private: //methods
private: //vars and objs
  sf::RenderWindow window;
};

#endif
