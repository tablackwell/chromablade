#include "ChromaBlade.hpp"
#include "Title.hpp"

Title::Title() { init(); };
Title::~Title() { };

void Title::init() {

    // background
    if (!m_texture.loadFromFile("../res/chromablade.png")) {
        fprintf(stderr, "%s:%d: cannot load texture\n",
                __FILE__, __LINE__);
        return;
    }
    m_background.setTexture(&m_texture);
    m_background.setSize(sf::Vector2f(WIDTH, HEIGHT));

    // create font
    if (!m_font.loadFromFile("../res/PressStart2P.ttf")) {
        fprintf(stderr, "%s:%d: cannot load font\n",
                __FILE__, __LINE__);
        return;
    }

    // menu text
    m_play.setString("Play");
    m_play.setFont(m_font);
    m_play.setCharacterSize(24);
    m_play.setFillColor(sf::Color::White);
    m_play.setOutlineColor(sf::Color::Black);
    m_play.setOutlineThickness(1.0);
    m_play.setPosition(0, HEIGHT / 1.5);

    m_exit.setString("Exit");
    m_exit.setFont(m_font);
    m_exit.setCharacterSize(24);
    m_exit.setFillColor(sf::Color::White);
    m_exit.setOutlineColor(sf::Color::Black);
    m_exit.setOutlineThickness(1.0);
    m_exit.setPosition(0, HEIGHT / 1.35);

    // create menu cursor
    m_cursor.setString(">");
    m_cursor.setFont(m_font);
    m_cursor.setCharacterSize(24);
    m_cursor.setFillColor(sf::Color::White);
    m_cursor.setOutlineColor(sf::Color::Black);
    m_cursor.setOutlineThickness(1.0);

    // align text
    centerText(m_play);
    centerText(m_exit);
    moveCursor(m_play);
}

void Title::draw(sf::RenderWindow &window) {
    window.draw(m_background);
    window.draw(m_play);
    window.draw(m_exit);
    window.draw(m_cursor);
}

/* Centers text based on dimensions. */
void Title::centerText(sf::Text &text) {
    sf::FloatRect g = text.getGlobalBounds();
    sf::FloatRect l = text.getLocalBounds();
    text.setPosition((WIDTH - g.width) / 2, g.top - l.top);
}

/* Moves the menu cursor on Up and Down keypress. */
void Title::moveCursor(const sf::Text &text) {
    m_cursor.setPosition(text.getPosition().x - WIDTH / 20.0,
                       text.getPosition().y);
}

/* Checks which option the cursor is at. */
int Title::checkCursor(const sf::Text &text) {
    return m_cursor.getPosition().y == text.getPosition().y;
}

