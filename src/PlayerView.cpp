#include "PlayerView.hpp"
#include "GameState.hpp"
#include "ChromaBlade.hpp"
#include "KeySetting.hpp"
#include "MoveEvent.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdio>
#include <tuple>
#include <iostream>

#define START_POS sf::Vector2f(196, 235)
#define SPEED 200.f

PlayerView::PlayerView() : Process() {
}

/* Initialize player view by loading files and setting initial positions */
void PlayerView::init(){

    // Load title screen.
    m_title.init();

    // Load map and overlay of sample room
     m_map.loadFromText("../res/tilesets/lightworld.png","../res/level/demolevel_base.csv", sf::Vector2u(16, 16), 50, 38);
     m_overlay.loadFromText("../res/tilesets/lightworld.png","../res/level/demolevel_overlay.csv", sf::Vector2u(16, 16), 50, 38);

	// Load texture for character
    if(!m_charTexture.loadFromFile("../res/sprite.png")) {
		// ERROR
	}
//    m_character.setTextureRect(sf::IntRect(32, 0, 32, 32));
    
    walkingDown.setSpriteSheet(m_charTexture);
    walkingDown.addFrame(sf::IntRect(0, 0, 32, 32));
    walkingDown.addFrame(sf::IntRect(0, 32, 32, 32));
    walkingDown.addFrame(sf::IntRect(0, 64, 32, 32));
    walkingDown.addFrame(sf::IntRect(0, 96, 32, 32));
    
    walkingLeft.setSpriteSheet(m_charTexture);
    walkingLeft.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    walkingLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    walkingLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    
    walkingRight.setSpriteSheet(m_charTexture);
    walkingRight.addFrame(sf::IntRect(96, 0, 32, 32));
    walkingRight.addFrame(sf::IntRect(96, 32, 32, 32));
    walkingRight.addFrame(sf::IntRect(96, 64, 32, 32));
    walkingRight.addFrame(sf::IntRect(96, 96, 32, 32));
    
    walkingUp.setSpriteSheet(m_charTexture);
    walkingUp.addFrame(sf::IntRect(64, 0, 32, 32));
    walkingUp.addFrame(sf::IntRect(64, 32, 32, 32));
    walkingUp.addFrame(sf::IntRect(64, 64, 32, 32));
    walkingUp.addFrame(sf::IntRect(64, 96, 32, 32));

    currAnimation = &walkingDown;
    animatedSprite.setPosition(START_POS);
//    m_character.setTexture(m_charTexture);
//	m_character.setPosition(START_POS);
	animatedSprite.setScale(1.2f,1.2f);
    setState(Process::RUNNING);
    m_speed = SPEED;
    registerListener();
}


/* Set the window of the view */
void PlayerView::setContext(sf::RenderWindow* window){
	m_window = window;
}


/* Link the game logic with player view */
void PlayerView::setGameLogic(GameLogic* gameLogic) {
    m_gameLogic = gameLogic;
}


/* Link the game application with player view, so that we can check game state. */
void PlayerView::setGameApplication(ChromaBlade* game) {
    m_game = game;
}


/* Handle user inputs */
void PlayerView::handleInput(float deltaTime) {
    // First check game state
    GameState state = m_game->getState();
    switch(state) {
        case GameState::Title:
            int rc;
            rc = m_title.update(*m_window);
            // Moved the cursor
            if (rc == 0) {}
            // Selected Play
            else if (rc == 1) m_game->setState(GameState::Game);
            // Selected Exit
            else m_window->close();
            break;
        case GameState::Game:
            sf::Event event;
            while(m_window->pollEvent(event)){
                // Close window
                if(event.type == sf::Event::Closed){
                    m_window->close();
                }
            }
            if (sf::Keyboard::isKeyPressed(LEFT)){
                MoveEvent *move = new MoveEvent(Direction::Left);
                m_game->queueEvent(move);
            }
            else if (sf::Keyboard::isKeyPressed(RIGHT)){
                MoveEvent *move = new MoveEvent(Direction::Right);
                m_game->queueEvent(move);
            }
            if (sf::Keyboard::isKeyPressed(UP)){
                MoveEvent *move = new MoveEvent(Direction::Up);
                m_game->queueEvent(move);
            }
            else if (sf::Keyboard::isKeyPressed(DOWN)){
                MoveEvent *move = new MoveEvent(Direction::Down);
                m_game->queueEvent(move);
            }
          break;
    }
}



/* Render */
void PlayerView::draw() {
    m_window->clear();
    GameState state = m_game->getState();
    // Render the content depending on the game state
    switch(state) {
        case GameState::Title:
            m_title.draw(*m_window);
            break;
        case GameState::Game:
            m_window->draw(m_map);
            m_window->draw(m_overlay);
            m_window->draw(animatedSprite);
            break;
    }
    m_window->display();
}


/* Check if the window is open */
bool PlayerView::isOpen(){
	return m_window->isOpen();
}


/* Update view. */
void PlayerView::update(float &deltaTime){

}


/* Adds listeners to eventManager */
void PlayerView::registerListener() {
    // Create function for listener. Add to event manager.
    std::function<void(const EventInterface &event)> move = std::bind(&PlayerView::moveChar, this, std::placeholders::_1);
    const EventListener listener = EventListener(move, 4);
    m_game->registerListener(listener, EventType::moveEvent);
}


/* Used to build a listener for moveEvent */
void PlayerView::moveChar(const EventInterface& event) {
    const EventInterface *ptr = &event;
    const MoveEvent *moveEvent = dynamic_cast<const MoveEvent*>(ptr);
    Direction dir = moveEvent->getDirection();
    float deltaTime = moveEvent->getDeltaTime();
    bool noKeyPressed = true;
    sf::Vector2f moving;
    switch (dir){
    case Up:
//        m_character.move(0.f, -m_speed * deltaTime);
        currAnimation = &walkingUp;
        moving = sf::Vector2f(0.f, -m_speed * deltaTime);
        noKeyPressed = false;
        break;
    case Down:
//        m_character.move(0.f, m_speed * deltaTime);
        currAnimation = &walkingDown;
        moving = sf::Vector2f(0.f, m_speed * deltaTime);
        noKeyPressed = false;
        break;
    case Left:
//        m_character.move(-m_speed * deltaTime, 0.f);
        currAnimation = &walkingLeft;
        moving = sf::Vector2f(-m_speed * deltaTime, 0.f);
        noKeyPressed = false;
        break;
    case Right:
//        m_character.move(m_speed * deltaTime, 0.f);
        currAnimation = &walkingRight;
        moving = sf::Vector2f(m_speed * deltaTime, 0.f);
        noKeyPressed = false;
        break;
    }
    animatedSprite.play(*currAnimation);
    animatedSprite.move(moving);

    if (noKeyPressed) {
        animatedSprite.stop();
    }
    noKeyPressed = true;

    animatedSprite.update((sf::seconds(deltaTime)));
    std::cout << animatedSprite.getPosition().x << "\n";
    std::cout << animatedSprite.getPosition().y << "\n";
}
