#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <SFML/Audio.hpp>
#include "Process.hpp"

/* Handles playing sf::Sound and sf::Music. */
class Audio : public Process {
public:
    Audio();
    void init();
    void update(float &deltaTime);

    void playTitle();
    void pauseTitle();
    void stopTitle();

    void playSound();

private:
    sf::Music m_title;

    // TODO: add sound effects
    sf::SoundBuffer m_buf;
    sf::Sound m_sound;
};

#endif
