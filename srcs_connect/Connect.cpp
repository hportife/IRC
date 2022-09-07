//
// Created by Salena Alyce on 6/5/22.
//

#include "../includes/Connect.hpp"

const int buffSize = 128;
const int maxConnections = 1024;

Connect::Connect(unsigned short port, std::vector<pollfd> * polls) : _port(port), _polls(polls)
{}

Connect::~Connect() { stop(); }

void Connect::stop()
{
	std::vector<pollfd>::iterator iter;
	for (iter = _polls->begin(); iter != _polls->end(); ++iter)
	{
        close(iter->fd);
		remove(iter);
	}
}

void Connect::call_poll()
{
	if (poll(_polls->data(), _polls->size(), -1) == -1) {
		std::cerr << "poll failure" << std::endl;
		exit(EXIT_FAILURE);
	}
//	if (_polls[0].at(0).revents & POLLIN)
//		add();
}

void   Connect::remove_poolhup()
{
    for (iter = _polls->begin() + 1; iter != _polls->end(); ++iter) {
        if (iter->revents & POLLHUP) {
            //irc->remove(iter);
            this->remove(iter);
            break;
        }
    }
}


void Connect::start()
{
	init();

    _polls->push_back((pollfd){_socket, POLLIN, 0});
//    std::vector<pollfd>::iterator iter;
//    for (;;)
//    {
//        for (iter = _polls->begin() + 1; iter != _polls->end(); ++iter) {
//            if (iter->revents & POLLHUP) {
//                remove(iter);
//                break;
//            }
////            if (iter->revents & POLLOUT)
////                send_msg(iter->fd);
//
//            if (iter->revents & POLLIN)
//                receive(iter->fd);
//
////            if (!processed(iter->fd)) {
////                remove(iter);
////                break;
////            }
//        }
//    }

}



void Connect::init()
{
	char	buff[buffSize];
	createSocket();
	gethostname(&buff[0], buffSize);
	std::cout << "Server started as: " << buff << std::endl;
	if (listen(_socket, maxConnections) < 0)
	{
		std::cerr << "listen socket failure" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (fcntl(_socket, F_SETFL, O_NONBLOCK) < 0)
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
	addr.sin_port = htons(_port);
	if ((_socket = socket(addr.sin_family, SOCK_STREAM, 0)) == -1 ||
        setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &restrict, sizeof (int)) == -1 ||
        bind(_socket, (struct sockaddr*)&addr, sizeof (addr)) == -1)
	{
		std::cerr << "socket created failed" << std::endl;
		exit(EXIT_FAILURE);
	}


}

int Connect::add()
{
    struct sockaddr_in	clientaddr = {};
    socklen_t			len = sizeof(clientaddr);

    int client_socket = accept(_socket, (struct sockaddr *) &clientaddr, &len);

    if (fcntl(client_socket, F_SETFL, O_NONBLOCK) < 0) {
        std::cerr << "fcntl nonblock failure" << std::endl;
        exit(EXIT_FAILURE);
    }

    _polls->push_back((pollfd){client_socket, POLLIN | POLLOUT | POLLHUP, 0});

//    char host[buffSize];
//    if (getnameinfo((struct sockaddr *) &clientaddr, len, &host[0], buffSize, nullptr, 0, 0)) {
//        std::cerr << "getnameinfo failure" << std::endl;
//        exit(EXIT_FAILURE);
//    }

	return client_socket;
}

void Connect::remove(std::vector<pollfd>::iterator iter)
{
	close(iter->fd);
	_polls->erase(iter);
}

