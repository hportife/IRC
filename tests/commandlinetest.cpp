#include "../srv_inside/CommandLine.hpp"

int main(void){
    CommandLine *test = new CommandLine("<MSG> <Lala> <Keke> <MSGGG> <LalaAA> <Keeeee>", 6);
    std::cout << test->getNumberOfParameter() << std::endl;
    std::cout << test->getOneParameter(1) << std::endl;
    std::cout << test->getOneParameter(2) << std::endl;
    std::cout << test->getOneParameter(3) << std::endl;
    std::cout << test->getOneParameter(4) << std::endl;
    std::cout << test->getOneParameter(5) << std::endl;
    std::cout << test->getOneParameter(6) << std::endl;
    std::cout << test->getOneParameter(7) << std::endl;
}