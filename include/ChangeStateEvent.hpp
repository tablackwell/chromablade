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
    virtual const EventType& getEventType(void) const;
    const GameState getGameState(void) const;
private:
    GameState newState;
    EventType type;
private:
};

#endif
