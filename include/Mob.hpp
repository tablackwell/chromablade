#ifndef MOB_HPP
#define MOB_HPP

#include "DynamicActor.hpp"

class Mob : public DynamicActor {
public:
    Mob(Color color);
    void attack(DynamicActor target);
};

#endif
