/*
 * Event that changes game states.
 */

 #ifndef CHANGESTATEEVENT_HPP
 #define CHANGESTATEEVENT_HPP

#include "EventInterface.hpp"
#include "EventType.hpp"
#include "GameState.hpp"

class ChangeStateEvent : public EventInterface{
public:
    ChangeStateEvent(GameState state);
    const GameState getGameState(void) const;
private:
    GameState m_newState;
    EventType m_type;
private:
};

#endif
