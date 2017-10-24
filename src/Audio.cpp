#include "Audio.hpp"

// Initialize Process variables 
Audio::Audio() : Process() {
}

void Audio::init() {
    // Load title screen music
    if (!m_title.openFromFile("../res/legendaryhero.ogg")) {
        return;
    }

    // Example for loading sound effect
    if (!m_buf.loadFromFile("../res/blip.wav")) {
        return;
    }
    m_sound.setBuffer(m_buf);

    // Start title screen music
    playTitle();

    setState(Process::RUNNING);
}

void Audio::update(float &deltaTime) {
    // TODO: accommodate for buffering?
}

/* Media controls for title screen music */
void Audio::playTitle() {
    m_title.play();
}
void Audio::pauseTitle() {
    m_title.pause();
}
void Audio::stopTitle() {
    m_title.stop();
}
