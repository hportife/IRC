//
// Created by Hoover Brent on 8/9/22.
//

#include "Parser.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>

// :Angel PRIVMSG Wiz :Hello are you receiving this message ?
// То КоммандЛайн должен выглядеть как:
// <PRIVMSG><Angel><Wiz><Hello are you receiving this message ?>

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

Parser::Parser(const std::string& input_commandLine) {
	//input_commandLine
    std::string	cmd;
    std::string arg;
    std::vector<std::string> command;

    std::string word;

	if (input_commandLine.find(':') == 0) {
		int pos = (int)input_commandLine.substr(1).find(':');
		if (pos != -1) {
			cmd = input_commandLine.substr(1, pos);
			arg = input_commandLine.substr(pos + 2);
//            std::stringstream sstream(cmd);

//			while (std::getline(sstream, word, ' ')) {
//				word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
//				if (!word.empty())
//                    command.push_back("<" + word + ">");
//			}
            command = split(cmd, ' ');
            for (std::vector<std::string>::iterator it = command.begin(); it != command.end(); ++it) {
                word = toUppercase(*it);
                word = word.substr(1, word.size() - 2);
                _type = verbToCommand(word);
                if (_type != UNDEFINED) {
                    std::string tmp = *command.begin();
                    std::vector<std::string>::iterator itr = std::find(command.begin(), command.end(), word);
                    int i = (int)std::distance(command.begin(), itr);
                    command[0] = command[i];
                    command[i] = tmp;
                }
			command.push_back("<" + arg + ">");
		}
		//else
		//std::string	cmd = input_commandLine.substr(1);

        }
        std::string str;
        for (std::vector<std::string>::iterator it = command.begin(); it != command.end(); ++it)
            str += *it;
        this->commandLine = CommandLine(str, (int)command.size());
	}



}

CommandLine Parser::getCommandLine() {
	return this->commandLine;
}

Parser::~Parser() {

}

