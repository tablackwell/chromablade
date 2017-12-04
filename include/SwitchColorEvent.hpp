#ifndef SWITCHCOLOREVENT_HPP
#define SWITCHCOLOREVENT_HPP

#include "EventInterface.hpp"
#include "EventType.hpp"
#include <SFML/Graphics.hpp>


/*
 * A SWITCHCOLOREvent is generated when the character or enemy SWITCHCOLORs.
 */
class SwitchColorEvent : public EventInterface {
    public:
        SwitchColorEvent(sf::Color col) { m_color = col; m_type = switchColorEvent; }
        const sf::Color getColor(void) const { return m_color; }

    private:

    private: // event data
        sf::Color m_color;
};

#endif
