#ifndef PLAYERVIEW_HPP
#define PLAYERVIEW_HPP

#include <SFML/Graphics.hpp>
#include "EventInterface.hpp"
#include "Process.hpp"
#include "GameLogic.hpp"


class PlayerView : public Process {
    public:
        PlayerView();
        void init();
        void update(float &deltaTime);
        void update1(const EventInterface &event);
        void draw();
        void setContext(sf::RenderWindow* window);
        void setListener(EventManager *eventManager);
        void handleInput(float);
        bool isOpen();
        void setGameLogic(GameLogic& gameLogic);

    private: //methods
        void moveEventListener(const EventInterface& moveEvent);
    private: //vars and objs
        EventManager *m_eventManager;
        sf::RenderWindow* m_targetWindow;
        sf::Sprite m_character;
        sf::Texture m_charTexture;
        float m_speed;
        bool m_notReleased;
        GameLogic m_gameLogic;
};

#endif
