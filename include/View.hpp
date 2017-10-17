#ifndef VIEW
#define VIEW
#include <SFML/Graphics.hpp>

class View{
public:
  View();
  void update();
  void init();
  void setContext(sf::RenderWindow* window);
  void handleEvents();
  bool isOpen();
private: //methods
private: //vars and objs
  sf::RenderWindow* targetWindow;
};

#endif
