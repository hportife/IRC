//
// Created by Salena Alyce on 6/5/22.
//

#include "Connect.hpp"

const int buffSize = 128;
const int maxConnections = 1024;

Connect::Connect(unsigned short port, int socket) : port(port),
														m_socket(socket)
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
	char	buff[buffSize];
	createSocket();
	gethostname(&buff[0], buffSize);
	std::cout << "server started as: " << buff << std::endl;
	if (listen(m_socket, maxConnections) < 0)
	{
		std::cerr << "listen socket failure" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (fcntl(m_socket, F_SETFL, O_NONBLOCK) < 0)
	{
		std::cerr << "fcntl nonblock failure" << std::endl;
		exit(EXIT_FAILURE);
	}
}

void Connect::createSocket()
{
	struct	sockaddr_in addr = {};
	int		restrict = 1;

	bzero(&addr, sizeof addr);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	if ((m_socket = socket(addr.sin_family, SOCK_STREAM, 0)) == -1 ||
	setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &restrict, sizeof (int)) == -1 ||
	bind(m_socket, (struct sockaddr*)&addr, sizeof (addr)) == -1)
	{
		std::cerr << "socket created failed" << std::endl;
		exit(EXIT_FAILURE);
	}


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
