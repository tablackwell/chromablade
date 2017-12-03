#ifndef AIVIEW_HPP
#define AIVIEW_HPP

#include "DynamicActor.hpp"
#include <SFML/Graphics.hpp>

class AIView {
public:
    AIView(DynamicActor *actor, std::vector<Actor*>*rocks, std::vector<DynamicActor*> *mobs);
    void move(const sf::Vector2f& target);

private:
    DynamicActor *m_actor;
    std::vector<Actor*> *m_rocks;
    std::vector<DynamicActor*> *m_mobs;
};

#endif
