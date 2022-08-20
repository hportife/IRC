//
// Created by Hoover Brent on 8/9/22.
//

#include "Parser.hpp"
#include <iterator>
// :Angel PRIVMSG Wiz :Hello are you receiving this message ?
// То КоммандЛайн должен выглядеть как:
// <PRIVMSG><Angel><Wiz><Hello are you receiving this message ?>

CommandEnum verbToCommand(std::string &verb) {
    return CommandEnum(std::find(CommandNames, CommandNames + UNDEFINED, verb) - CommandNames);
}

std::string toUppercase(std::string const &original) {
    std::string uppercased;

    for (std::vector<char const>::iterator it = original.begin(); it != original.end(); ++it)
        uppercased += std::toupper(*it);
    return uppercased;
}

std::vector<std::string>    split(const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (getline (ss, item, delim)) {
        if (!item.empty())
            result.push_back("<" + item + ">");
    }

    return result;
}

Parser::Parser(std::string input_commandLine) {
    std::vector<std::string> command;
    std::string word;

    if (input_commandLine.find(':') == 0) {
        int pos = (int)input_commandLine.substr(1).find(':');
        if (pos != -1) {
			std::string	cmd = input_commandLine.substr(1, pos);
			std::string arg = input_commandLine.substr(pos + 2);

            command = split(cmd, ' ');
            for (std::vector<std::string>::iterator it = command.begin(); it != command.end(); ++it) {
                word = toUppercase(*it);
                word = word.substr(1, word.size() - 2);
                _type = verbToCommand(word);
                if (_type != UNDEFINED) {
                    int i = (int)std::string <std::string>iterator::distance(command.begin(), word);
                    std::string tmp = command[0];
                    command[0] = command[i];
                    command[i] = tmp;
                }
//                else
//                    throw FtException();

            }
			command.push_back("<" + arg + ">");
		}
		//else
		//std::string	cmd = input_commandLine.substr(1);


		this->commandLine = CommandLine(command, command.size());
	}



}


CommandLine Parser::getCommandLine() {
	return CommandLine(__cxx11::basic_string(), 0);
}

Parser::~Parser() {

}