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
//    std::cout << "Привет! Чтобы запустить сервер, "
//                 "нужно ввести пароль, который будет"
//                 "использоваться для сервера:\n";
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
            //std::cout << "fd= " << iter->fd << " events= " << iter->events << " revents= " << iter->revents << std::endl;
            //sleep(1);
            if ((iter->revents & POLLHUP) || (iter->revents & POLLRDHUP)
            || (iter->revents & POLLNVAL) || (iter->revents & POLLERR)) {
                IRC_server->getConnect()->remove(iter);
                //std::cout << "----------11\n";
                break;
            }
            if (iter->revents & POLLIN) {
                //std::cout << IRC_server->getConnect()->receive(iter->fd) << std::endl;
                std::string msg = IRC_server->getConnect()->receive(iter->fd); //данный метод получает сообщение от получателя

                Parser parser(msg, iter->fd, IRC_server);


                if (parser.start_parser() != ERR_UNKNOWNCOMMAND)
                    parser.commandHandler();



                /// этим блоком проверяешь правильно ли распарсил, сожержимое
                /// таски-командлайна, если возникнут сомнения,
                /// но тогда сверху в условии закоментируй parser.commandHandler();,
                /// а так логи парса сделаны

//				parser.start_parser();
//
//                std::cout << "queue size = " << (int)parser.getAllCommandLine().size() << std::endl;
//                while (!parser.getAllCommandLine().empty()) {
//                    std::cout << parser.getOneCommandLine().getParameters() << std::endl;
//                    std::cout << parser.getOneCommandLine().getNumberOfParameter() << std::endl;
//                    std::cout << parser.getOneCommandLine().getOneParameter(1) << std::endl;
//                    std::cout << parser.getOneCommandLine().getOneParameter(2) << std::endl;
//                    std::cout << parser.getOneCommandLine().getOneParameter(3) << std::endl;
//                    std::cout << parser.getOneCommandLine().getOneParameter(4) << std::endl;
//                    std::cout << parser.getOneCommandLine().getOneParameter(5) << std::endl;
//                    std::cout << parser.getOneCommandLine().getOneParameter(6) << std::endl;
//                    parser.popOneCommandLine();
//                }


            }

//            if (!processed(iter->fd)) {
//                remove(iter);
//                break;
//            }
        }
    }
}