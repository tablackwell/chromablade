#ifndef TITLE_HPP
#define TITLE_HPP
#include <SFML/Graphics.hpp>

#include "EventListener.hpp"
#include "EventManager.hpp"
#include "EventInterface.hpp"

class Title {
public:
    Title();
    ~Title();
    
    void setListener(EventManager *eventManager);

    void draw(sf::RenderWindow &window);
	void update(const EventInterface& event);
    
private:
    void init();
    void centerText(sf::Text &text);
    void moveCursor(const sf::Text &text);
    int checkCursor(const sf::Text &text);

    sf::Texture m_texture;
    sf::RectangleShape m_background;
    sf::Font m_font;
    sf::Text m_play;
    sf::Text m_exit;
    sf::Text m_cursor;
};

#endif
