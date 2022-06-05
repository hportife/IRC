//
// Created by Salena Alyce on 6/5/22.
//

#include "Connect.hpp"

Connect::Connect(unsigned short port, int socket) : port(port),
														socket(socket)
{}

Connect::~Connect() { stop(); }

void Connect::stop()
{
	std::vector<pollfd>::iterator iter;
	for (iter = polls_fd.begin(); iter != polls_fd.end(); ++iter)
	{
		remove(iter);
	}
}

void Connect::start()
{
	init();

}

void Connect::init()
{

}

void Connect::createSocket()
{
	struct sockaddr_in addr = {};

	bzero(&addr, sizeof addr);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	if ((m_socket = socket(addr.sin_family, SOCK_STREAM, 0)) == -1)


}

int Connect::add()
{
	return 0;
}

void Connect::remove(std::vector<pollfd>::iterator iter)
{
	close(iter->fd);
	polls_fd.erase(iter);
}

int Connect::receive(int)
{
	return 0;
}

int Connect::send_msg(int)
{
	return 0;
}
