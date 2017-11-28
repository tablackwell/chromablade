#include "PlayerView.hpp"
#include "GameState.hpp"
#include "ChromaBlade.hpp"
#include "KeySetting.hpp"
#include "Actor.hpp"

#include "MoveEvent.hpp"
#include "DoorEvent.hpp"
#include "AttackEvent.hpp"
#include "SpawnEvent.hpp"
#include "LoadMapEvent.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <cstdio>
#include <tuple>
#include <iostream>
#include <math.h>

#define START_POS sf::Vector2f(196, 255)
#define SPEED 200.f

PlayerView::PlayerView() : Process() {
}


/* Initialize player view by loading files and setting initial positions */
void PlayerView::init(){

    // Load title screen.
    m_title.init();

    // Load texture for character
    if(!m_charTexture.loadFromFile("../res/sprite/spritenew.png")) {
        // ERROR
    }

    // Load sound for sword swing
    m_buffer.loadFromFile("../res/sfx/swordSwing.wav");
    m_sound.setBuffer(m_buffer);

    // Load animations
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
    animatedSprite.setScale(0.9f,0.9f);
    animatedSprite.play(*currAnimation);
    setState(Process::RUNNING);
    m_camera.setSize(WIDTH,HEIGHT);
    m_speed = SPEED;
    m_filter.setSize(sf::Vector2f(WIDTH,HEIGHT));
}


/* Set the window of the view */
void PlayerView::setContext(sf::RenderWindow* window){
  m_window = window;
  sf::View view = window->getDefaultView();
  window->setView(view);
}


/* Link the game logic with player view */
void PlayerView::setGameLogic(GameLogic* gameLogic) {
    m_gameLogic = gameLogic;
    gameLogic->setAnimatedSprite(&animatedSprite);
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
            if (rc == 0) {} // Moved the cursor
            else if (rc == 1) { // Selected Play
                ChangeStateEvent* changeState = new ChangeStateEvent(GameState::Hub);
                LoadMapEvent* loadMap = new LoadMapEvent(GameState::Hub);
                m_game->queueEvent(changeState);
                m_game->queueEvent(loadMap);
            }
            else m_window->close(); // Selected Exit
            break;
        default: // in the game
            sf::Event event;
            while(m_window->pollEvent(event)){
                // Close window
                if(event.type == sf::Event::Closed){
                    m_window->close();
                }
                else if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == ATTACK) {
                        AttackEvent *attack = new AttackEvent(true);
                        m_game->queueEvent(attack);
                        m_sound.play();
                    }
                    if (event.key.code == RED) {
                        // TODO: switchSwordEvent
                    }
                    if (event.key.code == BLUE) {
                        // TODO: switchSwordEvent
                    }
                    if (event.key.code == YELLOW) {
                        // TODO: switchSwordEvent
                    }
                }
            }
            sf::Vector2f v;
            Direction dir;

            if (sf::Keyboard::isKeyPressed(LEFT)){
                v.x -= SPEED;
//                dir = Direction::Left;
//                MoveEvent *move = new MoveEvent(Direction::Left);
//                m_game->queueEvent(move);
            }
            else if (sf::Keyboard::isKeyPressed(RIGHT)){
                v.x += SPEED;
//                dir = Direction::Right;
//                MoveEvent *move = new MoveEvent(Direction::Right);
//                m_game->queueEvent(move);
            }
            if (sf::Keyboard::isKeyPressed(UP)){
                v.y -= SPEED;
//                dir = Direction::Up;
//                MoveEvent *move = new MoveEvent(Direction::Up);
//                m_game->queueEvent(move);
            }
            else if (sf::Keyboard::isKeyPressed(DOWN)){
                v.y += SPEED;
//                dir = Direction::Down;
//                MoveEvent *move = new MoveEvent(Direction::Down);
//                m_game->queueEvent(move);
            }
            if (v.x != 0.f && v.y != 0.f) {
                v.x /= sqrt(2.f);
                v.y /= sqrt(2.f);
            }
            if (v.x > 0) {
                MoveEvent *move = new MoveEvent(Direction::Right, v.x);
                m_game->queueEvent(move);
            }
            else if (v.x < 0) {
                MoveEvent *move = new MoveEvent(Direction::Left, v.x);
                m_game->queueEvent(move);
            }
            if (v.y > 0) {
                MoveEvent *move = new MoveEvent(Direction::Down, v.y);
                m_game->queueEvent(move);
            }
            else if (v.y < 0) {
                MoveEvent *move = new MoveEvent(Direction::Up, v.y);
                m_game->queueEvent(move);
            }
            break;
    }
}


