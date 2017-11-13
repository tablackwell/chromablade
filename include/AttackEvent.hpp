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
        AttackEvent(DynamicActor* initiator, float damage) { m_damage = damage; m_initiator = initiator; m_type = attackEvent; }
        AttackEvent() { m_damage = 10; m_initiator = NULL; m_type = attackEvent; }
        DynamicActor* getInitiator() const { return m_initiator; }
        float getDamage() const { return m_damage; }
        const EventType& getEventType(void) const { return m_type; }

    private:

    private: // event data
        DynamicActor* m_initiator;
        float m_damage;
        EventType m_type;
};

#endif
