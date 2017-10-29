/*
 * Event manager used for processing events.
 */

#include "EventManager.hpp"
#include <iostream>

EventManager::EventManager() {
}


void EventManager::init() {
}

/* Set reference to window. */
void EventManager::setWindow(sf::RenderWindow *mainWindow) {
    m_window = mainWindow;
}


/* Queue event. */
void EventManager::queueEvent(EventInterface *event) {
    m_registerQueue->m_eventList.push_back(event);
}


/* Queue SFML event. */
void EventManager::queueEvent(sf::Event event) {
    SFMLEvent *newEvent = new SFMLEvent(event);
    m_registerQueue->m_eventList.push_back((EventInterface*)newEvent);
	
//    std::cout<<"Queue size: "<<m_registerQueue->m_eventList.size()<<" "<<m_registerQueue->m_eventList.back()<<"\n";
}


/* Add listener. */
void EventManager::addListener(const EventListener &listener, const EventType &type) {

	m_listeners = m_eventMap[type];
	
	// Listener not in list m_listeners. Add to list.
	if (std::find(m_listeners.begin(), m_listeners.end(), listener) == m_listeners.end()) {
		m_listeners.push_back(listener);
        
//        std::cout<<"Event type "<<type<< " Listener added: "<<listener.getId()<<" "<<m_listeners.back().getId()<<"\n";
		
	}
}


/* Trigger event. */
void EventManager::triggerEvent(EventInterface& event) {
    
	// Event not found.
	if (m_eventMap.find(event.getEventType()) == m_eventMap.end()) {
		std::cout<<"Event not found \n";
	}
	
	// Trigger all events in listener list.
	else {
		for (auto m_funcItr = m_listeners.begin(); m_funcItr != m_listeners.end(); m_funcItr++){
			m_funcItr->callFunction(event);
		}
	}
}


/* Process all events in event queue. */
void EventManager::handleEvents() {
    // Swap queues and clear old queue.
    std::swap(m_processQueue, m_registerQueue);
    m_registerQueue->m_eventList.clear();

    // Process all events in queue.
    while (m_processQueue->m_eventList.size() > 0) {
        EventInterface *event = m_processQueue->m_eventList.front();
		m_processQueue->m_eventList.pop_front(); // No return value
        triggerEvent(*event);

    }
}
