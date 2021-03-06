/*
 * Event listener.
 */

#ifndef EVENTLISTENER_HPP
#define EVENTLISTENER_HPP

#include <functional>
#include "EventInterface.hpp"

//typedef struct {
//    std::function<void(const EventInterface&)> function;
//} EventListener;

class EventListener {
public:
    /* Override equality operator. */
    bool operator==(const EventListener &otherListener) {
        return m_id == otherListener.getId();
    }
    EventListener();
	EventListener(std::function<void(const EventInterface&)> function);
	EventListener(std::function<void(const EventInterface&)> function, float id);
	void callFunction(const EventInterface&);
    void setFunction(std::function<void(const EventInterface&)>);
    void setId(float id);
    float getId() const;
private:
private:
    float m_id; // Used for overriding equality
    std::function<void(const EventInterface&)> m_function;
};

#endif
