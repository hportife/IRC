#include <iostream>
#include "includes/Serv.hpp"
#include "includes/Connect.hpp"

int main(){
    std::string pass;
    std::cout << "Привет! Чтобы запустить сервер, "
                 "нужно ввести пароль, который будет"
                 "использоваться для сервера:\n";
    std::cin >> pass;
    std::cout << "Сервер запускается...\n";
    Serv *IRC_server = new Serv(pass);

	unsigned short port = 6667;
	std::vector<pollfd>	_polls;
	std::vector<pollfd>::iterator iter;
	Connect *irc = new Connect(port, &_polls);
	irc->start();
    while (true){
		irc->call_poll();

		for (iter = _polls.begin() + 1; iter != _polls.end(); ++iter) {
			if (iter->revents & POLLHUP) {
				irc->remove(iter);
				break;
			}
//            if (iter->revents & POLLOUT)
//                send_msg(iter->fd);

			if (iter->revents & POLLIN)
				irc->receive(iter->fd);

//            if (!processed(iter->fd)) {
//                remove(iter);
//                break;
//            }
		}
    }
}