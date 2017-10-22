#include "ChromaBlade.hpp"
#include "Title.hpp"

Title::Title() { init(); };
Title::~Title() { };

void Title::init() {
    // create font
    if (!m_font.loadFromFile("../res/PressStart2P.ttf")) {
        fprintf(stderr, "%s:%d: cannot load font\n",
                __FILE__, __LINE__);
        return;
    }

    // create menu text
    m_title.setString("CHROMABLADE");
    m_title.setFont(m_font);
    m_title.setCharacterSize(96);
    m_title.setFillColor(sf::Color::White);
    m_title.setPosition(0, HEIGHT / 6.0);

    m_play.setString("Play");
    m_play.setFont(m_font);
    m_play.setCharacterSize(24);
    m_play.setFillColor(sf::Color::White);
    m_play.setPosition(0, HEIGHT / 1.75);

    m_exit.setString("Exit");
    m_exit.setFont(m_font);
    m_exit.setCharacterSize(24);
    m_exit.setFillColor(sf::Color::White);
    m_exit.setPosition(0, HEIGHT / 1.5);

    // center text
    centerText(m_title);
    centerText(m_play);
    centerText(m_exit);
}

void Title::draw(sf::RenderWindow &window) {
    window.draw(m_title);
    window.draw(m_play);
    window.draw(m_exit);
}

/* Centers text based on dimensions. */
void Title::centerText(sf::Text &text) {
    sf::FloatRect g = text.getGlobalBounds();
    sf::FloatRect l = text.getLocalBounds();
    text.setPosition((WIDTH - g.width) / 2, g.top - l.top);
}
