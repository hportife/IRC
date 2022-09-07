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
#include <strings.h>
#include <cstring>

#define GREY_COL "\033[37m"
#define GREEN_COL "\033[32m"
#define NO_COL "\033[0m"


class Connect
{
private:
	unsigned short			_port;
	int 					_socket;
	std::vector<pollfd>	*	_polls;
    std::vector<pollfd>::iterator iter;

public:
	Connect(unsigned short port, std::vector<pollfd> * polls);
	virtual ~Connect();
	void	start();
	void	stop();
	int		add(); //возвращает fd соединения
	void	remove(std::vector<pollfd>::iterator); // получает fd соединения и закрывает его
	const std::string receive(int); // принимает сообщение по fd
	int		send_msg(int, const std::string&); // отправляет сообщения по fd
	void	call_poll();
    void    remove_poolhup();// удаляет отвалившихся клиентов


protected:
	void	init();
	void	createSocket();

};


#endif //IRC_CONNECT_HPP
