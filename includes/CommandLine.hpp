#ifndef IRC_COMMNADLINE_HPP
#define IRC_COMMNADLINE_HPP

#include <iostream>
#include "defines.hpp"

class CommandLine{
private:
    std::string parameters;
    int         number_of_params;

public:
    CommandLine();
    CommandLine(const std::string& cmdln, int number_of_params);
    ~CommandLine();

    int         getNumberOfParameter() const;
    std::string getOneParameter(int position);
    std::string getParameters() const;
};

#endif