const std::string Connect::receive(int client_socket)
{
    char msg[buffSize];

    bzero(&msg, sizeof(msg));
    if (recv(client_socket, &msg, buffSize - 1, 0) < 0) {
        std::cerr << "recv() failure" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "msg = [" << msg << "]" << strlen(msg) << std::endl;

    if (strlen(msg) == 5)
    {
        std::cout << "send msg\n";
        send_msg(client_socket, "сообщение получено");
    }
//    if (strlen(msg) == 63)
//    {
//        std::cout << "send msg\n";
//        send_msg(client_socket, ":IRCat 375 salyce :- IRCat Message of the day - \r\n"
//                                ":IRCat 372 salyce :- ⠀⠀⠀⠀ ⣴⠉⡙⠳⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⠤⣚⡯⠴⢬⣱⡀⠀\r\n"
//                                ":IRCat 372 salyce :- ⠀⠀⠀⠀⢰⡇⣷⡌⢲⣄⡑⢢⡀⠀⠀⠀⠀⠀⢠⠾⢋⠔⣨⣴⣿⣷⡌⠇⡇⠀\r\n"
//                                ":IRCat 372 salyce :- ⠀⠀⠀⠀⢸⢹⣿⣿⣄⢻⣿⣷⣝⠷⢤⣤⣤⡶⢋⣴⣑⠟⠿⠿⠿⣿⣿⡀⡇⠀\r\n"
//                                ":IRCat 372 salyce :- ⠀⠀⠀⠀⢸⢸⣿⡄⢁⣸⣿⣋⣥⣶⣶⣶⣶⣶⣶⣿⣿⣶⣟⡁⠚⣿⣿⡇⡇⠀\r\n"
//                                ":IRCat 372 salyce :- ⢀⣠⡤⠤⠾⡘⠋⢀⣘⠋⠉⠉⠉⠉⢭⣭⣭⣭⣍⠉⢩⣭⠉⠉⠂⠙⠛⠃⣇⡀\r\n"
//                                ":IRCat 372 salyce :- ⠏⠀⠀⢿⣿⣷⡀⠀⢿⡄⠀⠀⠀⠀⠀⠀⢿⣿⣿⣿⣆⠀⢿⣇⠀⠀⠀⠀⠀⠀⠈⢱\r\n"
//                                ":IRCat 372 salyce :- ⣦⠀⠀⠈⢿⣿⣧⠀⠘⣿⠀⠀⠀⡀⠀⠀⠘⣿⣿⣿⣿⡆⠀⢻⡆⠀⠀⠀⠀⠀⠀⢸\r\n"
//                                ":IRCat 372 salyce :- ⢻⡄⠀⠀⠘⠛⠉⠂⠀⠙⠁⠀⣼⣧⠀⠀⠀⠈⠀⠀⠈⠙⠀⠘⠓⠀⠀⠀⠀⠀⢀⡟\r\n"
//                                ":IRCat 372 salyce :- ⠀⢳⡀⠀⠀⠀⠀⠀⠀⠀⠀⠸⠿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⣏⠀\r\n"
//                                ":IRCat 372 salyce :- ⠀⠀⠛⢶⢰⣶⢢⣤⣤⣄⠲⣶⠖⠀⣙⣀⠀⠀⠀⠤⢤⣀⣀⡀⣀⣠⣾⠟⡌⠀\r\n"
//                                ":IRCat 372 salyce :- ⠀⠀⠀⠘⢄⠃⣿⣿⣿⣿⠗⠀⠾⢿⣿⣿⣿⣿⣿⣿⣶⣶⣶⣶⠸⠟⣡⣤⡳⢦\r\n"
//                                ":IRCat 372 salyce :- ⠀⠀⠀⠀⠀⢻⡆⣙⡿⢷⣾⣿⣶⣾⣿⣿⣿⣿⣿⣿⣿⡿⠟⢡⣴⣾⣿⣿⣿⣦\r\n"
//                                ":IRCat 372 salyce :- ⠀⠀⠀⠀⠀⡼⢁⡟⣫⣶⣍⡙⠛⠛⠛⠛⠛⣽⡖⣉⣠⣶⣶⣌⠛⢿⣿⣿⣿⣿\r\n"
//                                ":IRCat 372 salyce :- ⠀⠀⠀⢀⠔⢡⢎⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⠹⣿⣿⣿\r\n"
//                                ":IRCat 372 salyce :- ⠀⢠⠖⢁⣴⡿⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⢹⣿⣿\r\n"
//                                ":IRCat 376 salyce :End of /MOTD command");
//    }

	return (msg);
}

int Connect::send_msg(int client_socket, const std::string& reply)
{

    if (send(client_socket, reply.c_str(), reply.size(), 0) == -1)
    {
        std::cerr << "send message to client failure\n";
        exit(EXIT_FAILURE);
    }
    std::cout << GREY_COL << reply << NO_COL;

	return 0;
}


