#ifndef AIVIEW_HPP
#define AIVIEW_HPP

#include "DynamicActor.hpp"

class AIView {
public:
    AIView(DynamicActor *actor);
    void setSpawnPositions(std::vector<Actor*> rocks, std::vector<DynamicActor*> mobs);

private:
    DynamicActor *m_actor;
    std::vector<Actor*> m_rocks;
    std::vector<DynamicActor*> m_mobs;
};

#endif
