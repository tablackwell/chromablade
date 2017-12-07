#include "AttackEvent.hpp"

/* The constructor is called when the player attacks */
AttackEvent::AttackEvent(bool isFromPlayer, Direction dir, sf::Color col) {
    m_type = attackEvent;
    m_isFromPlayer = isFromPlayer;
    m_color = col;
    m_dir = dir;
}

/* The constructor is called when an enemy attacks */
AttackEvent::AttackEvent(bool isFromPlayer, DynamicActor* attacker) {
    m_type = attackEvent; 
    m_isFromPlayer = isFromPlayer; 
    m_attacker = attacker;
}

/* Indicate whether the attack is a player attack */
bool AttackEvent::isFromPlayer() const {
    return m_isFromPlayer;
}

/* Return the direction of the attack, only used when player attacks */
Direction AttackEvent::getDirection() const { 
    return m_dir;
}

/* Return the attacker, only used when an enemy attacks */
DynamicActor* AttackEvent::getAttacker() const {
    return m_attacker;
}

