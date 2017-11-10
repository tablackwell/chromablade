#ifndef PLAYERVIEW_HPP
#define PLAYERVIEW_HPP

#include <SFML/Graphics.hpp>
#include "EventInterface.hpp"
#include "Process.hpp"
#include "GameLogic.hpp"
#include "Title.hpp"
#include "TileMap.hpp"

class ChromaBlade; // Forward declaration of class ChromaBlade, so that we can declare a pointer to ChromaBlade in PlayerView


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
        void setGameLogic(GameLogic* gameLogic);
        void setGameApplication(ChromaBlade* game);

    private: //methods
        void moveEventListener(const EventInterface& moveEvent);
    private: //vars and objs
        EventManager *m_eventManager;
        sf::RenderWindow* m_window;
        sf::Sprite m_character;
        sf::Texture m_charTexture;
        float m_speed;
        GameLogic* m_gameLogic;
        ChromaBlade* m_game;
        TileMap m_map;
        TileMap m_overlay;
        Title m_title;

};

#endif
