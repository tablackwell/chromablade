#include "DoorEvent.hpp"

DoorEvent::DoorEvent(GameState state, int room) {
    m_state = state;
    m_room = room;
    m_type = doorEvent;
}

const EventType& DoorEvent::getEventType() const {
    return m_type;
}

const GameState DoorEvent::getGameState() const {
    return m_state;
}

const int DoorEvent::getRoom() const {
    return m_room;
}
