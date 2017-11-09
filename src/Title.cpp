#include "ChromaBlade.hpp"
#include "Title.hpp"

#include <iostream>

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
    m_background.setSize(sf::Vector2f(WIDTH / 2, HEIGHT / 2));
    m_background.setPosition(sf::Vector2f(200, 40));

    // create font
    if (!m_font.loadFromFile("../res/PressStart2P.ttf")) {
        fprintf(stderr, "%s:%d: cannot load font\n",
                __FILE__, __LINE__);
        return;
    }

    // menu text
    m_play.setString("Play");
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
    centerText(m_play);
    centerText(m_exit);
    moveCursor(m_play);
}

void Title::setWindow(sf::RenderWindow *window) {
    m_window = window;
}

void Title::setListener(EventManager *eventManager) {
    m_eventManager = eventManager;
    
    // Create function for listener. Add to event manager.
    std::function<void(const EventInterface &event)> titleScreen = std::bind(&Title::update, this, std::placeholders::_1);
    const EventListener m_listener = EventListener(titleScreen, 2);
    m_eventManager->addListener(m_listener, EventType::sfmlEvent);
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


/* Update title screen based on keyPressed event. */
void Title::update(const EventInterface &event) {
    const EventInterface *ptr = &event;
    
    // Convert to SFML inherited class.
    if (const SFMLEvent *sfEvent = dynamic_cast<const SFMLEvent*>(ptr)){
        
        sf::Event sfmlEvent = sfEvent->getSFMLEvent();
        
        if (sfmlEvent.type == sf::Event::KeyPressed) {
            if (sfmlEvent.key.code == sf::Keyboard::Down) {
                if (checkCursor(m_play)) moveCursor(m_exit);
            } else if (sfmlEvent.key.code == sf::Keyboard::Up) {
                if (checkCursor(m_exit)) moveCursor(m_play);
            } else if (sfmlEvent.key.code == sf::Keyboard::Return) {
                // Exit game
                if (checkCursor(m_exit)) {
                    sf::Event event;
                    event.type = sf::Event::Closed;
                    m_eventManager->queueEvent(event);
                }
                // Change game state
                else {
                    const ChangeStateEvent *event = new ChangeStateEvent(GameState::Game);
                    m_eventManager->queueEvent((EventInterface*)event);
                }
            }
        }
    }
}
