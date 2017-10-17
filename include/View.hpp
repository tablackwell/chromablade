#ifndef VIEW
#define VIEW
#include <SFML/Graphics.hpp>

class View{
public:
  View();
  void update();
  void init();
  void handleEvents();
  bool isOpen();
private: //methods
private: //vars and objs
  sf::RenderWindow window;
};

#endif
