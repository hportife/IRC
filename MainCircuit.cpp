#include <iostream>
#include "includes/Serv.hpp"
#include "includes/Connect.hpp"

//c++ -std=c++98 ./srcs_connect/*.cpp MainCircuit.cpp Serv.cpp ./srv_inside/RoomStorage.cpp ./srv_inside/Room.cpp ./srv_inside/User.cpp ./srv_inside/UserStorage.cpp

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
    Serv *IRC_server = new Serv(arg[1], port);

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
			if (iter->revents & POLLHUP) {
                IRC_server->getConnect()->remove(iter);
				break;
			}
			if (iter->revents & POLLIN)
                IRC_server->getConnect()->receive(iter->fd);

//            if (!processed(iter->fd)) {
//                remove(iter);
//                break;
//            }
		}
    }
}