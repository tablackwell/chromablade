#ifndef TITLE_HPP
#define TITLE_HPP
#include <SFML/Graphics.hpp>

#include "ChromaBlade.hpp"
#include "EventListener.hpp"
#include "EventManager.hpp"
#include "EventInterface.hpp"

class Title {
public:
    Title();
    ~Title();
    
    void setWindow(sf::RenderWindow *window);
    void setListener(EventManager *eventManager);

    void init();
    void draw(sf::RenderWindow &window);
	void update(const EventInterface& event);
    
private:
    void centerText(sf::Text &text);
    void moveCursor(const sf::Text &text);
    int checkCursor(const sf::Text &text);
    
    EventManager *m_eventManager;
    sf::RenderWindow *m_window;
    sf::Texture m_texture;
    sf::RectangleShape m_background;
    sf::Font m_font;
    sf::Text m_play;
    sf::Text m_exit;
    sf::Text m_cursor;
};

#endif
