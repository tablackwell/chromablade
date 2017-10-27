/*
 * Event manager used for processing events.
 */

#include "EventManager.hpp"
#include <iostream>

EventManager::EventManager() {
}


void EventManager::init() {
	Title title;
	std::function<void(const EventInterface &event)> titleScreen = std::bind(&Title::update2, &title, std::placeholders::_1);
	const EventListener listener = EventListener(titleScreen, 1);
	addListener(listener, EventType::sfmlEvent);
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
    SFMLEvent *newEvent = new SFMLEvent(event);
    m_registerQueue->m_eventList.push_back((EventInterface*)newEvent);
	
	std::cout<<"Queue size: "<<m_registerQueue->m_eventList.size()<<" "<<m_registerQueue->m_eventList.back()<<"\n";
}


/* Add listener. */
void EventManager::addListener(const EventListener &listener, const EventType &type) {

	m_listeners = m_eventMap[type];
	const static auto addToEnd = std::move(listener);
	
	// Listener not in list m_listeners. Add to list.
	if (std::find(m_listeners.begin(), m_listeners.end(), listener) == m_listeners.end()) {
		m_listeners.push_back(addToEnd);
		std::cout<<"Event type "<<type<< " Listener added: "<<listener.getId()<<" "<<m_listeners.back().getId()<<"\n";
		
	}
	std::cout<<"Listeners list size: "<<m_listeners.size()<<"\n";
}


/* Trigger event. */
void EventManager::triggerEvent(EventInterface& event) {
	auto m_itr = m_eventMap.find(event.getEventType());
	
	std::cout<<"Event type: "<<event.getEventType();
	std::cout<<" same as Iterator Event type: " << m_itr->first<<"\n";
	
	// Event not found
	if (m_itr == m_eventMap.end()) {
		std::cout<<"End \n";
		return;
	}
	
	// Trigger all events in listener list
	else {
		auto m_list = m_itr->second;
		std::cout<<"Map size: "<<m_eventMap.size()<<"Listener list size: "<<m_list.size()<<" ID: "<<m_list.front().getId()<<"\n";
		for (auto m_funcItr = m_list.begin(); m_funcItr != m_list.end(); m_funcItr++){
			std::cout<<"Call";
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
    while (m_processQueue->m_eventList.size() > 0) {
        EventInterface *event = m_processQueue->m_eventList.front();
		m_processQueue->m_eventList.pop_front(); // No return value
        triggerEvent(*event);

    }
}
