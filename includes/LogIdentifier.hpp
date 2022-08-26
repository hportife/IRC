#ifndef IRC_LOGIDENTIFIER_HPP
#define IRC_LOGIDENTIFIER_HPP

//#define RED     \033[31m
//#define GREEN   \033[32m
//#define YELLOW  \033[33m
//#define UNDERLINE \033[4m
//#define FATTEXT   \033[1m

#include <iostream>

class LogIdentifier
{
public:
    LogIdentifier();
    ~LogIdentifier();

    static std::string debug();
    static std::string error();
    static std::string info();
    static std::string debug(std::string from);
    static std::string error(std::string from);
    static std::string info(std::string from);
};

#endif