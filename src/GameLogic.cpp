#include "GameLogic.hpp"
#include "MoveEvent.hpp"
#include "AttackEvent.hpp"
#include "SpawnEvent.hpp"
#include "ChromaBlade.hpp"

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


/* Sets the position of character */
void GameLogic::setCharPosition(std::tuple<float, float> position) {
    m_player.setPosition(position);
    //std::cout << std::get<0>(position) << "\n";
    //std::cout << std::get<1>(position) << "\n";
}


/* Used to build a listener for moveEvent */
void GameLogic::moveChar(const EventInterface& event) {
    const EventInterface *ptr = &event;
    const MoveEvent *moveEvent = dynamic_cast<const MoveEvent*>(ptr);
    Direction dir = moveEvent->getDirection();
    float deltaTime = moveEvent->getDeltaTime();
    float x = std::get<0>(m_player.getPosition());
    float y = std::get<1>(m_player.getPosition());
    switch (dir){
    case Up:
        y = y - SPEED * deltaTime;
        break;
    case Down:
        y = y + SPEED * deltaTime;
        break;
    case Left:
        x = x - SPEED * deltaTime;
        break;
    case Right:
        x = x + SPEED * deltaTime;
        break;
    }
    setCharPosition(std::make_tuple(x, y));
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

        x = rand() % (blockSizeX-128) + i*blockSizeX + minX;
        y = rand() % (blockSizeY-128) + j*blockSizeY + minY;
        Actor *rock = new Actor(Actor::Rock, sf::Vector2f(32,32), sf::Vector2f(x,y));
        m_rocks.push_back(rock);

        n++;
    }
}

std::vector<Actor*> GameLogic::getRocks() {
    return m_rocks;
}

void GameLogic::clearRocks() {
    m_rocks.clear();
}
