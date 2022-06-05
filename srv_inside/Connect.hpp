//
// Created by Salena Alyce on 6/5/22.
//

#ifndef IRC_CONNECT_HPP
#define IRC_CONNECT_HPP

#include <iostream>
#include <sys/poll.h>
#include <vector>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <netdb.h>
#include <string>
#include "fcntl.h"
#include "unistd.h"


class Connect
{
private:
	unsigned short			port;
	int 					m_socket;
	std::vector<pollfd>		polls_fd;

public:
	Connect(unsigned short port, int socket);
	virtual ~Connect();
	void	start();
	void	stop();
	int		add(); //возвращает fd соединения
	void	remove(std::vector<pollfd>::iterator); // получает fd соединения и закрывает его
	int		receive(int); // принимает сообщение по fd
	int		send_msg(int); // отправляет сообщения по fd

protected:
	void	init();
	void	createSocket();

};


#endif //IRC_CONNECT_HPP
