#include "MoveEvent.hpp"

MoveEvent::MoveEvent(Direction direction) {
    dir = direction;
}

const EventType& MoveEvent::getEventType() const{
    return EventType::moveEvent;
}

/* Set the movement direction */
void MoveEvent::setDirection(Direction direction){
    dir = direction;
}

Direction MoveEvent::getDirection(){
    return dir;
}
