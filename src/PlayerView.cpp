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

#define START_POS sf::Vector2f(196, 255)
#define SPEED 200.f

PlayerView::PlayerView() : Process() {
}

/* Initialize player view by loading files and setting initial positions */
void PlayerView::init(){

    // Load title screen.
    m_title.init();

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
      animatedSprite.setScale(0.9f,0.9f);
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
//                m_game->setState(GameState::Hub);
                ChangeStateEvent* change = new ChangeStateEvent(GameState::Hub);
                LoadMapEvent* loadMapEvent = new LoadMapEvent(GameState::Hub);
                m_game->queueEvent(change);
                m_game->queueEvent(loadMapEvent);
            }
            // Selected Exit
            else m_window->close();
            break;
        default:
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
  m_camera.setCenter(newX, newY);
  m_window->setView(m_camera);
}


/* Render */
void PlayerView::draw() {
    m_window->clear();
    GameState state = m_game->getState();
    Actor rock(Actor::Rock, sf::Vector2f(32,32), sf::Vector2f(100,100));

    // Render the content depending on the game state
    switch(state) {
        case GameState::Title:
            m_title.draw(*m_window);
            break;
        default:{
            m_window->draw(m_map);
            m_window->draw(m_overlay);
            m_window->draw(m_filter);
            m_window->draw(animatedSprite);
            /* Some nice debug stuff */
            sf::RectangleShape debugRectangle(sf::Vector2f(boundaryBox.width, boundaryBox.height));
            debugRectangle.setFillColor(sf::Color(250, 150, 100, 100));
            debugRectangle.setPosition(animatedSprite.getPosition().x, animatedSprite.getPosition().y);
            m_window->draw(debugRectangle);
            m_collisions.drawBoxes(m_window);
            m_doors.drawBoxes(m_window);
          break;
        }

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
    const EventListener listener = EventListener(move, EventType::moveEvent);
    m_game->registerListener(listener, EventType::moveEvent);

    // DoorEvent
    std::function<void(const EventInterface &event)> door = std::bind(&PlayerView::useDoor, this, std::placeholders::_1);
    const EventListener doorListener = EventListener(door, EventType::doorEvent);
    m_game->registerListener(doorListener, EventType::doorEvent);

    // LoadMapEvent
    std::function<void(const EventInterface &event)> loadMap = std::bind(&PlayerView::loadMap, this, std::placeholders::_1);
    const EventListener loadMapListener = EventListener(loadMap, EventType::loadMapEvent);
    m_game->registerListener(loadMapListener, EventType::loadMapEvent);
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
    for(int i = 0; i < m_collisions.m_boxes.size(); i++){
      if (animatedSprite.getGlobalBounds().intersects(m_collisions.m_boxes[i].getGlobalBounds())){
        //std::cout << "COLLISION! \n";
        collisionDetected = true;
        break;
      }
    }
    if(collisionDetected){
      animatedSprite.setPosition(prevX, prevY);
      m_gameLogic->setCharPosition(std::make_tuple(prevX, prevY));
    }
    bool doorDetected = false;
    for(int i = 0; i < m_doors.m_boxes.size(); i++){
      if (animatedSprite.getGlobalBounds().intersects(m_doors.m_boxes[i].getGlobalBounds())){
        doorDetected = true;
        break;
      }
    }
    if (doorDetected && !m_onDoor) {
        std::cout << "onDoor\n";
        m_onDoor = true;

        DoorEvent *doorEvent = new DoorEvent(GameState::RedLevel, 1, dir);
        m_game->queueEvent(doorEvent);
    } else if (!doorDetected && m_onDoor) {
        std::cout << "not onDoor\n";
        m_onDoor = false;
    }
    boundaryBox = animatedSprite.getGlobalBounds();
    animatedSprite.update((sf::seconds(deltaTime)));
    //std::cout << animatedSprite.getPosition().x << "\n";
    //std::cout << animatedSprite.getPosition().y << "\n";
}

void PlayerView::clearTileMaps() {
    fprintf(stderr, "clearTileMaps!\n");
    m_map.clear();
    m_overlay.clear();
    m_collisions.clear();
    m_doors.clear();
}

/* Triggered by a LoadMapEvent. */
void PlayerView::loadMap(const EventInterface& event) {
    fprintf(stderr, "loadMap!\n");
    const EventInterface *ptr = &event;
    const LoadMapEvent *loadMapEvent = dynamic_cast<const LoadMapEvent*>(ptr);
    const GameState state = loadMapEvent->getGameState();

    clearTileMaps();

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
        break;
        case GameState::RedLevel:

            fprintf(stderr, "loading RedLevel!\n");
            levelToggled = true;
            animatedSprite.setPosition(32,1520);
            updateCamera(400,1520);
            m_map.loadFromText("../res/tilesets/dungeon.png",
                    "../res/level/DemoDungeon/dungeon_base.csv",
                    sf::Vector2u(16, 16), 100, 114);
            // m_overlay.loadFromText("../res/tilesets/dungeon.png",
            //         "../res/level/DemoDungeon/dungeon_overlay.csv",
            //         sf::Vector2u(16, 16), 100, 114);
            m_collisions.loadCollisionsFromText("../res/tilesets/dungeon.png",
                    "../res/level/DemoDungeon/dungeon_collision.csv",
                    sf::Vector2u(16, 16), 100, 114);
            m_doors.loadDoorsFromText("../res/tilesets/dungeon.png",
                    "../res/level/DemoDungeon/dungeon_doors.csv",
                    sf::Vector2u(16, 16), 100, 114);
        break;
    }
}

/* Triggered by a DoorEvent. */
void PlayerView::useDoor(const EventInterface& event) {
    fprintf(stderr, "useDoor!\n");

    const EventInterface *ptr = &event;
    const DoorEvent *doorEvent = dynamic_cast<const DoorEvent*>(ptr);
    GameState curState = m_game->getState();
    const GameState newState = doorEvent->getGameState();
    const int room = doorEvent->getRoom();
    const Direction dir = doorEvent->getDirection();
    bool dontChangeCamera = false;
    if (newState != curState) {
        fprintf(stderr, "door leads to %d\n", newState);
        ChangeStateEvent* change = new ChangeStateEvent(newState);
        LoadMapEvent* loadMapEvent = new LoadMapEvent(newState);
        m_game->queueEvent(change);
        m_game->queueEvent(loadMapEvent);
    }

    if(levelToggled){
    if (room > 0) {
        if (std::find(m_clearedRooms.begin(), m_clearedRooms.end(), room)
                == m_clearedRooms.end()) {
            sf::Vector2f center = m_window->getView().getCenter();
            sf::Vector2f size = m_window->getView().getSize();
            SpawnEvent *spawnEvent = new SpawnEvent(Actor::Rock, 1, size, center);
            m_game->queueEvent(spawnEvent);
        }
    }

    if (dir == Direction::Left) {
        animatedSprite.setPosition(prevX - 100, prevY);
        updateCamera(m_camera.getCenter().x - 800, m_camera.getCenter().y);
    }
    else if (dir == Direction::Right){
        animatedSprite.setPosition(prevX + 100, prevY);
        updateCamera(m_camera.getCenter().x + 800, m_camera.getCenter().y);
    }
    else if (dir == Direction::Up){
        animatedSprite.setPosition(prevX, prevY - 100);
        updateCamera(m_camera.getCenter().x, m_camera.getCenter().y - 608);

    }
    else if (dir == Direction::Down){
      animatedSprite.setPosition(prevX, prevY + 100);
      updateCamera(m_camera.getCenter().x, m_camera.getCenter().y + 608);
    }
  }
}
