#ifndef PATHMAPEVENT_HPP
#define PATHMAPEVEN_HPP

#include "EventInterface.hpp"
#include "EventType.hpp"

class PathMapEvent : public EventInterface {
public:
    PathMapEvent() { m_type = pathMapEvent; }
};

#endif
