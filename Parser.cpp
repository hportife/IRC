//
// Created by Hoover Brent on 8/9/22.
//

#include "Parser.hpp"
//#include <iterator> ?
#include "tools/LogIdentifier.hpp"

// :Angel PRIVMSG Wiz :Hello are you receiving this message ?
// То КоммандЛайн должен выглядеть как:
// <PRIVMSG><Angel><Wiz><Hello are you receiving this message ?>

std::string trim(const std::string &s)
{
    std::vector<char const>::iterator start = s.begin();
    while (start != s.end() && std::isspace(*start)) {
        start++;
    }

    std::vector<char const>::iterator end = s.end();
    do {
        end--;
    } while (std::distance(start, end) > 0 && std::isspace(*end));

    return std::string(start, end + 1);
}

std::vector<std::string>    split(const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (getline (ss, item, delim)) {
        if (!item.empty())
            result.push_back(trim(item));
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

std::vector<std::string>    find_channel(std::string str, int *pos) {
    std::vector<std::string>    result;

    for (int i = 0; i < str.size(); ++i) {
        std::string new_str;
        if ((str[i] == '#' or str[i] == '&')) {
            while (str[i] != ',' and str[i] != ' ') {
                new_str += str[i++];
                *pos = i;
            }
            result.push_back(new_str);
        }
    }
    return result;
}

void    comma_find(std::string cmd, std::vector<std::string> *users, std::vector<std::string> *command) {
    int com = (int)cmd.find(',');
    if (com != -1) {
        int space = (int)cmd.rfind(' ',com);
        *users = split(cmd.substr(space), ',');
        cmd = cmd.substr(0, space);
        *command = split(cmd, ' ');
    } else
        *command = split(cmd, ' ');
}



Parser::Parser(std::string input_commandLine) {
	//input_commandLine
    // :Angel PrIVMSg Wiz, Den,Jax :Hello are you receiving this message ?
    // :Angel PRIVMSG Wiz :Hello are you receiving this message ?

//  JOIN #foobar                      // вход на канал #foobar.
//  JOIN &foo fubar                   // вход на канал &foo, используя ключ "fubar".
//  JOIN #foo,&bar fubar              // вход на канал #foo, используя ключ "fubar" и на канал &bar без использования ключа.
//  JOIN #foo,#bar fubar,foobar       // вход на канал #foo, используя ключ "fubar" и на канал #bar, используя ключ "foobar".
//  JOIN #foo,#bar

    std::string	cmd; //?

    std::string msg; //must have

    std::vector<std::string> channels;

    std::vector<std::string> command;


    std::vector<std::vector<std::string> > tasks;

    std::string word;

    std::vector<std::string> keys;


    std::vector<std::string> users;

    this->_countCommand = 0;


    input_commandLine = trim(input_commandLine); // must have

    if (input_commandLine.find(':') == 0) // must have
        input_commandLine = input_commandLine.substr(1);

    int pos = (int)input_commandLine.find(':'); // must have

    if (pos != -1) {
        msg = input_commandLine.substr(pos + 1);
        input_commandLine = input_commandLine.substr(0, pos);
    }

    if ((int)input_commandLine.find(',') != -1) {
        if ((int)input_commandLine.find('&') != -1 or (int)input_commandLine.find('#') != -1) {
            channels = find_channel(input_commandLine, &pos);
            if ((int)input_commandLine.find(',', pos) != -1)
                keys = split(input_commandLine.substr(pos), ',');
            if (strchr(input_commandLine.c_str(), '&'))
                input_commandLine = input_commandLine.substr(0, input_commandLine.find('&'));
            else
                input_commandLine = input_commandLine.substr(0, input_commandLine.find('#'));
            command = split(input_commandLine, ' ');
        } else
            comma_find(input_commandLine, &users, &command);

    }


    /*
    if (pos != -1) {
        cmd = input_commandLine.substr(0, pos);
        msg = input_commandLine.substr(pos + 1);
//        int channel = (int)cmd.find("&#");
        comma_find(cmd, &users, &command);
    } else
        comma_find(input_commandLine, &users, &command);

    for (std::vector<std::string>::iterator it = command.begin(); it != command.end(); ++it)
    {
        word = toUppercase(*it);
        _type = verbToCommand(word);
        if (_type != UNDEFINED)
        {
            std::string tmp = *command.begin();
            std::vector<std::string>::iterator itr = std::find(command.begin(), command.end(), *it);
            int i = (int)std::distance(command.begin(), itr);
            command[0] = word;
            if (i != 0)
                command[i] = tmp;
            _countCommand++;
        }
    }

    for (std::vector<std::string>::iterator it = users.begin(); it != users.end(); ++it) {
        std::vector<std::string> tmp = command;
        tmp.push_back(*it);
        if (!msg.empty())
            tmp.push_back(msg);
        std::string str;
        for (std::vector<std::string>::iterator it = tmp.begin(); it != tmp.end(); ++it)
            str += "<" + *it + ">";
        this->_commandLine = CommandLine(str, (int)tmp.size());
        this->_tasks.push(_commandLine);
//        tmp.clear(); //?
//        str.clear();
    }

    if (users.empty()) {
        if (!msg.empty())
            command.push_back(msg);
        std::string str;
        for (std::vector<std::string>::iterator it = command.begin(); it != command.end(); ++it)
            str += "<" + *it + ">";
        this->_commandLine = CommandLine(str, (int)command.size());
        this->_tasks.push(_commandLine);
    }
    if (_countCommand < 1)
        std::cout << LogIdentifier::error("<command> :Unknown command") << std::endl;
*/

}

CommandLine Parser::getOneCommandLine() {
	return getAllCommandLine().front();
}

std::queue<CommandLine> Parser::getAllCommandLine() {
    return this->_tasks;
}

void    Parser::popOneCommandLine() {
    this->_tasks.pop();
}

Parser::~Parser() {

}