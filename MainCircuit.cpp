#include <iostream>
#include "includes/Serv.hpp"
#include "includes/Connect.hpp"
#include "includes/Parser.hpp"

//c++ -std=c++98 ./srcs_connect/Connect.cpp MainCircuit.cpp Serv.cpp ./srv_inside/*.cpp tools/LogIdentifier.cpp Commando.cpp Parser.cpp

int main(int arc, char **arg){
    if (arc != 3) {
        std::cerr << "./ircserv <PORT> <PASSWORD>\n";
        exit(EXIT_FAILURE);
    } else if (strtol(arg[1], NULL, 10) <= 1024
               || strtol(arg[1], NULL, 10) > 65535) {
        std::cerr << "Invalid <PORT>\n";
        exit(EXIT_FAILURE);
    }
    unsigned short port = atoi(arg[1]);
    std::cout << "Сервер запускается...\n";
    Serv *IRC_server = new Serv(arg[2], port);

    std::vector<pollfd>::iterator iter;
    IRC_server->getConnect()->start();
    while (true){
        IRC_server->getConnect()->call_poll();
        if (IRC_server->getPolls()->at(0).revents & POLLIN)
            IRC_server->getCommando()->UserConnect(
                    IRC_server->getConnect()->add()
            );

        IRC_server->getConnect()->remove_poolhup();

        for (iter = IRC_server->getPolls()->begin() + 1;
            iter != IRC_server->getPolls()->end(); ++iter) {
            //std::cout << " fd=" << iter->fd << " ev= " << iter->events << " rev= " << iter->revents << std::endl;
            if ((iter->revents & POLLHUP) || (iter->revents & POLLNVAL) || (iter->revents & POLLERR)
            //)
               || (iter->revents & POLLRDHUP))
            {
                IRC_server->getConnect()->remove(iter);
                break;
            }
            if (iter->revents & POLLIN) {
                std::string msg = IRC_server->getConnect()->receive(iter->fd); //данный метод получает сообщение от получателя
                Parser parser(msg, iter->fd, IRC_server);
                if (parser.start_parser() != ERR_UNKNOWNCOMMAND)
                    parser.commandHandler();

                /// этим блоком проверяешь правильно ли распарсил, сожержимое
                /// таски-командлайна, если возникнут сомнения,
                /// но тогда сверху в условии закоментируй parser.commandHandler();,
                /// а так логи парса сделаны

            }
        }
    }
}