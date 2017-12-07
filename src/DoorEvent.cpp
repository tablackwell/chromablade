#include "DoorEvent.hpp"

DoorEvent::DoorEvent(GameState state, bool isDungeon, Direction dir) {
    m_type = doorEvent;
    m_state = state;
    m_isDungeon = isDungeon;
    m_dir = dir;
}

const GameState DoorEvent::getGameState() const {
    return m_state;
}

const int DoorEvent::isDungeon() const {
    return m_isDungeon;
}

const Direction DoorEvent::getDirection() const {
    return m_dir;
}
