#ifndef PROCESSMANAGER_HPP
#define PROCESSMANAGER_HPP

#include <list>
#include "Process.hpp"

class ProcessManager {
public:
    ProcessManager();
    ~ProcessManager();

    void update(float &deltaTime);
    void attachProcess(Process *p);
    void abortAll();
    void removeProcess(Process *p);

private:
    std::list<Process*> m_procs;
};

#endif
