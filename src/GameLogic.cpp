#include "GameLogic.hpp"
#include "MoveEvent.hpp"
#include "LoadMapEvent.hpp"
#include "DoorEvent.hpp"
#include "AttackEvent.hpp"
#include "SpawnEvent.hpp"
#include "SwitchColorEvent.hpp"
#include "ChromaBlade.hpp"
#include "PlayerView.hpp"
#include "AIView.hpp"
#include "Mob.hpp"
#include "MoveMobsEvent.hpp"
#include "SpawnPositionsEvent.hpp"

#include <iostream>


GameLogic::GameLogic() : Process() {
}


void GameLogic::init(){
    m_level = red;
    m_levelToggled = false;
    setState(Process::RUNNING);

    /* Temporary Hard-coding values of portals */
    sf::RectangleShape bluePortal(sf::Vector2f(32,32));
    bluePortal.setPosition(384,32);
    m_portals.push_back(bluePortal);
}


void GameLogic::update(float &deltaTime){
    GameState state = m_game->getState();

    if (state != GameState::Hub) {
        moveMobs();
    }
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

    // SwitchColorEvent
    std::function<void(const EventInterface &event)> switchCol = std::bind(&GameLogic::switchColor, this, std::placeholders::_1);
    const EventListener switchListener = EventListener(switchCol, EventType::switchColorEvent);
    m_game->registerListener(switchListener, EventType::switchColorEvent);

    // SpawnPositionsEvent
    std::function<void(const EventInterface &event)> setSpawnPositions
        = std::bind(&GameLogic::setSpawnPositions, this, std::placeholders::_1);
    const EventListener spawnPositionsListener
        = EventListener(setSpawnPositions, EventType::spawnPositionsEvent);
    m_game->registerListener(spawnPositionsListener, EventType::spawnPositionsEvent);
}


/* Check collision with tiles, rocks and mobs */
bool GameLogic::checkCollisions(const sf::FloatRect& fr) {
    /* Check intersections with mini collision tiles. */
    for(int i = 0; i < m_collisionVector.size(); i++){
        if (fr.intersects(m_collisionVector[i].getGlobalBounds())){
            //std::cout << "COLLISION! \n";
            return true;
        }
    }

    /* Check intersections with rock tiles. */
    for (int i = 0; i < m_rocks.size(); i++) {
        if (fr.intersects(m_rocks[i]->getGlobalBounds())) {
            //std::cout << "ROCK COLLISION! \n";
            return true;
        }
    }
    
    /* Check intersections with mobs. */
    for (int i = 0; i < m_mobs.size(); i++) {
        if (fr.intersects(m_mobs[i]->getGlobalBounds())) {
            //std::cout << "MOB COLLISION! \n";
            return true;
        }
    }
    return false;
}


/* Checks intersection with doors */
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


/* Checks collision with portal */
bool GameLogic::checkPortals(const sf::FloatRect& fr){
    for (int i=0; i<m_portals.size(); i++) {
	    if (fr.intersects(m_portals[i].getGlobalBounds())) {
	        //std::cout << "PORTAL COLLISION \n";
	        return true;
	    }
    }
}


/* Returns rock vector */
std::vector<Actor*> GameLogic::getRocks() {
    return m_rocks;
}


/* Returns mob vector */
std::vector<DynamicActor*> GameLogic::getMobs() {
    return m_mobs;
}


void GameLogic::clearRocks() {
    m_rocks.clear();
}


/* Called after a player-initiated attackEvent */
void GameLogic::playerAttack(Direction dir) {
    sf::FloatRect fr = m_sprite->getGlobalBounds();
    // Change the size and position of the rectangle depending on the attack direction, attack range is 20px
    switch (dir) {
        case Up:
            fr.height += 20;
            fr.top -= 20;
            break;
        case Down:
            fr.height += 20;
            break;
        case Left:
            fr.width += 20;
            fr.left -= 20;
            break;
        case Right:
            fr.width += 20;
            break;
    }

    /* Check attack's intersection with mobs. */
    for (int i = 0; i < m_mobs.size(); i++) {
        if (fr.intersects(m_mobs[i]->getGlobalBounds())) {
            m_mobs[i]->setHealth(m_mobs[i]->getHealth() - m_player.getDamage());
        }
    }
}


void GameLogic::enemyAttack() {

}

void GameLogic::moveMobs() {
//    MoveMobsEvent* moveMobsEvent = new MoveMobsEvent(m_player.getPosition());
//    m_game->queueEvent(moveMobsEvent);
}

/***************************** Event Triggered Functions ******************************/

