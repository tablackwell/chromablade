#include "MoveEvent.hpp"

MoveEvent::MoveEvent(Direction direction) {
    m_dir = direction;
}

const EventType& MoveEvent::getEventType() const{
    return eventType;
}

/* Set the movement direction */
void MoveEvent::setDirection(Direction direction){
    m_dir = direction;
}

Direction MoveEvent::getDirection(){
    return m_dir;
}
