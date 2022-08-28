#include <iostream>
#include "includes/Serv.hpp"

int main(){
    std::string pass;
    std::cout << "Привет! Чтобы запустить сервер, "
                 "нужно ввести пароль, который будет"
                 "использоваться для сервера:\n";
    std::cin >> pass;
    std::cout << "Сервер запускается...\n";
    Serv *IRC_server = new Serv(pass);
    while (true){

    }
}