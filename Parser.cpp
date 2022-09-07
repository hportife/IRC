//
// Created by Hoover Brent on 8/9/22.
//

#include "includes/Parser.hpp"
#include "includes/LogIdentifier.hpp"

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

    for (int i = 0; i < (int)str.size(); ++i) {
        std::string new_str;
        if ((str[i] == '#' or str[i] == '&')) {
            while (str[i] != ',' and str[i] != ' ' and str[i]) {
                new_str += str[i++];
                *pos = i;
            }
            result.push_back(new_str);
        }
    }
    return result;
}

void    comma_find(std::string cmd, std::vector<std::string> *users, std::vector<std::string> *command) {
    int space = (int)cmd.rfind(' ',cmd.find(','));
    *users = split(cmd.substr(space), ',');
    cmd = cmd.substr(0, space);
    *command = split(cmd, ' ');
}

std::vector<std::string>    mode_find(std::string str, const std::string& sign) {
    std::vector<std::string>    result;

    for (int i = 0; i < (int)str.size(); ++i) {
        while (strchr("opsitnbvmlk", str[i]) and str[i]) {
            std::string new_str;
            new_str += sign + str[i++];
            result.push_back(new_str);
        }
        break;
    }
    return result;
}

Parser::Parser(std::string input_commandLine) {
    char const  *cmd;

    std::string msg; //must have

    std::vector<std::string> channels;

    std::vector<std::string> command;

    std::vector<std::vector<std::string> > tasks;

    std::string word;

    std::vector<std::string> keys_users_modes;

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
                keys_users_modes = split(input_commandLine.substr(pos), ',');
            else
                keys_users_modes = split(input_commandLine.substr(pos), ',');
            if ((int)input_commandLine.find('#') > (int)input_commandLine.find('&') and (int)input_commandLine.find('&') != -1)
                input_commandLine = input_commandLine.substr(0, input_commandLine.find('&'));
            else
                input_commandLine = input_commandLine.substr(0, input_commandLine.find('#'));
            command = split(input_commandLine, ' ');
        } else
            comma_find(input_commandLine, &keys_users_modes, &command);
    } else {
        if ((int)input_commandLine.find(" +") != -1) {
            pos = (int)input_commandLine.find(" +");
            keys_users_modes = mode_find(input_commandLine.substr(pos + 2), "+");
        }
        if ((int)input_commandLine.find(" -") != -1) {
            pos = (int)input_commandLine.find(" -");
            keys_users_modes = mode_find(input_commandLine.substr(pos + 2), "-");
        }
        if ((int)input_commandLine.find(" -") != -1 or (int)input_commandLine.find(" +") != -1) {
            cmd = input_commandLine.substr(pos + 2).c_str();
            while (*cmd != ' ' and *cmd)
                cmd++;
            input_commandLine = input_commandLine.substr(0, pos) + cmd;
        }
        command = split(input_commandLine, ' ');
    }

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

    int n;

    if (!channels.empty())
        n = (int)channels.size();
    else
        n = (int)keys_users_modes.size();

    for (int i = 0; i < n; ++i) {
        std::vector<std::string> tmp = command;
        if (!channels.empty() and i < (int)channels.size())
            tmp.push_back(channels[i]);
        if (!keys_users_modes.empty() and i < (int)keys_users_modes.size())
            tmp.push_back(keys_users_modes[i]);
        if (!msg.empty())
            tmp.push_back(msg);
        std::string str;
        for (std::vector<std::string>::iterator it = tmp.begin(); it != tmp.end(); ++it) {
                str += "<" + *it + ">";
        }
        this->_commandLine = CommandLine(str, (int)tmp.size());
        this->_tasks.push(_commandLine);
    }

    if (channels.empty() and keys_users_modes.empty()) {
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