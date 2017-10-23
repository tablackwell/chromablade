#ifndef PROCESS_HPP
#define PROCESS_HPP

class Process {
public:
    enum States { UNINITIALIZED, RUNNING, PAUSED, SUCCESS, FAILED, ABORTED };

    Process() {}
    ~Process() {}

    virtual void initialize() { m_state = RUNNING; }
    virtual void update(float &deltaTime) = 0;
    virtual void postSuccess() {}
    virtual void postFailed() {}
    virtual void postAborted() {}

    //void Pause();
    //void Unpause();
    bool isDead() { return m_state = SUCCESS | FAILED | ABORTED; }
    bool setState(States state) { m_state = state; }
    int state() { return m_state; }

    bool hasChild() { return m_child; }
    Process *getChild() { return m_child; }

private:
    int m_state;
    Process *m_child;
};

#endif
