#include "GameLogic.hpp"
#include "ChromaBlade.hpp"
#include "PlayerView.hpp"
#include "AIView.hpp"
#include "BossScript.hpp"
#include "Mob.hpp"
#include "Greyscale.hpp"
#include "Macros.hpp"

#include "MoveEvent.hpp"
#include "LoadMapEvent.hpp"
#include "DoorEvent.hpp"
#include "AttackEvent.hpp"
#include "SpawnEvent.hpp"
#include "SwitchColorEvent.hpp"
#include "PathMapEvent.hpp"

#include <iostream>
#include <cmath>

GameLogic::GameLogic() : Process() {
}


void GameLogic::init(){
    m_levelToggled = false;
    setState(Process::RUNNING);

    /* Init portals */
    m_bluePortal.setSize((sf::Vector2f(32,32)));
    m_bluePortal.setPosition(384,32);
    m_redPortal.setSize(sf::Vector2f(32,32));
    m_redPortal.setPosition(1184,32);
    m_yellowPortal.setSize(sf::Vector2f(32,32));
    m_yellowPortal.setPosition(1984,32);
    m_greyPortal.setSize((sf::Vector2f(32,32)));
    m_greyPortal.setPosition(1184,880);
    m_bossTrigger.setSize((sf::Vector2f(32,32)));
    m_bossTrigger.setPosition(400,496);
    bossAvailable = false;

    /* Allocate memory for path maps. */
    m_numNodes.x = WIDTH / TILE_DIM;
    m_numNodes.y = HEIGHT / TILE_DIM;
    m_pathMap = new char* [m_numNodes.x];
    for (int i=0; i<m_numNodes.x; i++) {
        m_pathMap[i] = new char[m_numNodes.y];
    }
}


void GameLogic::update(float &deltaTime){
    GameState state = m_game->getState();

    if (state != GameState::Hub) {
        moveMobs(deltaTime);
    }

    if (state == GameState::BossLevel){
      updateGreyscale(deltaTime);
    }
}


/* Links game logic to game application */
void GameLogic::setGameApplication(ChromaBlade* game) {
    m_game = game;
}


/* Sets the internal collision mapping for game logic*/
void GameLogic::setCollisionMapping(std::vector<sf::RectangleShape> collVector, std::vector<sf::RectangleShape> doorVector){
	m_collisionVector = collVector;
	m_doors = doorVector;
}

void GameLogic::setBoundaries(int xBound, int yBound){
  m_xBound = xBound;
  m_yBound = yBound;
}


/* Sets the position of character */
void GameLogic::setCharPosition(sf::Vector2f position) {
    m_player.setPosition(position);
    m_sprite->setPosition(position);
}

/* Reset character stats after death */
void GameLogic::resetCharacter() {
    m_player.setHealth(100);
    setCharPosition(HUB_POS);
}

/* Links game logic to player view */
void GameLogic::setView(PlayerView* view) {
    m_view = view;
}

/* Provides a reference to the character's sprite in order to get a bounding box*/
void GameLogic::setAnimatedSprite(AnimatedSprite* sprite){
	m_sprite = sprite;
}

void GameLogic::toggleLevel(){
	m_levelToggled = !m_levelToggled;
}


/* Returns if a color is available */
bool GameLogic::hasColor(sf::Color col) {
    return m_player.hasColor(col);
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

    // PathMapEvent
    std::function<void(const EventInterface &event)> pathMap = std::bind(&GameLogic::pathMap, this, std::placeholders::_1);
    const EventListener pathMapListener = EventListener(pathMap, EventType::pathMapEvent);
    m_game->registerListener(pathMapListener, EventType::pathMapEvent);

}

/* Check collision with tiles, rocks and mobs */
bool GameLogic::checkCollisions(sf::FloatRect fr, int extra) {
    /* Increase bounds if necessary. */
    fr.top -= TILE_DIM * extra;
    fr.left -= TILE_DIM * extra;
    fr.width += TILE_DIM * 2 * extra;
    fr.height += TILE_DIM * 2 * extra;

    return (checkRockCollisions(fr) || checkTileCollisions(fr) || checkMobCollisions(fr));
}

