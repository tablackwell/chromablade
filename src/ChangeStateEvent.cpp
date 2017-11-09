/*
 * Event that changes game states.
 */

#include "ChangeStateEvent.hpp"

ChangeStateEvent::ChangeStateEvent(GameState state) {
    this->m_type = EventType::changeStateEvent;
    this->m_newState = state;
}

/* Return event type. */
const EventType& ChangeStateEvent::getEventType() const {
    return m_type;
}

/* Return game state. */
const GameState ChangeStateEvent::getGameState() const {
    return m_newState;
}
