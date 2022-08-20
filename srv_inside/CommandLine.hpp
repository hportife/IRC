#ifndef IRC_COMMNADLINE_HPP
#define IRC_COMMNADLINE_HPP

#define ISNOCOMMANT 2000
#define ISCOMMAND   2001

#include <iostream>

class CommandLine{
private:
    std::string parameters;
    int         number_of_params;

public:
    CommandLine();
    CommandLine(std::string cmdln, int number_of_params);
    ~CommandLine();

    int         getNumberOfParameter() const;
    std::string getOneParameter(int position);
    std::string getParameters();
};

#endif