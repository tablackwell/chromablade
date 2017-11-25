#include "GameLogic.hpp"
#include "MoveEvent.hpp"
#include "LoadMapEvent.hpp"
#include "DoorEvent.hpp"
#include "AttackEvent.hpp"
#include "SpawnEvent.hpp"
#include "ChromaBlade.hpp"
#include "PlayerView.hpp"

#include <tuple>
#include <iostream>


GameLogic::GameLogic() : Process() {
}

void GameLogic::init(){
	m_level = red;
    setState(Process::RUNNING);
}

void GameLogic::update(float &deltaTime){
}

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
void GameLogic::setCharPosition(std::tuple<float, float> position) {
    m_player.setPosition(position);
    //std::cout << std::get<0>(position) << "\n";
    //std::cout << std::get<1>(position) << "\n";
}


/* Links game logic to player view */
void GameLogic::setView(PlayerView* view) {
    m_view = view;
}

void GameLogic::setAnimatedSprite(AnimatedSprite* sprite){
	m_sprite = sprite;
}

void GameLogic::toggleLevel(){
	levelToggled = true;
}


/* Adds listeners to eventManager */
void GameLogic::setListener() {
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


/***************************** Event Triggered Functions ******************************/

/* Used to build a listener for moveEvent */
void GameLogic::moveChar(const EventInterface& event) {
    const EventInterface *ptr = &event;
    const MoveEvent *moveEvent = dynamic_cast<const MoveEvent*>(ptr);
    Direction dir = moveEvent->getDirection();
    float deltaTime = moveEvent->getDeltaTime();
    float x = std::get<0>(m_player.getPosition());
    float y = std::get<1>(m_player.getPosition());
		float prevX = std::get<0>(m_player.getPosition());
		float prevY = std::get<1>(m_player.getPosition());
    bool noKeyPressed = true;
    sf::Vector2f moving;

    switch (dir){
        case Up:
            y = y - SPEED * deltaTime;

            moving = sf::Vector2f(0.f, -SPEED * deltaTime);
            noKeyPressed = false;
            break;
        case Down:
            y = y + SPEED * deltaTime;
            moving = sf::Vector2f(0.f, SPEED * deltaTime);
            noKeyPressed = false;
            break;
        case Left:
            x = x - SPEED * deltaTime;
            moving = sf::Vector2f(-SPEED * deltaTime, 0.f);
            noKeyPressed = false;
            break;
        case Right:
            x = x + SPEED * deltaTime;
            moving = sf::Vector2f(SPEED * deltaTime, 0.f);
            noKeyPressed = false;
            break;
    }
    setCharPosition(std::make_tuple(x, y));
    m_view->drawAnimation(dir, moving, noKeyPressed, deltaTime);
		bool collisionDetected = false;
		for(int i = 0; i < m_collisionVector.size(); i++){
			if (m_sprite->getGlobalBounds().intersects(m_collisionVector[i].getGlobalBounds())){
				std::cout << "COLLISION! \n";
				collisionDetected = true;
				break;
			}
		}
		for (int i=0; i<m_rocks.size(); i++) {
			if (m_sprite->getGlobalBounds().intersects(m_rocks[i]->getGlobalBounds())) {
				collisionDetected = true;
				break;
			}
		}
		if(collisionDetected){
			setCharPosition(std::make_tuple(prevX, prevY));
			m_sprite->setPosition(prevX, prevY);
		}
		bool doorDetected = false;
		for(int i = 0; i < m_doors.size(); i++){
			if (m_sprite->getGlobalBounds().intersects(m_doors[i].getGlobalBounds())){
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
		if(m_game->inDebugMode()){
			std::cout <<"Player Position (sprite then logic): \n " ;
			x = std::get<0>(m_player.getPosition());
			y = std::get<1>(m_player.getPosition());
			std::cout << m_sprite->getPosition().x << "," << m_sprite->getPosition().y << "\n";
			std::cout << x << "," << y << "\n";
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
        m_view->updateCamera(400,1520);
        m_sprite->setPosition(60,1520);
        setCharPosition(std::make_tuple(60,1520));
    }

    if(levelToggled){
    if (dir == Direction::Left) {
        m_sprite->setPosition(m_sprite->getPosition().x - 100, m_sprite->getPosition().y);
        m_view->updateCamera(-800,0);
    }
    else if (dir == Direction::Right){
        m_sprite->setPosition(m_sprite->getPosition().x + 100, m_sprite->getPosition().y);
        m_view->updateCamera(800,0);
    }
    else if (dir == Direction::Up){
        m_sprite->setPosition(m_sprite->getPosition().x, m_sprite->getPosition().y - 100);
        m_view->updateCamera(0, -608);

    }
    else if (dir == Direction::Down){
      m_sprite->setPosition(m_sprite->getPosition().x, m_sprite->getPosition().y + 100);
      m_view->updateCamera(0,608);
    }
    setCharPosition(std::make_tuple(m_sprite->getPosition().x, m_sprite->getPosition().y));
    }

    if (room > 0) {
        if (std::find(m_clearedRooms.begin(), m_clearedRooms.end(), room)
                == m_clearedRooms.end()) {
            sf::Vector2f center = m_view->getCameraCenter();
            sf::Vector2f size = m_view->getCameraSize();
            SpawnEvent *spawnEvent = new SpawnEvent(Actor::Rock, 1, size, center);
            m_game->queueEvent(spawnEvent);
        }
    }

}


void GameLogic::attack(const EventInterface& event) {
    const EventInterface *ptr = &event;
    const AttackEvent *attackEvent = dynamic_cast<const AttackEvent*>(ptr);
    if (attackEvent->getInitiator() == NULL) { // player attack
        // TODO: look for enemies nearby
        m_player.attack();
        std::cout << "player attack\n";
    }

}

void GameLogic::spawn(const EventInterface& event) {
    printf("spawn!\n");
    const EventInterface *ptr = &event;
    const SpawnEvent *spawnEvent = dynamic_cast<const SpawnEvent*>(ptr);
    const Actor::Type actorType = spawnEvent->getActorType();
    const int count = spawnEvent->getCount();
    const sf::Vector2f size = spawnEvent->getSize();
    const sf::Vector2f center = spawnEvent->getCenter();

    int x,y,r,i,j;
    int minX = center.x - size.x / 2 + 48;
    int minY = center.y - size.y / 2 + 48;

    int numBlocks = 3;
    int blockSizeX = size.x / numBlocks;
    int blockSizeY = size.y / numBlocks;

    int hash[9] = {0};

    int n=0;
    while (n < count) {
        do {
            r = rand() % 9;
        } while (r == 3 || hash[r]);

        hash[r]++;
        i = r % 3;
        j = r / 3;

        x = rand() % (blockSizeX-144) + i*blockSizeX + minX;
        y = rand() % (blockSizeY-144) + j*blockSizeY + minY;
        printf("%d %d %d %d %d\n", r, i, j, x, y);
        Actor *actor = new Actor(actorType, sf::Vector2f(32,32), sf::Vector2f(x,y));
        m_rocks.push_back(actor);

        n++;
    }
}

std::vector<Actor*> GameLogic::getRocks() {
    return m_rocks;
}

void GameLogic::clearRocks() {
    m_rocks.clear();
}
