#ifndef MOVEEVENT_HPP
#define MOVEEVENT_HPP

#include "EventInterface.hpp"
#include "EventType.hpp"


enum Direction { Up, Down, Left, Right };


/*
 * A MoveEvent is generated when the player presses keys associated with character movement.
 */
class MoveEvent : public EventInterface {
	public:
        MoveEvent(Direction direction);
	    Direction getDirection();

	private:
    
	private: // event data
	    Direction m_dir;
};

#endif
