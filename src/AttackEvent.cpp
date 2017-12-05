#include "AttackEvent.hpp"

AttackEvent::AttackEvent(bool isFromPlayer, Direction dir, sf::Color col) {
    m_type = attackEvent;
    m_isFromPlayer = isFromPlayer;
    m_color = col;
    m_dir = dir;
}

AttackEvent::AttackEvent(bool isFromPlayer, DynamicActor* attacker) {
    m_type = attackEvent; 
    m_isFromPlayer = isFromPlayer; 
    m_attacker = attacker;
}

bool AttackEvent::isFromPlayer() const {
    return m_isFromPlayer;
}

Direction AttackEvent::getDirection() const { 
    return m_dir;
}

DynamicActor* AttackEvent::getAttacker() const {
    return m_attacker;
}

