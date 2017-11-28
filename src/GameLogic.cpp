#include "GameLogic.hpp"
#include "MoveEvent.hpp"
#include "LoadMapEvent.hpp"
#include "DoorEvent.hpp"
#include "AttackEvent.hpp"
#include "SpawnEvent.hpp"
#include "ChromaBlade.hpp"
#include "PlayerView.hpp"

#include <iostream>


GameLogic::GameLogic() : Process() {
}


void GameLogic::init(){
	m_level = red;
    m_levelToggled = false;
    setState(Process::RUNNING);
}


void GameLogic::update(float &deltaTime){
}


/* Returns the current level */
GameLogic::Level GameLogic::getLevel(){
	return m_level;
}


/* Links game logic to game application */
void GameLogic::setGameApplication(ChromaBlade* game) {
    m_game = game;
}


void GameLogic::setCollisionMapping(std::vector<sf::RectangleShape> collVector, std::vector<sf::RectangleShape> doorVector){
	m_collisionVector = collVector;
	m_doors = doorVector;
}


/* Sets the position of character */
void GameLogic::setCharPosition(sf::Vector2f position) {
    m_player.setPosition(position);
    m_sprite->setPosition(position);
}


/* Links game logic to player view */
void GameLogic::setView(PlayerView* view) {
    m_view = view;
}

void GameLogic::setAnimatedSprite(AnimatedSprite* sprite){
	m_sprite = sprite;
}

void GameLogic::toggleLevel(){
	m_levelToggled = !m_levelToggled;
}


/* Adds listeners to eventManager */
void GameLogic::setListener() {

    // AttackEvent
    std::function<void(const EventInterface &event)> attack = std::bind(&GameLogic::attack, this, std::placeholders::_1);
    const EventListener attackListener = EventListener(attack, EventType::attackEvent);
    m_game->registerListener(attackListener, EventType::attackEvent);

    // SpawnEvent
    std::function<void(const EventInterface &event)> spawn = std::bind(&GameLogic::spawn, this, std::placeholders::_1);
    const EventListener spawnListener = EventListener(spawn, EventType::spawnEvent);
    m_game->registerListener(spawnListener, EventType::spawnEvent);

    // MoveEvent
    std::function<void(const EventInterface &event)> move = std::bind(&GameLogic::moveChar, this, std::placeholders::_1);
    const EventListener moveListener = EventListener(move, EventType::moveEvent);
    m_game->registerListener(moveListener, EventType::moveEvent);

		// DoorEvent
    std::function<void(const EventInterface &event)> door = std::bind(&GameLogic::useDoor, this, std::placeholders::_1);
    const EventListener doorListener = EventListener(door, EventType::doorEvent);
    m_game->registerListener(doorListener, EventType::doorEvent);

}

bool GameLogic::checkCollisions(const sf::FloatRect& fr) {
    /* Check intersections with mini collision tiles. */
    for(int i = 0; i < m_collisionVector.size(); i++){
        if (fr.intersects(m_collisionVector[i].getGlobalBounds())){
            std::cout << "COLLISION! \n";
            return true;
        }
    }
    
    /* Check intersections with rock tiles. */
    for (int i=0; i<m_rocks.size(); i++) {
        if (fr.intersects(m_rocks[i]->getGlobalBounds())) {
            std::cout << "ROCK COLLISION! \n";
            return true;
        }
    }
    return false;
}

bool GameLogic::checkDoors(sf::FloatRect fr, int extra) {
    /* Increase bounds if necessary. */
    fr.top -= TILE_DIM * extra;
    fr.left -= TILE_DIM * extra;
    fr.width += TILE_DIM * 2 * extra;
    fr.height += TILE_DIM * 2 * extra;

    /* Check intersections with mini door tiles. */
    for(int i = 0; i < m_doors.size(); i++){
        if (fr.intersects(m_doors[i].getGlobalBounds())) {
            return true;
        }
    }
    return false;
}

