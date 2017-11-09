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
void EventManager::queueEvent(EventInterface *event, float deltaTime) {
    m_registerQueue->m_eventList.push_back(event);
    std::cout<<" Size "<<m_registerQueue->m_eventList.size();
    std::cout<<" Queuing event "<<event->getEventType()<<"\n";
}


/* Queue SFML event. */
void EventManager::queueEvent(sf::Event event, float deltaTime) {
    SFMLEvent *newEvent = new SFMLEvent(event);
    std::cout<<"Delta time: "<<newEvent->getDeltaTime()<<std::endl;
    m_registerQueue->m_eventList.push_back((EventInterface*)newEvent);
}


/* Add listener. */
void EventManager::addListener(const EventListener &listener, const EventType &type) {

    auto eventType = m_eventMap.find(type);
    std::list<EventListener> listeners;

    // Event type already in map.
    if (eventType != m_eventMap.end()) {
        listeners = m_eventMap.find(type)->second;
        
        // Listener not in list. Add to list.
        if (std::find(listeners.begin(), listeners.end(), listener) == listeners.end()) {
            auto newListener = std::move(listener);
            std::cout<<"Adding";
            eventType->second.push_back(newListener);
        }
        
   // Event type not already in map.
    } else {
        listeners.push_front(listener);
        m_eventMap.emplace(type, listeners);
    }
    std::cout<<"Event type "<<type<<"Listener "<<listener.getId()<<"\n";
    
    auto map = m_eventMap.find(type);

    std::cout<<"Inserting: "<<listener.getId()<<" Size "<<map->second.size();
    std::cout << "KEY: " << m_eventMap.find(type)->first << " Values: ";
    for (auto list_iter = map->second.begin(); list_iter != map->second.end(); list_iter++) {
        std::cout << " " << list_iter->getId();
    }
    std::cout<<std::endl;
}


/* Trigger event. */
void EventManager::triggerEvent(EventInterface& event) {
    // Find listeners mapped to event type.
    auto listItr = m_eventMap.find(event.getEventType());
    
    // Event not found.
	if (m_eventMap.find(event.getEventType()) == m_eventMap.end()) {
		std::cout<<"Event not found \n";
	}
	
	// Trigger all events in listener list.
	else {
        std::list<EventListener> listeners;

        listeners = listItr->second;
        std::cout<<"EVENT TYPE: "<<event.getEventType()<<" ";
        for (auto m_funcItr = listeners.begin(); m_funcItr != listeners.end(); m_funcItr++){
            m_funcItr->callFunction(event);
            std::cout<<"Calling: "<<m_funcItr->getId()<<" ";
        }
        std::cout<<std::endl;
    }
}


/* Process all events in event queue. */
void EventManager::update() {
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
