#ifndef PROCESS_HPP
#define PROCESS_HPP

/* Abstract class for processes to be handled by ProcessManager. */
class Process {
public:
    enum States { UNINITIALIZED, RUNNING, PAUSED, SUCCESS, FAILED, ABORTED };

    Process() : m_id(-1), m_state(UNINITIALIZED), m_child(0) {}
    ~Process() {}

    virtual void init() { m_state = RUNNING; }
    virtual void update(float &deltaTime) = 0;

    // TODO
    virtual void postSuccess() {}
    virtual void postFailed() {}
    virtual void postAborted() {}

    int getID() { return m_id; }
    void setID(int id) { m_id = id; }

    //void Pause();
    //void Unpause();
    bool isDead() { return (m_state == SUCCESS) || (m_state == FAILED) || 
        (m_state == ABORTED); }
    void setState(States state) { m_state = state; }
    int state() { return m_state; }

    bool hasChild() { return m_child; }
    Process *getChild() { return m_child; }

private:
    int m_id;           // pid given by ProcessManager
    int m_state;        // Process state
    Process *m_child;
};

#endif
