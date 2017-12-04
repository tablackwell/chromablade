#ifndef ATTACKEVENT_HPP
#define ATTACKEVENT_HPP

#include "EventInterface.hpp"
#include "EventType.hpp"
#include "DynamicActor.hpp"


/*
 * An AttackEvent is generated when the character or enemy attacks.
 */
class AttackEvent : public EventInterface {
    public:
        AttackEvent(bool isFromPlayer, Direction dir, sf::Color col) { m_dir = dir; m_isFromPlayer = isFromPlayer; m_type = attackEvent; m_color = col;}
        AttackEvent(bool isFromPlayer, DynamicActor* attacker) { m_isFromPlayer = isFromPlayer; EventType m_type; m_attacker = attacker; }
        bool isFromPlayer() const { return m_isFromPlayer; }
        Direction getDirection() const { return m_dir; }
        DynamicActor* getAttacker() const { return m_attacker; }

    private:

    private: // event data
        bool m_isFromPlayer;
        Direction m_dir;
        DynamicActor* m_attacker;
        sf::Color m_color;
};

#endif
