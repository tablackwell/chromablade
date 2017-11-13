#include "PlayerView.hpp"
#include "GameState.hpp"
#include "ChromaBlade.hpp"
#include "KeySetting.hpp"
#include "MoveEvent.hpp"
#include "StaticActor.hpp"
#include "DoorEvent.hpp"
#include "AttackEvent.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <cstdio>
#include <tuple>
#include <iostream>

#define START_POS sf::Vector2f(196, 255)
#define SPEED 200.f

PlayerView::PlayerView() : Process() {
}

/* Initialize player view by loading files and setting initial positions */
void PlayerView::init(){

    // Load title screen.
    m_title.init();

    // Load map and overlay of sample room
    m_map.loadFromText("../res/tilesets/lightworld.png","../res/level/TestLevel/test_base.csv", sf::Vector2u(16, 16), 100, 38);
    m_overlay.loadFromText("../res/tilesets/lightworld.png","../res/level/TestLevel/test_overlay.csv", sf::Vector2u(16, 16),100, 38);
    m_collisions.loadCollisionsFromText("../res/tilesets/lightworld.png","../res/level/TestLevel/test_collisions.csv", sf::Vector2u(16, 16), 100, 38);

    // Load texture for character
    if(!m_charTexture.loadFromFile("../res/spritenew.png")) {
        // ERROR
    }
    m_buffer.loadFromFile("../res/swordSwing.wav");
    m_sound.setBuffer(m_buffer);
//    m_character.setTextureRect(sf::IntRect(32, 0, 32, 32));

    walkingDown.setSpriteSheet(m_charTexture);
    walkingDown.addFrame(sf::IntRect(0, 0, 32, 32));
    walkingDown.addFrame(sf::IntRect(0, 32, 32, 32));
    walkingDown.addFrame(sf::IntRect(0, 64, 32, 32));
    walkingDown.addFrame(sf::IntRect(0, 96, 32, 32));

    walkingLeft.setSpriteSheet(m_charTexture);
    walkingLeft.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    walkingLeft.addFrame(sf::IntRect(32, 64, 32, 32));
    walkingLeft.addFrame(sf::IntRect(32, 96, 32, 32));

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
//  m_character.setPosition(START_POS);
      animatedSprite.setScale(1.0f,1.0f);
    setState(Process::RUNNING);
    camera.setSize(800,600);
    m_speed = SPEED;
}


/* Set the window of the view */
void PlayerView::setContext(sf::RenderWindow* window){
    m_window = window;
  sf::View camera = window->getDefaultView();
  window->setView(camera);
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
            else if (rc == 1) {
//                m_game->setState(GameState::Game);
                ChangeStateEvent* change = new ChangeStateEvent(GameState::Game);
                m_game->queueEvent(change);
            }
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
                else if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == ATTACK) {
                        AttackEvent *attack = new AttackEvent();
                        m_game->queueEvent(attack);
                        std::cout << "attack event \n";
                        m_sound.play();
                    }
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

void PlayerView::updateCamera(int newX, int newY){
  camera.setCenter(newX, newY);
  m_window->setView(camera);
}


/* Render */
void PlayerView::draw() {
    m_window->clear();
    GameState state = m_game->getState();
    StaticActor rock(StaticActor::Rock, sf::Vector2f(32,32), sf::Vector2f(100,100));

    // Render the content depending on the game state
    switch(state) {
        case GameState::Title:
            m_title.draw(*m_window);
            break;
        case GameState::Game:
            m_window->draw(m_map);
            m_window->draw(m_overlay);
            m_window->draw(animatedSprite);
            /* Some nice debug stuff */
            // sf::RectangleShape debugRectangle(sf::Vector2f(boundaryBox.width, boundaryBox.height));
            // debugRectangle.setFillColor(sf::Color(250, 150, 100, 100));
            // debugRectangle.setPosition(animatedSprite.getPosition().x, animatedSprite.getPosition().y);
            // m_window->draw(debugRectangle);
            // m_collisions.drawBoxes(m_window);
            break;
    }
    rock.draw(*m_window);
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
void PlayerView::setListener() {
    // Create function for listener. Add to event manager.
    std::function<void(const EventInterface &event)> move = std::bind(&PlayerView::moveChar, this, std::placeholders::_1);
    const EventListener listener = EventListener(move, 2);
    m_game->registerListener(listener, EventType::moveEvent);

    // DoorEvent
    std::function<void(const EventInterface &event)> door = std::bind(&PlayerView::useDoor, this, std::placeholders::_1);
    const EventListener doorListener = EventListener(door, 4);
    m_game->registerListener(doorListener, EventType::doorEvent);
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
    prevX = animatedSprite.getPosition().x;
    prevY = animatedSprite.getPosition().y;
    animatedSprite.move(moving);

    if (noKeyPressed) {
        animatedSprite.stop();
    }
    noKeyPressed = true;
    bool collisionDetected = false;
    for(int i = 0; i < m_collisions.m_collisionRects.size(); i++){
      if (animatedSprite.getGlobalBounds().intersects(m_collisions.m_collisionRects[i].getGlobalBounds())){
        std::cout << "COLLISION! \n";
        collisionDetected = true;
        break;
      }
    }
    if(collisionDetected){
      animatedSprite.setPosition(prevX, prevY);
      m_gameLogic->setCharPosition(std::make_tuple(prevX, prevY));
    }
    boundaryBox = animatedSprite.getGlobalBounds();
    animatedSprite.update((sf::seconds(deltaTime)));
    std::cout << animatedSprite.getPosition().x << "\n";
    std::cout << animatedSprite.getPosition().y << "\n";
}

/* Triggered by a DoorEvent. */
void PlayerView::useDoor(const EventInterface& event) {
    const EventInterface *ptr = &event;
    const DoorEvent *doorEvent = dynamic_cast<const DoorEvent*>(ptr);

    fprintf(stderr, "useDoor!\n");
}