/***************************** Event Triggered Functions ******************************/

/* Used to build a listener for moveEvent */
void GameLogic::moveChar(const EventInterface& event) {
    const EventInterface *ptr = &event;
    const MoveEvent *moveEvent = dynamic_cast<const MoveEvent*>(ptr);
    Direction dir = moveEvent->getDirection();
    float speed = moveEvent->getSpeed();
    float deltaTime = moveEvent->getDeltaTime();
    sf::Vector2f pos = m_player.getPosition();
    sf::Vector2f prev = m_player.getPosition();
    bool noKeyPressed = true;
    sf::Vector2f moving;

    switch (dir){
        case Up:
            pos.y = pos.y + speed * deltaTime;
            moving = sf::Vector2f(0.f, speed * deltaTime);
            noKeyPressed = false;
            break;
        case Down:
            pos.y = pos.y + speed * deltaTime;
            moving = sf::Vector2f(0.f, speed * deltaTime);
            noKeyPressed = false;
            break;
        case Left:
            pos.x = pos.x + speed * deltaTime;
            moving = sf::Vector2f(speed * deltaTime, 0.f);
            noKeyPressed = false;
            break;
        case Right:
            pos.x = pos.x + speed * deltaTime;
            moving = sf::Vector2f(speed * deltaTime, 0.f);
            noKeyPressed = false;
            break;
    }
    setCharPosition(pos);
    m_view->drawAnimation(dir, moving, noKeyPressed, deltaTime);

    /* Check collisions. */
    if(checkCollisions(m_sprite->getGlobalBounds())){
        setCharPosition(prev);
    }

    /* Check doors. */
    bool doorDetected = checkDoors(m_sprite->getGlobalBounds(), 0);
    if (doorDetected && !m_onDoor) {
        std::cout << "onDoor\n";
        m_onDoor = true;

        DoorEvent *doorEvent = new DoorEvent(GameState::RedLevel, 1, dir);
        m_game->queueEvent(doorEvent);
    } else if (!doorDetected && m_onDoor) {
        std::cout << "not onDoor\n";
        m_onDoor = false;
    }
    if(m_game->inDebugMode()){
        std::cout <<"Player Position (sprite then logic): \n " ;
        pos = m_player.getPosition();
        std::cout << m_sprite->getPosition().x << "," << m_sprite->getPosition().y << "\n";
        std::cout << pos.x << "," << pos.y << "\n";
    }
}

