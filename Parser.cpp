//
// Created by Hoover Brent on 8/9/22.
//

#include "includes/Parser.hpp"
#include "includes/LogIdentifier.hpp"

///////utils

std::string trim(std::string s)
{
    std::string::iterator start = s.begin();
    while (start != s.end() && std::isspace(*start)) {
        start++;
    }

    std::string ::iterator end = s.end();
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
        if (!trim(item).empty())
            result.push_back(trim(item));
    }

    return result;
}

CommandEnum verbToCommand(std::string &verb) {
    return CommandEnum(std::find(CommandNames, CommandNames + UNDEFINED, verb) - CommandNames);
}

std::string toUppercase(std::string original) {
    std::string uppercased;

    for (std::string::iterator it = original.begin(); it != original.end(); ++it) {
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

///////-------------------------------------------------------------------------------------------------------

Parser::Parser(const std::string& input_commandLine, int id_user, Serv *serv) {
    this->id_user = id_user;
    this->serv = serv;
    this->_countCommand = 0;

    ///use this if find "\r\n";
    _input_commandLINES = split(input_commandLine, '\r');
}

int	Parser::start_parser() {
	char const  *cmd;

	std::vector<std::string> channels;

	std::vector<std::string> command;

	std::vector<std::vector<std::string> > tasks;

	std::vector<std::string> keys_users_modes;

	std::string input_commandLine;

	for (std::vector<std::string>::iterator command_iter = _input_commandLINES.begin(); command_iter != _input_commandLINES.end(); ++command_iter) {
        ///clear whitespaces
        input_commandLine = trim(*command_iter); // must have

		std::cout << LogIdentifier::info("Была подана строка ") + input_commandLine << std::endl;

        /// detect msg

        std::string msg; //must have

        int pos;

        detect_msg(&input_commandLine, &msg, &pos);
        /////-----------------

        //// detect arguments and commands
        detect_args_and_cmds(&input_commandLine, &pos, &channels, &keys_users_modes, &command, &cmd);
        //////////-------------------

        ////define command

        define_command(&command);

		if (_countCommand < 1) {
			std::cout << LogIdentifier::error("Неизвестная команда ") + command[0] << std::endl;
			return ERR_UNKNOWNCOMMAND;
		}
        ///----------------

        ////build commandLine with args
        build_commandLine_with_args(command, channels, keys_users_modes, msg);

        ////---------------------------

        ////build commandLine without args
        if (channels.empty() and keys_users_modes.empty())
            build_commandLine_no_args(command, msg);
        ////-----------------------
    }
	return RPL_RIGHTCMD;
}

void    Parser::detect_msg(std::string *input_commandLine, std::string *msg, int *pos) {
    if (input_commandLine->find(':') == 0)
        *input_commandLine = input_commandLine->substr(1);

    *pos = (int)input_commandLine->find(':');

    if (*pos != -1) {
        *msg = input_commandLine->substr(*pos);
        *input_commandLine = input_commandLine->substr(0, *pos);
    }
}

void    Parser::detect_args_and_cmds(std::string *input_commandLine, int *pos, std::vector<std::string> *channels,
                                     std::vector<std::string> *keys_users_modes, std::vector<std::string> *command, char const **cmd) {
    if ((int)input_commandLine->find(',') != -1) {
        if ((int)input_commandLine->find('&') != -1 or (int)input_commandLine->find('#') != -1) {
            *channels = find_channel(*input_commandLine, pos);
            if ((int)input_commandLine->find(',', *pos) != -1)
                *keys_users_modes = split(input_commandLine->substr(*pos), ',');
            else
                *keys_users_modes = split(input_commandLine->substr(*pos), ',');
            if ((int)input_commandLine->find('#') > (int)input_commandLine->find('&') and (int)input_commandLine->find('&') != -1)
                *input_commandLine = input_commandLine->substr(0, input_commandLine->find('&'));
            else
                *input_commandLine = input_commandLine->substr(0, input_commandLine->find('#'));
            *command = split(*input_commandLine, ' ');
        } else
            comma_find(*input_commandLine, keys_users_modes, command);
    } else {
        if ((int)input_commandLine->find(" +") != -1) {
            *pos = (int)input_commandLine->find(" +");
            *keys_users_modes = mode_find(input_commandLine->substr(*pos + 2), "+");
        }
        if ((int)input_commandLine->find(" -") != -1) {
            *pos = (int)input_commandLine->find(" -");
            *keys_users_modes = mode_find(input_commandLine->substr(*pos + 2), "-");
        }
        if ((int)input_commandLine->find(" -") != -1 or (int)input_commandLine->find(" +") != -1) {
            *cmd = input_commandLine->substr(*pos + 2).c_str();
            while (**cmd != ' ' and *cmd)
                (*cmd)++;
            *input_commandLine = input_commandLine->substr(0, *pos) + *cmd;
        }
        *command = split(*input_commandLine, ' ');
    }
}

void    Parser::define_command(std::vector<std::string> *command) {
    for (std::vector<std::string>::iterator it = command->begin(); it != command->end(); ++it)
    {
        std::string word = toUppercase(*it);
        _type = verbToCommand(word);
        if (_type != UNDEFINED)
        {
            std::string tmp = *command->begin();
            std::vector<std::string>::iterator itr = std::find(command->begin(), command->end(), *it);
            int i = (int)std::distance(command->begin(), itr);
            (*command)[0] = word;
            if (i != 0)
                (*command)[i] = tmp;
            _countCommand++;
		}
    }
}

void    Parser::build_commandLine_with_args(const std::vector<std::string>& command, const std::vector<std::string>& channels,
                                  const std::vector<std::string>& keys_users_modes, const std::string& msg) {
    int n;

    if (!channels.empty())
        n = (int)channels.size();
    else
        n = (int)keys_users_modes.size();

    for (int i = 0; i < n; ++i) {
        std::vector<std::string> tmp = command;
		std::cout << LogIdentifier::info("Была подана команда ") + tmp[0] << std::endl;
		if (!channels.empty() and i < (int)channels.size())
			tmp.push_back(channels[i]);
        if (!keys_users_modes.empty() and i < (int)keys_users_modes.size())
			tmp.push_back(keys_users_modes[i]);
        if (!msg.empty())
			tmp.push_back(msg);
        std::string str;
		for (std::vector<std::string>::iterator it = tmp.begin(); it != tmp.end(); ++it) {
			if ((*it)[0] == ':')
				std::cout << LogIdentifier::info("с сообщением ") + (*it).substr(1) << std::endl;
			else if ((*it)[0] == '#' or (*it)[0] == '&')
				std::cout << LogIdentifier::info("с названием комнаты ") + *it << std::endl;
			else if (it != tmp.begin())
				std::cout << LogIdentifier::info("с аргументом ") + *it << std::endl;
			str += "<" + *it + ">";
        }
        this->_commandLine = CommandLine(str, (int)tmp.size());
        this->_tasks.push(_commandLine);
    }
}

void Parser::build_commandLine_no_args(std::vector<std::string> command, const std::string& msg) {
	std::cout << LogIdentifier::info("Была подана команда ") + command[0] << std::endl;
	if (!msg.empty())
		command.push_back(msg);
    std::string str;
    for (std::vector<std::string>::iterator it = command.begin(); it != command.end(); ++it) {
		if ((*it)[0] == ':')
			std::cout << LogIdentifier::info("с сообщением ") + (*it).substr(1) << std::endl;
		else if ((*it)[0] == '#' or (*it)[0] == '&')
			std::cout << LogIdentifier::info("с названием комнаты ") + *it << std::endl;
		else if (it != command.begin())
			std::cout << LogIdentifier::info("с аргументом ") + *it << std::endl;
		str += "<" + *it + ">";
    }
    this->_commandLine = CommandLine(str, (int)command.size());
    this->_tasks.push(_commandLine);
}

void Parser::commandHandler() {
    std::string word;

	while (!this->getAllCommandLine().empty()) {
		word = toUppercase(this->getOneCommandLine().getOneParameter(1));
		switch (verbToCommand(word)) {
			case INVITE:
				if (this->getOneCommandLine().getNumberOfParameter() == 3)
					this->serv->getCommando()->InviteCmd(id_user, this->getOneCommandLine().getOneParameter(3));
				else
					this->serv->getCommando()->InviteCmd(id_user, this->getOneCommandLine().getOneParameter(4));
				break;
			case MODE:
				if (this->getOneCommandLine().getOneParameter(3)[1] == 'l')
					this->serv->getCommando()->ModeLCmd(this->getOneCommandLine().getOneParameter(2),
														std::atoi(this->getOneCommandLine().getOneParameter(4).c_str()));
				else if (this->getOneCommandLine().getOneParameter(3)[1] == 'o')
					this->serv->getCommando()->ModeOCmd(this->getOneCommandLine().getOneParameter(2), this->serv->getOpers()->front(),
														this->getOneCommandLine().getOneParameter(4), true); ////rewrite!!!!!
				break;
			case AWAY:
				this->serv->getCommando()->AwayCmd(this->getOneCommandLine().getOneParameter(2), this->getOneCommandLine().getOneParameter(3));
				break;
			case PASS:
				this->serv->setPassword(this->getOneCommandLine().getOneParameter(2)); //?
				break;
			case USER:
				this->serv->getCommando()->UserCmd(id_user, this->getOneCommandLine().getOneParameter(2), this->getOneCommandLine().getOneParameter(3));
				break;
			case NICK:
				if (this->getOneCommandLine().getNumberOfParameter() < 3)
					this->serv->getCommando()->NickCmd(id_user, this->getOneCommandLine().getOneParameter(2));
				else
					this->serv->getCommando()->NickCmd(this->getOneCommandLine().getOneParameter(2), this->getOneCommandLine().getOneParameter(2));
				break;
			case PING:
//                    handlePing(command);
				break;
			case PONG:
//                    handlePong(command);
				break;
			case QUIT:
				this->serv->getCommando()->QuitCmd(id_user, this->getOneCommandLine().getOneParameter(2));
				break;
			case PRIVMSG:
				this->serv->getCommando()->PrivmsgToChannel(this->getOneCommandLine().getOneParameter(2), this->getOneCommandLine().getOneParameter(3));
				break;
			case NOTICE:
				this->serv->getCommando()->NoticeCmd(id_user, this->getOneCommandLine().getOneParameter(3));
				break;
			case JOIN:
				this->serv->getCommando()->JoinCmd(id_user, this->getOneCommandLine().getOneParameter(2));
				break;
			case OPER:
				this->serv->getCommando()->OperCmd(this->getOneCommandLine().getOneParameter(2), this->getOneCommandLine().getOneParameter(3));
				break;
			case KILL:
//                    handleKill(command);
				break;
			case KICK:
				this->serv->getCommando()->KickCmd(id_user, id_user
						/* ???this->getOneCommandLine().getOneParameter(3) ???*/, this->getOneCommandLine().getOneParameter(2));
				break;
			case LIST:
//                    logStream << "LIST method is not implemented" << std::endl;
//                    logger.logMessage(logStream, DEV);
				break;
			case PART:
//                    handlePart(command);
				break;
			case WHO:
//                    handleWho(command);
				break;
			default:
				break;
		}
		this->popOneCommandLine();
    }
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

//void exec_certain_command(, std::string command, std::string arg1, std::string arg2, std::string arg2) {
//    switch (command) {
//        case expression:
////add commanline
//    }
//}
