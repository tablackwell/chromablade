#include "ChromaBlade.hpp"
#include "Pause.hpp"

#include <iostream>
Pause::Pause() { };
Pause::~Pause() { };

void Pause::init() {

    // Load background
    if (!m_texture.loadFromFile("../res/chromablade.png")) {
        fprintf(stderr, "%s:%d: cannot load texture\n",
                __FILE__, __LINE__);
        return;
    }
    m_background.setTexture(&m_texture);
    m_background.setSize(sf::Vector2f(WIDTH / 3, HEIGHT / 3));
    m_background.setPosition(sf::Vector2f(WIDTH / 3, 100));

    // Load font
    if (!m_font.loadFromFile("../res/OpenSans.ttf")) {
        fprintf(stderr, "%s:%d: cannot load font\n",
                __FILE__, __LINE__);
        return;
    }

    // Title
    m_pause.setString("Game Paused");
    m_pause.setFont(m_font);
    m_pause.setStyle(sf::Text::Style::Italic);
    m_pause.setCharacterSize(24);
    m_pause.setFillColor(sf::Color::White);
    m_pause.setOutlineColor(sf::Color::Black);
    m_pause.setOutlineThickness(1.0);
    m_pause.setPosition(0, 40);

    // Colors
    m_colors.setString("Dungeons Cleared:");
    m_colors.setFont(m_font);
    m_colors.setStyle(sf::Text::Style::Italic);
    m_colors.setCharacterSize(24);
    m_colors.setFillColor(sf::Color::White);
    m_colors.setOutlineColor(sf::Color::Black);
    m_colors.setOutlineThickness(1.0);
    m_colors.setPosition(150, HEIGHT / 1.8);

    m_red.setFillColor(sf::Color(255, 0, 0));
    m_red.setSize(sf::Vector2f(25, 25));
    m_red.setPosition(sf::Vector2f(600, HEIGHT / 1.8));

    m_blue.setFillColor(sf::Color(0, 0, 255));
    m_blue.setSize(sf::Vector2f(25, 25));
    m_blue.setPosition(sf::Vector2f(650, HEIGHT / 1.8));

    m_yellow.setFillColor(sf::Color(255,255, 0));
    m_yellow.setSize(sf::Vector2f(25, 25));
    m_yellow.setPosition(sf::Vector2f(700, HEIGHT / 1.8));

    // Menu text
    m_play.setString("Resume");
    m_play.setFont(m_font);
    m_play.setStyle(sf::Text::Style::Italic);
    m_play.setCharacterSize(24);
    m_play.setFillColor(sf::Color::White);
    m_play.setOutlineColor(sf::Color::Black);
    m_play.setOutlineThickness(1.0);
    m_play.setPosition(0, HEIGHT / 1.5);

    m_exit.setString("Quit");
    m_exit.setFont(m_font);
    m_exit.setStyle(sf::Text::Style::Italic);
    m_exit.setCharacterSize(24);
    m_exit.setFillColor(sf::Color::White);
    m_exit.setOutlineColor(sf::Color::Black);
    m_exit.setOutlineThickness(1.0);
    m_exit.setPosition(0, HEIGHT / 1.35);

    // Menu cursor
    m_cursor.setString(">");
    m_cursor.setFont(m_font);
    m_cursor.setStyle(sf::Text::Style::Italic);
    m_cursor.setCharacterSize(24);
    m_cursor.setFillColor(sf::Color::White);
    m_cursor.setOutlineColor(sf::Color::Black);
    m_cursor.setOutlineThickness(1.0);

    // Align text
    centerText(m_pause);
    centerText(m_play);
    centerText(m_exit);
    moveCursor(m_play);
}


/* Draws the title page */
void Pause::draw(sf::RenderWindow &window) {
    window.draw(m_background);
    window.draw(m_pause);
    window.draw(m_colors);
    window.draw(m_red);
    window.draw(m_blue);
    window.draw(m_yellow);
    window.draw(m_play);
    window.draw(m_exit);
    window.draw(m_cursor);
}

/* Centers text based on dimensions. */
void Pause::centerText(sf::Text &text) {
    sf::FloatRect g = text.getGlobalBounds();
    sf::FloatRect l = text.getLocalBounds();
    text.setPosition((WIDTH - g.width) / 2, g.top - l.top);
}


/* Moves the menu cursor on Up and Down key press. */
void Pause::moveCursor(const sf::Text &text) {
    m_cursor.setPosition(text.getPosition().x - WIDTH / 20.0,text.getPosition().y);
}


/* Checks which option the cursor is at. */
int Pause::checkCursor(const sf::Text &text) {
    return m_cursor.getPosition().y == text.getPosition().y;
}


/* Returns an integer that indicates the action based on keyboard input. */
int Pause::update(sf::RenderWindow &window) {
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