/* Camera Functions */
void PlayerView::updateCamera(int newX, int newY){
  m_camera.setCenter(m_camera.getCenter().x + newX, m_camera.getCenter().y + newY);
  m_window->setView(m_camera);
}

void PlayerView::resetCamera(){
  m_camera.setCenter(0,0);
  m_window->setView(m_camera);
}

sf::Vector2f PlayerView::getCameraCenter(){
  return m_camera.getCenter();
}

sf::Vector2f PlayerView::getCameraSize(){
  return m_camera.getSize();
}


/* Render */
void PlayerView::draw() {
    m_window->clear();
    GameState state = m_game->getState();
    std::vector<Actor*> rocks = m_gameLogic->getRocks();

    // Render the content depending on the game state
    switch(state) {
        case GameState::Title:
            m_title.draw(*m_window);
            break;
        default:
            m_window->draw(m_map);
            m_window->draw(m_overlay);
            for (int i=0; i<rocks.size(); i++) {
                rocks[i]->draw(m_window);
            }
            // m_window->draw(m_filter);
            m_window->draw(animatedSprite);

            /* Debug stuff */
            if(m_game->inDebugMode()){
              sf::RectangleShape debugRectangle(sf::Vector2f(boundaryBox.width, boundaryBox.height));
              debugRectangle.setFillColor(sf::Color(250, 150, 100, 100));
              debugRectangle.setPosition(animatedSprite.getPosition().x, animatedSprite.getPosition().y);
              m_window->draw(debugRectangle);
              m_collisions.drawBoxes(m_window);
              m_doors.drawBoxes(m_window);
            }
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
void PlayerView::setListener() {
    // LoadMapEvent
    std::function<void(const EventInterface &event)> loadMap = std::bind(&PlayerView::loadMap, this, std::placeholders::_1);
    const EventListener loadMapListener = EventListener(loadMap, EventType::loadMapEvent);
    m_game->registerListener(loadMapListener, EventType::loadMapEvent);
}



void PlayerView::drawAnimation(Direction dir, sf::Vector2f moving , bool noKeyPressed, float deltaTime) {
    Animation *currAnimation;
    switch (dir) {
        case Up: {
            currAnimation = &walkingUp;
            break;
        }
        case Down: {
            currAnimation = &walkingDown;
            break;
        }
        case Right: {
            currAnimation = &walkingRight;
            break;
        }
        case Left: {
            currAnimation = &walkingLeft;
            break;
        }
    }
        animatedSprite.play(*currAnimation);
        animatedSprite.move(moving);

        if (noKeyPressed) {
            animatedSprite.stop();
        }
        noKeyPressed = true;
        animatedSprite.update(sf::seconds(deltaTime));
}


/* Used to build a listener for moveEvent */
//void PlayerView::moveChar(const EventInterface& event) {
//    const EventInterface *ptr = &event;
//    const MoveEvent *moveEvent = dynamic_cast<const MoveEvent*>(ptr);
//    Direction dir = moveEvent->getDirection();
//    float deltaTime = moveEvent->getDeltaTime();
//    bool noKeyPressed = true;
//    sf::Vector2f moving;
//    switch (dir){
//    case Up:
//        currAnimation = &walkingUp;
//        moving = sf::Vector2f(0.f, -m_speed * deltaTime);
//        noKeyPressed = false;
//        break;
//    case Down:
//        currAnimation = &walkingDown;
//        moving = sf::Vector2f(0.f, m_speed * deltaTime);
//        noKeyPressed = false;
//        break;
//    case Left:
//        currAnimation = &walkingLeft;
//        moving = sf::Vector2f(-m_speed * deltaTime, 0.f);
//        noKeyPressed = false;
//        break;
//    case Right:
//        currAnimation = &walkingRight;
//        moving = sf::Vector2f(m_speed * deltaTime, 0.f);
//        noKeyPressed = false;
//        break;
//    }
//    animatedSprite.play(*currAnimation);
//    animatedSprite.move(moving);
//
//    if (noKeyPressed) {
//        animatedSprite.stop();
//    }
//    noKeyPressed = true;
//    animatedSprite.update((sf::seconds(deltaTime)));
//}


void PlayerView::clearTileMaps() {
    fprintf(stderr, "clearTileMaps!\n");
    m_map.clear();
    m_overlay.clear();
    m_collisions.clear();
    m_doors.clear();
}


/* Load the map of a level. Triggered by a LoadMapEvent. */
void PlayerView::loadMap(const EventInterface& event) {
    fprintf(stderr, "loadMap!\n");
    const EventInterface *ptr = &event;
    const LoadMapEvent *loadMapEvent = dynamic_cast<const LoadMapEvent*>(ptr);
    const GameState state = loadMapEvent->getGameState();

    clearTileMaps();
    m_gameLogic->clearRocks();

    switch (state) {
        case GameState::Hub:
            m_map.loadFromText("../res/tilesets/lightworld.png",
                    "../res/level/TestLevel/test_base.csv",
                    sf::Vector2u(16, 16), 100, 38);
            m_overlay.loadFromText("../res/tilesets/lightworld.png",
                    "../res/level/TestLevel/test_overlay.csv",
                    sf::Vector2u(16, 16),100, 38);
            m_collisions.loadCollisionsFromText("../res/tilesets/lightworld.png",
                    "../res/level/TestLevel/test_collisions.csv",
                    sf::Vector2u(16, 16), 100, 38);
            m_doors.loadDoorsFromText("../res/tilesets/lightworld.png",
                    "../res/level/TestLevel/test_doors.csv",
                    sf::Vector2u(16, 16), 100, 38);
            m_filter.setFillColor(sf::Color(0,0,0,0));
            m_gameLogic->setCollisionMapping(m_collisions.m_boxes, m_doors.m_boxes);
            break;
        case GameState::RedLevel:
            fprintf(stderr, "loading RedLevel!\n");
            m_gameLogic->toggleLevel();
            m_map.loadFromText("../res/tilesets/dungeon.png",
                    "../res/level/RedDungeon/dungeon_base.csv",
                    sf::Vector2u(16, 16), 100, 114);
            m_overlay.loadFromText("../res/tilesets/dungeon.png", "../res/level/RedDungeon/dungeon_overlay.csv",
                    sf::Vector2u(16, 16), 100, 114);
            m_collisions.loadCollisionsFromText("../res/tilesets/dungeon.png",
                    "../res/level/RedDungeon/dungeon_collision.csv",
                    sf::Vector2u(16, 16), 100, 114);
            m_doors.loadDoorsFromText("../res/tilesets/dungeon.png",
                    "../res/level/RedDungeon/dungeon_doors.csv",
                    sf::Vector2u(16, 16), 100, 114);
            m_gameLogic->setCollisionMapping(m_collisions.m_boxes, m_doors.m_boxes);
        break;
        case GameState::BlueLevel:

            fprintf(stderr, "loadingBlueLevel!\n");
            m_gameLogic->toggleLevel();
            m_map.loadFromText("../res/tilesets/dungeon.png",
                    "../res/level/BlueDungeon/bluedungeon_base.csv",
                    sf::Vector2u(16, 16), 200, 76);
            m_overlay.loadFromText("../res/tilesets/dungeon.png", "../res/level/BlueDungeon/bluedungeon_overlay.csv", sf::Vector2u(16, 16),200, 76);
            m_collisions.loadCollisionsFromText("../res/tilesets/dungeon.png",
                    "../res/level/BlueDungeon/bluedungeon_collision.csv",
                    sf::Vector2u(16, 16), 200, 76);
            m_doors.loadDoorsFromText("../res/tilesets/dungeon.png",
                    "../res/level/DemoDungeon/bluedungeon_doors.csv",
                    sf::Vector2u(16, 16), 200, 76);
            m_gameLogic->setCollisionMapping(m_collisions.m_boxes, m_doors.m_boxes);
      break;
    }
}
