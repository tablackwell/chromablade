/*
 * Event manager used for processing events.
 */

#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <map>
#include <list>
#include <algorithm>

#include "EventInterface.hpp"
#include "EventListener.hpp"
#include "SFMLEvent.hpp"
#include "MoveEvent.hpp"
#include "EventType.hpp"

// Queues used to store events.
typedef struct {
    std::list<EventInterface*> m_eventList;
} EventQueue;


class EventManager {
public:
	EventManager();
	void init();
	void setWindow(sf::RenderWindow *mainWindow);
	void addListener(const EventListener &listener, const EventType &type);
	void removeListener(EventListener &listener, EventType &type);
	virtual void queueEvent(EventInterface *event);
	virtual void queueEvent(sf::Event event);
	virtual void triggerEvent(EventInterface &event);
	virtual void update(void);

private:
private:
	sf::RenderWindow *m_window; // Reference to RenderWindow
	EventQueue m_queues[2]; // List of queues
	EventQueue *m_processQueue = &m_queues[0]; // Queue for processing events
	EventQueue *m_registerQueue = &m_queues[1]; // Queue for registering events
	std::map<EventType, std::list<EventListener>> m_eventMap; // Maps event to listeners
};

#endif
