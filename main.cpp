#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>

#include "Parser.hpp"

using std::cout; using std::cin;
using std::endl; using std::string;
using std::vector; using std::istringstream;
using std::stringstream;

// :Angel PRIVMSG Wiz :Hello are you receiving this message ?
// То КоммандЛайн должен выглядеть как:
// <PRIVMSG><Angel><Wiz><Hello are you receiving this message ?>

int main() {
//    string str = ":Angel PRIVMSG Wiz :Hello are you receiving this message ?";
    string str = "PasS sed00834r";

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
