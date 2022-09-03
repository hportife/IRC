//
// Created by user1 on 26.06.2022.
//

//c++ -std=c++98 ../sr

#include "connectTest.hpp"
#include "../srcs_connect/Connect.hpp"

int main()
{
    std::cout << "IRC" << std::endl;
    unsigned short port = 6667;
	std::vector<pollfd>	_polls;
	std::vector<pollfd>::iterator iter;

    Connect *irc = new Connect(port, &_polls);
    irc->start();


	for (;;)
	{
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


    irc->stop();



    return (0);


}


