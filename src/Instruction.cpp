#include "Instruction.hpp"
#include "Macros.hpp"

#include <iostream>

Instruction::Instruction() { };
Instruction::~Instruction() { };

/* The instruction screen */
void Instruction::init() {

    // load font
    if (!m_font.loadFromFile("../res/OpenSans.ttf")) {
        fprintf(stderr, "%s:%d: cannot load font\n",
                __FILE__, __LINE__);
        return;
    }

    // menu text
    m_instruction.setString("ENTER  -  Select/Pause\nARROW KEYS  -  Movement\nSPACE BAR  -  Attack\n1  -  Red Sword\n2  -  Blue Sword\n3  -  Yellow Sword");
    m_instruction.setFont(m_font);
    m_instruction.setStyle(sf::Text::Style::Italic);
    m_instruction.setCharacterSize(24);
    m_instruction.setFillColor(sf::Color::White);
    m_instruction.setOutlineColor(sf::Color::Black);
    m_instruction.setOutlineThickness(1.0);
    m_instruction.setPosition(0, HEIGHT / 3.5);

    m_menu.setString("menu");
    m_menu.setFont(m_font);
    m_menu.setStyle(sf::Text::Style::Italic);
    m_menu.setCharacterSize(24);
    m_menu.setFillColor(sf::Color::White);
    m_menu.setOutlineColor(sf::Color::Black);
    m_menu.setOutlineThickness(1.0);
    m_menu.setPosition(0, HEIGHT / 1.35);

    // create menu cursor
    m_cursor.setString(">");
    m_cursor.setFont(m_font);
    m_cursor.setStyle(sf::Text::Style::Italic);
    m_cursor.setCharacterSize(24);
    m_cursor.setFillColor(sf::Color::White);
    m_cursor.setOutlineColor(sf::Color::Black);
    m_cursor.setOutlineThickness(1.0);

    // align text
    centerText(m_instruction);
    centerText(m_menu);
    setCursor(m_menu);
}


/* Draws the Instruction page */
void Instruction::draw(sf::RenderWindow &window) {
    window.draw(m_instruction);
    window.draw(m_menu);
    window.draw(m_cursor);
}


/* Centers text based on dimensions. */
void Instruction::centerText(sf::Text &text) {
    sf::FloatRect g = text.getGlobalBounds();
    sf::FloatRect l = text.getLocalBounds();
    text.setPosition((WIDTH - g.width) / 2, g.top - l.top);
}


/* Moves the menu cursor on Up and Down key press. */
void Instruction::setCursor(const sf::Text &text) {
    m_cursor.setPosition(text.getPosition().x - WIDTH / 20.0, text.getPosition().y);
}


/* Returns an integer that indicates the action based on keyboard input. */
int Instruction::update(sf::RenderWindow &window) {
    sf::Event event;
    while(window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Return) {
                    return 1;
                }
                break;
            case sf::Event::Closed:
                return 2;
                break;
            default:
                break;
        }
    }
    return 0;
}