/* Triggered by a DoorEvent. */
void GameLogic::useDoor(const EventInterface& event) {
    fprintf(stderr, "useDoor!\n");

    const EventInterface *ptr = &event;
    const DoorEvent *doorEvent = dynamic_cast<const DoorEvent*>(ptr);
    GameState curState = m_game->getState();
    const GameState newState = doorEvent->getGameState();
    const int room = doorEvent->getRoom();
    const Direction dir = doorEvent->getDirection();
    if (newState != curState) {
        fprintf(stderr, "door leads to %d\n", newState);
        ChangeStateEvent* change = new ChangeStateEvent(newState);
        LoadMapEvent* loadMapEvent = new LoadMapEvent(newState);
        m_game->queueEvent(change);
        m_game->queueEvent(loadMapEvent);
        m_view->resetCamera();
        if (newState == GameState::Hub) {
            setCharPosition(HUB_POS);
        } else if (newState == GameState::RedLevel) {
            m_view->updateCamera(RED_CAM);
            setCharPosition(RED_POS);
        } else {
        }
    }

    if(m_levelToggled){
        sf::Vector2f pos = m_player.getPosition();
        sf::Vector2f new_pos;
    if (dir == Direction::Left) {
        new_pos.x = ((int) m_player.getPosition().x / (int) WIDTH) * WIDTH - 2 * TILE_DIM;
        new_pos.y = m_player.getPosition().y;
        m_view->updateCamera(-WIDTH,0);
    }
    else if (dir == Direction::Right){
        new_pos.x = ((int) m_player.getPosition().x / (int) WIDTH + 1) * WIDTH + TILE_DIM;
        new_pos.y = m_player.getPosition().y;
        m_view->updateCamera(WIDTH,0);
    }
    else if (dir == Direction::Up){
        new_pos.x = m_player.getPosition().x;
        new_pos.y = ((int) m_player.getPosition().y / (int) HEIGHT) * HEIGHT - 2 * TILE_DIM;
        m_view->updateCamera(0,-HEIGHT);
    }
    else if (dir == Direction::Down){
        new_pos.x = m_player.getPosition().x;
        new_pos.y = ((int) m_player.getPosition().y / (int) HEIGHT + 1) * HEIGHT + TILE_DIM;
      m_view->updateCamera(0,HEIGHT);
    }

    if (new_pos.x < 0 || new_pos.y < 0) {
        DoorEvent *doorEvent = new DoorEvent(GameState::Hub, 0, dir);
        m_game->queueEvent(doorEvent);
        toggleLevel();
    } else {
        setCharPosition(new_pos);
        m_onDoor = false;
    }
    }

    if (room > 0) {
        if (std::find(m_clearedRooms.begin(), m_clearedRooms.end(), room)
                == m_clearedRooms.end()) {
            sf::Vector2f center = m_view->getCameraCenter();
            sf::Vector2f size = m_view->getCameraSize();
            SpawnEvent *spawnEvent = new SpawnEvent(Actor::Rock, 10, size, center);
            m_game->queueEvent(spawnEvent);
        }
    }

}


void GameLogic::attack(const EventInterface& event) {
    const EventInterface *ptr = &event;
    const AttackEvent *attackEvent = dynamic_cast<const AttackEvent*>(ptr);
    if (attackEvent->isFromPlayer() == true) { // player attack
        playerAttack();
    }
    else { // enemy attack
        enemyAttack();
    }
}


void GameLogic::playerAttack() {
    std::vector<DynamicActor>::iterator it;  // declare an iterator to a vector of DynamicActor

    // TODO: iterates over the enemies and attack the ones that are close enough
//    for(it = m_enemies.begin(); it != m_enemies.end(); it++) {
//        if (true) { // if the enemy is close enough
//            m_player.attack(*it);
//        }
//        std::cout << "one enemy attacked";
//    }
//    std::cout << "finish attack";
}


void GameLogic::enemyAttack() {

}


void GameLogic::spawn(const EventInterface& event) {
    printf("spawn!\n");
    const EventInterface *ptr = &event;
    const SpawnEvent *spawnEvent = dynamic_cast<const SpawnEvent*>(ptr);
    const Actor::Type actorType = spawnEvent->getActorType();
    const int count = spawnEvent->getCount();
    const sf::Vector2f size = spawnEvent->getSize();
    const sf::Vector2f center = spawnEvent->getCenter();


    int l = center.x - size.x / 2;
    int t = center.y - size.y / 2;

    sf::FloatRect tile;
    int rx, ry, x, y;

    for (int i=0; i<count; i++) {
        /* while not on wall or near door... */
        do {
            rx = rand() % (WIDTH  / TILE_DIM);
            ry = rand() % (HEIGHT / TILE_DIM);

            x = rx * TILE_DIM + l;
            y = ry * TILE_DIM + t;

            tile.left = x; tile.top = y;
            tile.width = tile.height = TILE_DIM;
        } while (checkCollisions(tile) || checkDoors(tile, 3));

        /* have a valid spawn location. */
        Actor *actor = new Actor(actorType, sf::Vector2f(TILE_DIM,TILE_DIM), 
                                            sf::Vector2f(x,y));
        m_rocks.push_back(actor);
    }
}

std::vector<Actor*> GameLogic::getRocks() {
    return m_rocks;
}

void GameLogic::clearRocks() {
    m_rocks.clear();
}
