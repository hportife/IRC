#include <iostream>

#include <iterator>

#include "Parser.hpp"

// :Angel PRIVMSG Wiz :Hello are you receiving this message ?
// То КоммандЛайн должен выглядеть как:
// <PRIVMSG><Angel><Wiz><Hello are you receiving this message ?>

int main() {
    std::string str = ":Angel PrIVMSg Wiz, Den,Jax :Hello are you receiving this message ?";
//    std::string str = "QUIT :Gone to have lunch";

    Parser parser(str);
//    std::cout << parser.getCommandLine().getParameters() << std::endl;
    std::cout << parser.getCommandLine().getParameters() << std::endl;
    std::cout << parser.getCommandLine().getNumberOfParameter() << std::endl;
    std::cout << parser.getCommandLine().getOneParameter(1) << std::endl;
    std::cout << parser.getCommandLine().getOneParameter(2) << std::endl;
    std::cout << parser.getCommandLine().getOneParameter(3) << std::endl;
    std::cout << parser.getCommandLine().getOneParameter(4) << std::endl;
    std::cout << parser.getCommandLine().getOneParameter(5) << std::endl;
    std::cout << parser.getCommandLine().getOneParameter(6) << std::endl;
    std::cout << parser.getCommandLine().getOneParameter(7) << std::endl;
	return EXIT_SUCCESS;
}
