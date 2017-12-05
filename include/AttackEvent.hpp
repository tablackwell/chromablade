#ifndef ATTACKEVENT_HPP
#define ATTACKEVENT_HPP

#include "EventInterface.hpp"
#include "EventType.hpp"
#include "DynamicActor.hpp"
#include "MoveEvent.hpp"

/*
 * An AttackEvent is generated when the character or enemy attacks.
 */
class AttackEvent : public EventInterface {
    public:
        AttackEvent(bool isFromPlayer, Direction dir, sf::Color col);
        AttackEvent(bool isFromPlayer, DynamicActor* attacker);
        bool isFromPlayer() const;
        Direction getDirection() const;
        DynamicActor* getAttacker() const;

    private: // event data
        bool m_isFromPlayer;
        Direction m_dir;
        DynamicActor* m_attacker;
        sf::Color m_color;
};

#endif
