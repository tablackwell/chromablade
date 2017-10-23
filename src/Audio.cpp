#include "Audio.hpp"

Audio::Audio() : Process() {
}

void Audio::init() {
    if (!m_title.openFromFile("../res/legendaryhero.ogg")) {
        return;
    }
    if (!m_buf.loadFromFile("../res/blip.wav")) {
        return;
    }
    m_sound.setBuffer(m_buf);

    playTitle();

    setState(RUNNING);
}

void Audio::update(float &deltaTime) {
}

void Audio::playTitle() {
    m_title.play();
}

void Audio::pauseTitle() {
    m_title.pause();
}

void Audio::stopTitle() {
    m_title.stop();
}
