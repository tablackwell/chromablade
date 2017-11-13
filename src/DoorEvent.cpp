#include "DoorEvent.hpp"

DoorEvent::DoorEvent(GameState state, int room, Direction dir) {
    m_type = doorEvent;
    m_state = state;
    m_room = room;
    m_dir = dir;
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

const Direction DoorEvent::getDirection() const {
    return m_dir;
}
