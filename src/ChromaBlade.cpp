#include "ChromaBlade.hpp"


/* This class is the game application layer */
ChromaBlade::ChromaBlade() : m_window(sf::VideoMode(WIDTH,HEIGHT,32), "Chromablade", sf::Style::Titlebar | sf::Style::Close)
{
    /* Starts on the Title screen. */
    m_state = GameState::Title;

    m_gameLogic.setGameApplication(this);
    m_gameLogic.setView(&m_view);
    m_view.setGameLogic(&m_gameLogic);
    m_view.setContext(&m_window);
    m_view.setGameApplication(this);
    m_eventManager.setWindow(&m_window);
    m_window.setVerticalSyncEnabled(true);
    m_window.setKeyRepeatEnabled(false);
    registerListeners();

    srand(time(NULL));
}


/* Initialize the game */
void ChromaBlade::init(){
    m_gameLogic.init();
    m_view.init();

    /* Play music on start. */
    //m_audio.init();

    /* Attach PlayerView, GameLogic, and Audio to ProcessManager. */
    m_processManager.attachProcess(&m_view);
    m_processManager.attachProcess(&m_gameLogic);
    //m_processManager.attachProcess(&m_audio);
}


/* Main game loop */
void ChromaBlade::run(){
	while(m_window.isOpen()){
        float deltaTime = m_fpsTimer.restart().asSeconds();
        handleInput(deltaTime);
        update(deltaTime);
        handleEvents(deltaTime);
        render();
	}
}


/* Call playerView to handle player inputs */
void ChromaBlade::handleInput(float deltaTime) {
    m_view.handleInput(deltaTime);
}


/* Update game logic */
void ChromaBlade::update(float &deltaTime) {
    switch (m_state) {
        case GameState::Title:
        case GameState::Pause:
        case GameState::PlayerDied:
        case GameState::Instruction:
            break;
        default:
            m_processManager.update(deltaTime);
            break;
    }
}


/* Process events in eventManager */
void ChromaBlade::handleEvents(float deltaTime) {
    m_eventManager.update(deltaTime);
}


/* Call playerView to render */
void ChromaBlade::render() {
    m_view.draw();
}


/* Set the game state */
void ChromaBlade::setState(GameState state) {
    m_state = state;
}


/* Return the game state */
GameState ChromaBlade::getState() {
    return m_state;
}


/* Return previous game state */
GameState ChromaBlade::getPrevState() {
    return m_prevState;
}


/* Allow other components to register listeners */
void ChromaBlade::registerListener(EventListener listener, EventType eventType) {
    m_eventManager.addListener(listener, eventType);
}


/* Allow other components to queue events */
void ChromaBlade::queueEvent(EventInterface *event) {
    m_eventManager.queueEvent(event);
}


/* Add listeners to the EventManager */
void ChromaBlade::registerListeners() {
    // Subscribe to events.
    std::function<void(const EventInterface &event)> changeState = std::bind(&ChromaBlade::updateState, this, std::placeholders::_1);
    const EventListener m_listener1 = EventListener(changeState, EventType::changeStateEvent);
    m_eventManager.addListener(m_listener1, EventType::changeStateEvent);
}


/* Update game state, triggered by a ChangeStateEvent. */
void ChromaBlade::updateState(const EventInterface &event) {
    const EventInterface *ptr = &event;
    if (const ChangeStateEvent *stateEvent = dynamic_cast<const ChangeStateEvent*>(ptr)){
        m_prevState = m_state;
        m_state = stateEvent->getGameState();
        switch(m_state) {
            case GameState::Title:
                printf("Changed state to Title!\n");
                break;
            case GameState::Pause:
                printf("Changed state to Pause!\n");
                break;
            case GameState::Hub:
                // Start the game
                m_view.setListener();
                m_gameLogic.setListener();
                printf("Changed state to Hub!\n");
                break;
            case GameState::RedLevel:
                printf("Changed state to RedLevel!\n");
                break;
            case GameState::BlueLevel:
                printf("Changed state to BlueLevel!\n");
                break;
            case GameState::YellowLevel:
                printf("Changed state to YellowLevel!\n");
                break;
            case GameState::Instruction:
                printf("Changed state to Instruction!\n");
                break;
        }
    }
}


/************************* Debug methods ************************/
bool ChromaBlade::inDebugMode(){
  return inDebug;
}


void ChromaBlade::setDebug(){
  inDebug = true;
}
