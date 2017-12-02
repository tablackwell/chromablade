#ifndef LOADMAPEVENT_HPP
#define LOADMAPEVENT_HPP

#include "EventInterface.hpp"
#include "EventType.hpp"
#include "GameState.hpp"

class LoadMapEvent : public EventInterface {
public:
    LoadMapEvent(GameState state);
    const GameState getGameState(void) const;
private:
    GameState m_state;
    EventType m_type;
};

#endif
