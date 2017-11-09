/*
 * Event that changes game states.
 */

#include "ChangeStateEvent.hpp"

ChangeStateEvent::ChangeStateEvent(GameState state) {
    this->type = EventType::changeStateEvent;
    this->newState = state;
}

/* Return event type. */
const EventType& ChangeStateEvent::getEventType() const {
    return type;
}

/* Return game state. */
const GameState ChangeStateEvent::getGameState() const {
    return newState;
}
