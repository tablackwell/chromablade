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
    this->m_window = mainWindow;
}


/* Queue event. */
void EventManager::queueEvent(EventInterface *event) {
    m_registerQueue->m_eventList.push_back(event);
}

void EventManager::queueEvent(sf::Event event) {
    EventInterface *newEvent = convertSfEvent(event);
    m_registerQueue->m_eventList.push_back(newEvent);
}


/* Convert sfKeyEvents to EventInterface for event handling. */
EventInterface* EventManager::convertSfEvent(sf::Event event) {
    EventInterface *newEvent;
    switch (event.type) {
        case sf::Event::KeyPressed: {
            if (event.key.code == sf::Keyboard::Up) {
                std::cout<<event.key.code;
                EventInterface *newEvent = new MoveEvent(Direction::Up);
            }
        }
        default :
            std::cout<<"DefaultSwitch"<<std::endl;
    }
    return newEvent;
}

/* Add listener. */
void EventManager::addListener(EventListener &listener, EventType &type) {

    m_listeners = m_eventMap[type];

    // Listener not found
    if (std::find(m_listeners.begin(), m_listeners.end(), listener) == m_listeners.end()) {
        m_listeners.push_back(listener);
    }
}


/* Trigger event. */
void EventManager::triggerEvent(EventInterface& event) {
    auto m_itr = m_eventMap.find(event.getEventType());

    // Event not found
    if (m_itr == m_eventMap.end()) {
        return;
    }
    // Trigger all events in listener list
    else {
        auto m_list = m_itr->second;
        for (auto m_funcItr = m_list.begin(); m_funcItr != m_list.end(); m_funcItr++){
            m_funcItr->callFunction(event);
        }
    }
}


/* Process all events in event queue. */
void EventManager::handleEvents() {
    // Swap queues and clear old queue
    std::swap(m_processQueue, m_registerQueue);
    m_registerQueue->m_eventList.clear();

    // Process all events in queue
    while (!(m_processQueue->m_eventList.empty())) {
        EventInterface *event = m_processQueue->m_eventList.front();
        m_processQueue->m_eventList.pop_front(); // No return value
        triggerEvent(*event);
    }
}
