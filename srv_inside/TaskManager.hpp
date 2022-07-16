
#ifndef IRC_TASKMANAGER_HPP
#define IRC_TASKMANAGER_HPP

#include "CommandLine.hpp"
#include <queue>

class TaskManager {
private:
    std::queue<std::string> tasks;
public:
    TaskManager();
};


#endif //IRC_TASKMANAGER_HPP
