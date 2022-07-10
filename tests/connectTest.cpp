//
// Created by user1 on 26.06.2022.
//

#include "connectTest.hpp"
#include "../srcs_connect/Connect.hpp"

int main()
{
    std::cout << "IRC" << std::endl;
    unsigned short port = 6667;

    Connect *irc = new Connect(port);
    irc->start();
    irc->stop();



    return (0);


}


