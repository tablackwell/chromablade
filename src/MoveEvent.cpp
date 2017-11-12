#include "MoveEvent.hpp"


MoveEvent::MoveEvent(Direction direction) {
    m_dir = direction;
    m_type = moveEvent;
}


/* Returns the direction of movement */
Direction MoveEvent::getDirection(){
    return m_dir;
}