/* Check collision with rocks. */
bool GameLogic::checkRockCollisions(const sf::FloatRect& fr) {
    /* Check intersections with rock tiles. */
    for (int i = 0; i < m_rocks.size(); i++) {
        if (fr.intersects(m_rocks[i]->getGlobalBounds())) {
            //std::cout << "ROCK COLLISION! \n";
            return true;
        }
    }
    return false;
}


/* Check intersections with mini collision tiles. */
bool GameLogic::checkTileCollisions(const sf::FloatRect& fr) {
    /* Check intersections with mini collision tiles. */
    for(int i = 0; i < m_collisionVector.size(); i++){
        if (fr.intersects(m_collisionVector[i].getGlobalBounds())){
            //std::cout << "COLLISION! \n";
            return true;
        }
    }
    return false;
}


/* Check intersections with mobs. */
bool GameLogic::checkMobCollisions(const sf::FloatRect& fr) {
    for (int i = 0; i < m_mobs.size(); i++) {
        if (fr.intersects(m_mobs[i]->getGlobalBounds())) {
            std::cout << "MOB COLLISION! \n";
//            enemyAttack(m_mobs[i]);
//            std::cout<<"Player health"<<m_player.getHealth();
            return true;
        }
    }

    /* Greyscale collision check*/
    for (int i = 0; i < m_greyscaleVec.size(); i++){
      if(fr.intersects(m_greyscaleVec[i]->getGlobalBounds())){
        //call something
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

/* Checks intersection with player */
bool GameLogic::checkPlayer(sf::FloatRect fr, int extra) {
    /* Increase bounds if necessary. */
    fr.top -= TILE_DIM * extra;
    fr.left -= TILE_DIM * extra;
    fr.width += TILE_DIM * 2 * extra;
    fr.height += TILE_DIM * 2 * extra;

    /* Check intersections with player bounds. */
    if (fr.intersects(m_view->getGlobalBounds())) {
        return true;
    }
    return false;
}

/* Checks collision with portal */
bool GameLogic::checkPortals(const sf::FloatRect& fr){
    if(fr.intersects(m_redPortal.getGlobalBounds())){
      std::cout << "RED PORTAL TRIGGERED \n";
      DoorEvent *doorEvent = new DoorEvent(GameState::RedLevel, 1, Direction::Up);
      m_game->queueEvent(doorEvent);
      return true;
    }

    else if(fr.intersects(m_bluePortal.getGlobalBounds())){
      std::cout << "BLUE PORTAL TRIGGERED \n";
      DoorEvent *doorEvent = new DoorEvent(GameState::BlueLevel, 1, Direction::Up);
      m_game->queueEvent(doorEvent);
      return true;
    }

    else if(fr.intersects(m_yellowPortal.getGlobalBounds())){
      std::cout << "YELLOW PORTAL TRIGGERED \n";
      DoorEvent *doorEvent = new DoorEvent(GameState::YellowLevel, 1, Direction::Up);
      m_game->queueEvent(doorEvent);
      return true;
    }

    else if(fr.intersects(m_greyPortal.getGlobalBounds())){
      if(!bossAvailable){
        std::cout << "LOAD BOSS ROOM \n";
        DoorEvent *doorEvent = new DoorEvent(GameState::BossLevel, 1, Direction::Up);
        m_game->queueEvent(doorEvent);
        spawnGreyscale();
      }
      else{
        std::cout << "BOSS BATTLE NOT YET AVAILABLE \n";
        //display text to user
      }
      return true;
    }
    return false; //no portal collisions
}

void GameLogic::spawnGreyscale(){
  DynamicActor *actor = new Greyscale(sf::Color(255,255,0), 100, 20, sf::Vector2f(400,80), 100.f);
  m_view->setGreyscaleAnimation(*actor);
  m_greyscaleVec.push_back(actor);
  m_view->setFadeGoal(0);

  AIView *aiview = new AIView(actor, this, m_game);
  m_aiviews.push_back(aiview);
}

std::vector<DynamicActor*> GameLogic::getGreyscale(){
  return m_greyscaleVec;
}

/* Returns rock vector */
std::vector<Actor*> GameLogic::getRocks() {
    return m_rocks;
}


/* Returns mob vector */
std::vector<DynamicActor*> GameLogic::getMobs() {
    return m_mobs;
}

/* remove rocks from memory */
void GameLogic::clearRocks() {
    m_rocks.clear();
}

/* Remove enemies from memory */
void GameLogic::clearEnemies(){
    m_mobs.clear();
}

/* Returns path map. */
char** GameLogic::getPathMap() {
    return m_pathMap;
}

/* Returns number of nodes in path map. */
sf::Vector2i GameLogic::getNumNodes() {
    return m_numNodes;
}

/* Called after a player-initiated attackEvent */
void GameLogic::playerAttack(Direction dir) {
    printf("playerAttack!\n");
    sf::FloatRect fr = m_sprite->getGlobalBounds();
    float verticalMove, horizontalMove;
    // Change the size and position of the rectangle depending on the attack direction, attack range is 20px
    switch (dir) {
        case Up:
            fr.height += 40;
            fr.top -= 40;
            fr.width += 40;
            fr.left -= 20;
            verticalMove = -100;
            horizontalMove = 0;
            break;
        case Down:
            fr.height += 40;
            fr.width += 40;
            fr.left -= 20;
            verticalMove = 100;
            horizontalMove = 0;
            break;
        case Left:
            fr.width += 40;
            fr.left -= 40;
            fr.height += 40;
            fr.top -= 20;
            verticalMove = 0;
            horizontalMove = -100;
            break;
        case Right:
            fr.width += 40;
            fr.height += 40;
            fr.top -= 20;
            verticalMove = 0;
            horizontalMove = 100;
            break;
    }

    /* Check attack's intersection with mobs. */
    for (int i = 0; i < m_mobs.size(); i++) {
        if (fr.intersects(m_mobs[i]->getGlobalBounds()) && m_mobs[i]->getColor() == m_player.getColor()) {
            m_player.attack(*m_mobs[i]);

            // Bounce back
            sf::Vector2f prevPos = m_mobs[i]->getPosition();
            prevPos.x = round(prevPos.x / TILE_DIM) * TILE_DIM;
            prevPos.y = round(prevPos.y / TILE_DIM) * TILE_DIM;

            m_mobs[i]->setPosition(sf::Vector2f(prevPos.x + horizontalMove, prevPos.y + verticalMove));
            m_mobs[i]->setKnockback(true);

            if (checkTileCollisions(m_mobs[i]->getGlobalBounds()) || checkRockCollisions(m_mobs[i]->getGlobalBounds())) {
                m_mobs[i]->setPosition(prevPos);
            }

            // Mob dies
            if (m_mobs[i]->getHealth() <= 0) {
                // flashes and disappear
                m_mobs.erase(m_mobs.begin() + i); // Delete the dead mob
                m_aiviews.erase(m_aiviews.begin() + i); // Delete the dead mob's aiview
            }
        }
    }
}


/* Called after a enemy-initiated attackEvent */
void GameLogic::enemyAttack(DynamicActor* attacker) {
    attacker->attack(m_player);
    // Player died
    if (m_player.getHealth() <= 0) {
        ChangeStateEvent *changeState = new ChangeStateEvent(GameState::PlayerDied);
        m_game->queueEvent(changeState);
    }
}

/* Return health of player */
float GameLogic::getPlayerHealth() {
    return m_player.getHealth();
}

/* Returns information on levels cleared */
int GameLogic::getLevelsCleared() {
    int index = 0;
    for (int k = 0; k < 3; k++) {
        if (m_possibleMobColors[k] == true) {
            index = k;
        }
    }
    return index;
}

void GameLogic::moveMobs(float &deltaTime) {
    for (int i=0; i<m_aiviews.size(); i++) {
        m_aiviews[i]->move(m_view, deltaTime);
    }
}

void GameLogic::updateGreyscale(float &deltaTime){
  for(int i = 0; i<m_bossScripts.size(); i++){
    m_bossScripts[i]->update(m_view, deltaTime);
  }
    for(int i = 0; i<m_bossAIScripts.size(); i++){
      m_bossAIScripts[i]->move(m_view, deltaTime);
    }


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
    if(checkCollisions(m_sprite->getGlobalBounds(), 0)){
        setCharPosition(prev);
    }

    /* Check doors. */
    bool doorDetected = checkDoors(m_sprite->getGlobalBounds(), 0);
    if (doorDetected && !m_onDoor) {
        std::cout << "onDoor\n";
        m_onDoor = true;
        DoorEvent *doorEvent = new DoorEvent(m_game->getState(), 1, dir);
        m_game->queueEvent(doorEvent);
    }
    else if (!doorDetected && m_onDoor) {
        std::cout << "not onDoor\n";
        m_onDoor = false;
    }

    if(m_game->getState() == GameState::Hub){
      bool portalDetected = checkPortals(m_sprite->getGlobalBounds());
      if(portalDetected){
        dungeonReturnPosition = prev;
        dungeonReturnCamera = m_view->getCameraCenter();
      }
    }

    if(m_game->getState() == GameState::BossLevel){
      if(m_sprite->getGlobalBounds().intersects(m_bossTrigger.getGlobalBounds())){
        std::cout << "BOSS BATTLE TRIGGERED \n";
        bossTriggered = true;
      }
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
            setCharPosition(dungeonReturnPosition);
            m_view->updateCamera(dungeonReturnCamera.x, dungeonReturnCamera.y);
            unlockColor(curState);
        }
        else if (newState == GameState::RedLevel) {
            m_view->updateCamera(RED_CAM);
            setCharPosition(RED_POS);
        }
        else if (newState == GameState::BlueLevel){
            m_view->updateCamera(BLUE_CAM);
            setCharPosition(BLUE_POS);
        }
        else if (newState == GameState::YellowLevel){
            m_view->updateCamera(YELLOW_CAM);
            setCharPosition(YELLOW_POS);
        }
        else if (newState == GameState::BossLevel){
          m_view->updateCamera(GREYSCALE_CAM);
          setCharPosition(GREY_POS);
        }
    }

    else{
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

        if (new_pos.x < 0 || new_pos.y < 0 || new_pos.x > m_xBound || new_pos.y > m_yBound) {
            DoorEvent *doorEvent = new DoorEvent(GameState::Hub, 0, dir);
            m_game->queueEvent(doorEvent);
            toggleLevel();
        }
        else {
            setCharPosition(new_pos);
            m_onDoor = false;
        }
    }


    /* Upon entering a new room, spawn enemies / rocks */
    if((room > 0) && (doorEvent->getGameState() != GameState::Hub) && (doorEvent->getGameState() != GameState::BossLevel)){
        if (std::find(m_clearedRooms.begin(), m_clearedRooms.end(), room) == m_clearedRooms.end()) {
            sf::Vector2f center = m_view->getCameraCenter();
            sf::Vector2f size = m_view->getCameraSize();
            SpawnEvent *spawnRocksEvent = new SpawnEvent(Actor::Rock, 10, size, center);
            m_game->queueEvent(spawnRocksEvent);
            SpawnEvent *spawnMobsEvent = new SpawnEvent(Actor::Mob, 2, size, center);
            m_game->queueEvent(spawnMobsEvent);
            PathMapEvent *pathMapEvent = new PathMapEvent(size, center);
            m_game->queueEvent(pathMapEvent);
        }
    }
}


/* Triggered by an attackEvent */
void GameLogic::attack(const EventInterface& event) {
    const EventInterface *ptr = &event;
    const AttackEvent *attackEvent = dynamic_cast<const AttackEvent*>(ptr);
    if (attackEvent->isFromPlayer() == true) { // player attack
        Direction dir = attackEvent->getDirection();
        playerAttack(dir);
    }
    else { // enemy attack
        DynamicActor* attacker = attackEvent->getAttacker();
        enemyAttack(attacker);
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

    int index = 0;
    for (int k = 0; k < 3; k++) {
        if (m_possibleMobColors[k] == true) {
            index = k;
        }
    }

    sf::FloatRect tile;
    int rx, ry, x, y;

    bool cond = true;
    for (int i=0; i<count; i++) {
        /* while not on wall or near door... */
        do {
            rx = rand() % (WIDTH  / TILE_DIM);
            ry = rand() % (HEIGHT / TILE_DIM);

            x = rx * TILE_DIM + l;
            y = ry * TILE_DIM + t;

            tile.left = x; tile.top = y;
            tile.width = tile.height = TILE_DIM;

            cond = checkCollisions(tile, 1) || checkDoors(tile, 2);
            if (actorType == Actor::Mob) {
                cond = cond || checkPlayer(tile, 10);
            }
        } while (cond);

        /* have a valid spawn location. */
        if (actorType == Actor::Rock) {
            Actor *actor = new Actor(actorType, sf::Vector2f(TILE_DIM,TILE_DIM),
                                                sf::Vector2f(x,y));
            m_view->setRockTexture(*actor);
            m_rocks.push_back(actor);
        } else if (actorType == Actor::Mob) {
            int col_int = rand() % (index + 1);
            sf::Color col;
            DynamicActor *actor;
            if (col_int == 0) { // Red: high health, low attack, low speed, good for getting familiar with game
                col = sf::Color(255, 0, 0);
                actor = new Mob(col, 150, 4, sf::Vector2f(x,y), 50.f);
            }
            else if (col_int == 1) { // Blue: medium health, medium attack, medium speed, medium mobs
                col = sf::Color(0, 0, 255);
                actor = new Mob(col, 100, 8, sf::Vector2f(x,y), 100.f);
            }
            else { // Yellow: low health, high attack, high speed, hard mobs
                col = sf::Color(255, 255, 0);
                actor = new Mob(col, 50, 12, sf::Vector2f(x,y), 150.f);
            }

            m_view->setMobAnimation(col, *actor);
            m_mobs.push_back(actor);

            AIView *aiview = new AIView(actor, this, m_game);
            m_aiviews.push_back(aiview);
        }
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

/* Unlocks a color that a spawned mob can have.*/
void GameLogic::unlockColor(GameState state) {
    if (state == GameState::RedLevel) {
        m_possibleMobColors[1] = true;
        m_player.unlockColor(sf::Color::Blue);
    }
    else if (state == GameState::BlueLevel) {
        m_possibleMobColors[2] = true;
        m_player.unlockColor(sf::Color::Yellow);
    }
}

void GameLogic::pathMap(const EventInterface& event) {
    printf("pathMap!\n");
    const PathMapEvent *pathMapEvent = dynamic_cast<const PathMapEvent*>(&event);
    const sf::Vector2f size = pathMapEvent->getSize();
    const sf::Vector2f center = pathMapEvent->getCenter();

    int n = m_numNodes.x;
    int m = m_numNodes.y;
    sf::FloatRect gb;

    // Reset map
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            m_pathMap[i][j] = ' ';
        }
    }

    // Collision tiles.
    for(int i = 0; i < m_collisionVector.size(); i++){
        gb = m_collisionVector[i].getGlobalBounds();

        // Outside of view.
        if (gb.left < center.x - size.x / 2 || gb.left >= center.x + size.x / 2 ||
            gb.top < center.y - size.x / 2 || gb.top >= center.y + size.x / 2) {
            continue;
        }

        int x = (int) gb.left % WIDTH / TILE_DIM;
        int y = (int) gb.top % HEIGHT / TILE_DIM;
        m_pathMap[x][y] = '#';
    }

    // Rock tiles.
    for (int i = 0; i < m_rocks.size(); i++) {
        gb = m_rocks[i]->getGlobalBounds();

        // Outside of view.
        if (gb.left < center.x - size.x / 2 || gb.left >= center.x + size.x / 2 ||
            gb.top < center.y - size.x / 2 || gb.top >= center.y + size.x / 2) {
            continue;
        }

        int x = (int) gb.left % WIDTH / TILE_DIM;
        int y = (int) gb.top % HEIGHT / TILE_DIM;
        printf("rock at %d %d\n", x, y);
        if (x > 0 && y > 0) {
            m_pathMap[x][y] = '#';
        }
    }

    for(int y=0;y<m;y++) {
        for(int x=0;x<n;x++)
            printf("%c", m_pathMap[x][y]);
        printf("\n");
    }
}
