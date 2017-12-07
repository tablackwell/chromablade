#ifndef DOOREVENT_HPP
#define DOOREVENT_HPP

#include "EventInterface.hpp"
#include "EventType.hpp"
#include "GameState.hpp"
#include "MoveEvent.hpp"

class DoorEvent : public EventInterface {
public:
    DoorEvent(GameState state, bool isDungeon, Direction dir);
    const int isDungeon() const;
    const Direction getDirection() const;
    const GameState getGameState() const;
    const sf::Vector2f getPrevPos() const;
private:
    GameState m_state;
    Direction m_dir;
    bool m_isDungeon;
};
#endif
