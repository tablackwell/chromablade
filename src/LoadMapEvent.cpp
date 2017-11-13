#include "LoadMapEvent.hpp"

LoadMapEvent::LoadMapEvent(GameState state) {
    m_type = EventType::loadMapEvent;
    m_state = state;
}

const EventType& LoadMapEvent::getEventType(void) const {
    return m_type;
};

const GameState LoadMapEvent::getGameState() const {
    return m_state;
}
