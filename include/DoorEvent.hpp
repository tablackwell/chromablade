#ifndef DOOREVENT_HPP
#define DOOREVENT_HPP

#include "EventInterface.hpp"
#include "EventType.hpp"
#include "GameState.hpp"

class DoorEvent : public EventInterface {
public:
    DoorEvent(GameState state, int room);
    const EventType& getEventType(void) const;
    const int getRoom() const;
    const GameState getGameState() const;
private:
    GameState m_state;
    int m_room;
    EventType m_type;
};
#endif
