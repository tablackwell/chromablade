#include "ChromaBlade.hpp"
#include "PlayerDied.hpp"

#include <iostream>
PlayerDied::PlayerDied() { };
PlayerDied::~PlayerDied() { };

void PlayerDied::init() {

    m_background.setFillColor(sf::Color(0, 0, 0, 125));
    m_background.setSize(sf::Vector2f(WIDTH, HEIGHT));
    m_background.setPosition(0, 0);

    // load font
    if (!m_font.loadFromFile("../res/OpenSans.ttf")) {
        fprintf(stderr, "%s:%d: cannot load font\n",
                __FILE__, __LINE__);
        return;
    }

    // menu text
    m_died.setString("Oh No! You died!");
    m_died.setFont(m_font);
    m_died.setStyle(sf::Text::Style::Italic);
    m_died.setCharacterSize(24);
    m_died.setFillColor(sf::Color::White);
    m_died.setOutlineColor(sf::Color::Black);
    m_died.setOutlineThickness(1.0);
    m_died.setPosition(0, HEIGHT / 2);

    m_play.setString("Restart");
    m_play.setFont(m_font);
    m_play.setStyle(sf::Text::Style::Italic);
    m_play.setCharacterSize(24);
    m_play.setFillColor(sf::Color::White);
    m_play.setOutlineColor(sf::Color::Black);
    m_play.setOutlineThickness(1.0);
    m_play.setPosition(0, HEIGHT / 1.5);

    m_exit.setString("Exit");
    m_exit.setFont(m_font);
    m_exit.setStyle(sf::Text::Style::Italic);
    m_exit.setCharacterSize(24);
    m_exit.setFillColor(sf::Color::White);
    m_exit.setOutlineColor(sf::Color::Black);
    m_exit.setOutlineThickness(1.0);
    m_exit.setPosition(0, HEIGHT / 1.35);

    // create menu cursor
    m_cursor.setString(">");
    m_cursor.setFont(m_font);
    m_cursor.setStyle(sf::Text::Style::Italic);
    m_cursor.setCharacterSize(24);
    m_cursor.setFillColor(sf::Color::White);
    m_cursor.setOutlineColor(sf::Color::Black);
    m_cursor.setOutlineThickness(1.0);

    // align text
    centerText(m_died);
    centerText(m_play);
    centerText(m_exit);
    moveCursor(m_play);
}


/* Draws the title page */
void PlayerDied::draw(sf::RenderWindow &window) {
    window.setView(window.getDefaultView());
    window.draw(m_background);
    window.draw(m_died);
    window.draw(m_play);
    window.draw(m_exit);
    window.draw(m_cursor);
}


/* Centers text based on dimensions. */
void PlayerDied::centerText(sf::Text &text) {
    sf::FloatRect g = text.getGlobalBounds();
    sf::FloatRect l = text.getLocalBounds();
    text.setPosition((WIDTH - g.width) / 2, g.top - l.top);
}


/* Moves the menu cursor on Up and Down key press. */
void PlayerDied::moveCursor(const sf::Text &text) {
    m_cursor.setPosition(text.getPosition().x - WIDTH / 20.0,
                       text.getPosition().y);
}


/* Checks which option the cursor is at. */
int PlayerDied::checkCursor(const sf::Text &text) {
    return m_cursor.getPosition().y == text.getPosition().y;
}


/* Returns an integer that indicates the action based on keyboard input. */
int PlayerDied::update(sf::RenderWindow &window) {
    sf::Event event;
    while(window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Down) {
                    if (checkCursor(m_play)) moveCursor(m_exit); // will return 0
                } else if (event.key.code == sf::Keyboard::Up) {
                    if (checkCursor(m_exit)) moveCursor(m_play); // will return 0
                } else if (event.key.code == sf::Keyboard::Return) {
                    if (checkCursor(m_play)) return 1;
                    else if (checkCursor(m_exit)) return 2;
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
