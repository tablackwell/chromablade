#include "Audio.hpp"

// Initialize Process variables
Audio::Audio() : Process() {
}

void Audio::init() {
    // Load title screen music
    if (!m_dungeon.openFromFile("../res/music/ruins.ogg")) {
        return;
    }


    // Start title screen music
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

/* Media controls for dungeon music */
void Audio::playDungeon() {
    m_dungeon.play();
}
void Audio::pauseDungeon() {
    m_dungeon.pause();
}
void Audio::stopDungeon() {
    m_dungeon.stop();
}
