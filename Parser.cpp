//
// Created by Hoover Brent on 8/9/22.
//

#include "Parser.hpp"
#include <iterator>
// :Angel PRIVMSG Wiz :Hello are you receiving this message ?
// То КоммандЛайн должен выглядеть как:
// <PRIVMSG><Angel><Wiz><Hello are you receiving this message ?>

std::vector<std::string>    split(const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (getline (ss, item, delim)) {
        if (!item.empty())
            result.push_back(item);
    }

    return result;
}

CommandEnum verbToCommand(std::string &verb) {
    return CommandEnum(std::find(CommandNames, CommandNames + UNDEFINED, verb) - CommandNames);
}

std::string toUppercase(std::string const &original) {
    std::string uppercased;

    for (std::vector<char const>::iterator it = original.begin(); it != original.end(); ++it) {
        uppercased += std::toupper(*it);
    }
    return uppercased;
}

Parser::Parser(std::string input_commandLine) {
	//input_commandLine
    std::string	cmd;
    std::string msg;
    std::vector<std::string> command;

    std::string word;

	if (input_commandLine.find(':') == 0)
        input_commandLine = input_commandLine.substr(1);
    
    int pos = (int)input_commandLine.find(':');
    if (pos != -1) {
        cmd = input_commandLine.substr(0, pos);
        msg = input_commandLine.substr(pos + 1);
        command = split(cmd, ' ');
    } else
        command = split(input_commandLine, ' ');
    for (std::vector<std::string>::iterator it = command.begin(); it != command.end(); ++it)
    {
        word = toUppercase(*it);
        _type = verbToCommand(word);
        if (_type != UNDEFINED)
        {
            std::string tmp = *command.begin();
            std::vector<std::string>::iterator itr = std::find(command.begin(), command.end(), *it);
            int i = (int)std::distance(command.begin(), itr); //?
            command[0] = word;
            if (i != 0)
                command[i] = tmp;
        }
    }
    if (pos != -1)
        command.push_back(msg);
    std::string str;
    for (std::vector<std::string>::iterator it = command.begin(); it != command.end(); ++it)
        str += "<" + *it + ">";
    this->_commandLine = CommandLine(str, (int)command.size());
    this->_tasks.push(_commandLine);
}

CommandLine Parser::getCommandLine() {
	return this->_tasks.front();
}

Parser::~Parser() {

}