#include <string>
#include <vector>
#include <fcntl.h>
#include <csignal>
#include <iostream>

bool work = true;

void sigHandler(int signum)
{
	(void)signum;
	work = false;
}

int main(int argc, char **argv)
{
	if (argc < 3)
	{
		std::cout << "Usage: ./ircserv <port> <password>" << std::endl;
		exit(EXIT_FAILURE);
	}
	int port = atoi(argv[1]);
	if (port < 1024 || port > 49151)
	{
		std::cout << "Wrong port!" << std::endl;
		exit(EXIT_FAILURE);
	}
	// Создание сокета

	// bind, listen  нужно реализовать



	signal(SIGINT, sigHandler);

	while (work)
	{
		// Нужно добавить вызов функци проверки наличия коннекта клиентов,
		// получения сообщении и т.д.
		std::cout << "Am I working";
	}

}