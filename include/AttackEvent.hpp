#ifndef ATTACKEVENT_HPP
#define ATTACKEVENT_HPP

#include "EventInterface.hpp"
#include "EventType.hpp"
#include "DynamicActor.hpp"


/*
 * A AttackEvent is generated when the character or enemy attacks.
 */
class AttackEvent : public EventInterface {
    public:
        AttackEvent(bool isFromPlayer, Direction dir) { m_dir = dir; m_isFromPlayer = isFromPlayer; m_type = attackEvent; }
        bool isFromPlayer() const { return m_isFromPlayer; }
        const EventType& getEventType(void) const { return m_type; }
        Direction getDirection() const { return m_dir; }

    private:

    private: // event data
        bool m_isFromPlayer;
        EventType m_type;
        Direction m_dir;
};

#endif