/* Triggered by a moveEvent */
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
    }
    else if (!doorDetected && m_onDoor) {
        std::cout << "not onDoor\n";
        m_onDoor = false;
    }

    if(m_game->getState() == GameState::Hub){
        bool portalDetected = checkPortals(m_sprite->getGlobalBounds());
    }

    // Debug stuff
    if(m_game->inDebugMode()){
			//todo: consider changing to drawing text on screen...
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
        ChangeStateEvent* changeState = new ChangeStateEvent(newState);
        LoadMapEvent* loadMapEvent = new LoadMapEvent(newState);
        m_game->queueEvent(changeState);
        m_game->queueEvent(loadMapEvent);
        m_view->resetCamera();
        if (newState == GameState::Hub) {
            setCharPosition(HUB_POS);
            m_view->updateCamera(HUB_CAM);
        }
        else if (newState == GameState::RedLevel) {
            m_view->updateCamera(RED_CAM);
            setCharPosition(RED_POS);
        }
        else {
        }
    }

    if(m_levelToggled){
        sf::Vector2f pos = m_player.getPosition();
        sf::Vector2f new_pos;
        if (dir == Direction::Left) {
            new_pos.x = ((int) pos.x / (int) WIDTH) * WIDTH - 2 * TILE_DIM;
            new_pos.y = pos.y;
            m_view->updateCamera(-WIDTH,0);
        }
        else if (dir == Direction::Right){
            new_pos.x = ((int) pos.x / (int) WIDTH + 1) * WIDTH + TILE_DIM;
            new_pos.y = pos.y;
            m_view->updateCamera(WIDTH,0);
        }
        else if (dir == Direction::Up){
            new_pos.x = pos.x;
            new_pos.y = ((int) pos.y / (int) HEIGHT) * HEIGHT - 2 * TILE_DIM;
            m_view->updateCamera(0,-HEIGHT);
        }
        else if (dir == Direction::Down){
            new_pos.x = pos.x;
            new_pos.y = ((int) pos.y / (int) HEIGHT + 1) * HEIGHT + TILE_DIM;
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
        if (std::find(m_clearedRooms.begin(), m_clearedRooms.end(), room) == m_clearedRooms.end()) {
            sf::Vector2f center = m_view->getCameraCenter();
            sf::Vector2f size = m_view->getCameraSize();
            SpawnEvent *spawnRocksEvent = new SpawnEvent(Actor::Rock, 10, size, center);
            m_game->queueEvent(spawnRocksEvent);
            SpawnEvent *spawnMobsEvent = new SpawnEvent(Actor::Mob, 10, size, center);
            m_game->queueEvent(spawnMobsEvent);
            SpawnPositionsEvent *spawnPositionsEvent
                = new SpawnPositionsEvent(m_rocks, m_mobs);
            m_game->queueEvent(spawnPositionsEvent);    
        }
    }
}


/* Triggered by an attackEvent */
void GameLogic::attack(const EventInterface& event) {
    const EventInterface *ptr = &event;
    const AttackEvent *attackEvent = dynamic_cast<const AttackEvent*>(ptr);
    Direction dir = attackEvent->getDirection();
    if (attackEvent->isFromPlayer() == true) { // player attack
        playerAttack(dir);
    }
    else { // enemy attack
        enemyAttack();
    }
}


/* Triggered by a spawnEvent */
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
        if (actorType == Actor::Rock) { 
            Actor *actor = new Actor(actorType, sf::Vector2f(TILE_DIM,TILE_DIM), 
                                                sf::Vector2f(x,y));
            m_rocks.push_back(actor);
        } else if (actorType == Actor::Mob) {
            DynamicActor *actor = new Mob(Purple, 100, 20, sf::Vector2f(x,y), 200.f);
            m_mobs.push_back(actor);

            AIView *aiview = new AIView(actor);
            m_aiviews.push_back(aiview);
        }
    }
}

/* Triggered by a SpawnPositionsEvent. */
void GameLogic::setSpawnPositions(const EventInterface& event) {
    const SpawnPositionsEvent *spawnPositionsEvent
        = dynamic_cast<const SpawnPositionsEvent*>(&event);
    std::vector<Actor*> rocks = spawnPositionsEvent->getRocks();
    std::vector<DynamicActor*> mobs = spawnPositionsEvent->getMobs();

    for (int i=0; i<m_aiviews.size(); i++) {
        m_aiviews[i]->setSpawnPositions(rocks, mobs);
    }
}

/* Triggered by a SwitchColorEvent */
void GameLogic::switchColor(const EventInterface& event) {
    printf("switch color!\n");
    const EventInterface *ptr = &event;
    const SwitchColorEvent *switchColorEvent = dynamic_cast<const SwitchColorEvent*>(ptr);
    sf::Color color = switchColorEvent->getColor();
    m_player.changeSwordColor(color);
}

