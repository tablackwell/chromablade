#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <SFML/Graphics.hpp>
#include "EventListener.hpp"
#include "EventManager.hpp"
#include "EventInterface.hpp"


class Instruction {
public:
    Instruction();
    ~Instruction();
    void init();
    void draw(sf::RenderWindow &window);
    int update(sf::RenderWindow &window);

private:
    void centerText(sf::Text &text);
    void setCursor(const sf::Text &text);

private:
    sf::Font m_font;
    sf::Text m_instruction;
    sf::Text m_menu;
    sf::Text m_cursor;
};

#endif
