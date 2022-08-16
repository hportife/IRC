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

Parser::Parser(std::string input_commandLine) {
	std::string commands[] = {"PASS", "USER", "NICK", "PONG", "PRIVMSG", "NOTICE", "JOIN",
							  "OPER", "QUIT", "KILL","KICK", "PING", "LIST", "WHO", "PART"};
	//input_commandLine
	if (input_commandLine.find(':') == 0) {
		int pos = (int)input_commandLine.substr(1).find(':');
		if (pos != -1) {
			std::string	cmd = input_commandLine.substr(1, pos);
			std::string arg = input_commandLine.substr(20);
			std::vector<std::string> command;

			std::stringstream sstream(cmd);
			std::string word;
			while (std::getline(sstream, word, ' ')){
				word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
				command.push_back("<" + word + ">");
			}
			command.push_back("<" + arg + ">");
		}
		//else
		//std::string	cmd = input_commandLine.substr(1);


		this->commandLine();
	}



}

//std::string Parser::getCommand() {
//    std::string commands[] = {"PASS", "USER", "NICK", "PONG", "PRIVMSG", "NOTICE", "JOIN", "OPER", "QUIT", "KILL", "KICK", "PING", "LIST", "WHO", "PART"};
//
//    return std::string();
//}





CommandLine Parser::getCommandLine() {
	return CommandLine(__cxx11::basic_string(), 0);
}

Parser::~Parser() {

}