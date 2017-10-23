#include "MoveEvent.h"

/* Set the movement direction */
void MoveEvent::setDirection(Direction direction){
    dir = direction;
}


Direction MoveEvent::getDirection(){
    return dir;
}


const EventType& MoveEvent::getEventType(void) const{
    return m_eventType;
}
