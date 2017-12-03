#ifndef PLAYERDIED_HPP
#define PLAYERDIED_HPP
#include <SFML/Graphics.hpp>
#include "EventListener.hpp"
#include "EventManager.hpp"
#include "EventInterface.hpp"

class PlayerDied {
public:
    PlayerDied();
    ~PlayerDied();
    void setWindow(sf::RenderWindow *window);
    void init();
    void draw(sf::RenderWindow &window);
	int update(sf::RenderWindow &window);
    
private:
    void centerText(sf::Text &text);
    void moveCursor(const sf::Text &text);
    int checkCursor(const sf::Text &text);
    
private:
    sf::RectangleShape m_background;
    sf::Font m_font;
    sf::Text m_died;
    sf::Text m_play;
    sf::Text m_exit;
    sf::Text m_cursor;
};

#endif
