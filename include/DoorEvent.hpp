#ifndef DOOREVENT_HPP
#define DOOREVENT_HPP

#include "EventInterface.hpp"
#include "EventType.hpp"
#include "GameState.hpp"
#include "MoveEvent.hpp"

class DoorEvent : public EventInterface {
public:
    DoorEvent(GameState state, int room, Direction dir);
    const int getRoom() const;
    const Direction getDirection() const;
    const GameState getGameState() const;
private:
    GameState m_state;
    Direction m_dir;
    int m_room;
};
#endif
