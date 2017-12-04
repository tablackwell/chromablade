#include "LoadMapEvent.hpp"

LoadMapEvent::LoadMapEvent(GameState state) {
    m_type = EventType::loadMapEvent;
    m_state = state;
}

const GameState LoadMapEvent::getGameState() const {
    return m_state;
}
