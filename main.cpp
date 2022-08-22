#include <iostream>
//#include "vector"
//#include "algorithm"

#include "Parser.hpp"

// :Angel PRIVMSG Wiz :Hello are you receiving this message ?
// То КоммандЛайн должен выглядеть как:
// <PRIVMSG><Angel><Wiz><Hello are you receiving this message ?>


int main() {
//    std::string str = ":Angel PrIVMSg Wiz, Den,Jax :Hello are you receiving this message ?";
    std::string str = "QUIT :Gone to have lunch";
//    std::string str = " :Angel PRIVMSG Wiz :Hello are you receiving this message ?";

    Parser parser(str);
//    std::cout << parser.getCommandLine().getParameters() << std::endl;
    int k = (int)parser.getAllCommandLine().size();
    std::cout << "queue size = " << k << std::endl;
    while (!parser.getAllCommandLine().empty()) {
        std::cout << parser.getOneCommandLine().getParameters() << std::endl;
        std::cout << parser.getOneCommandLine().getNumberOfParameter() << std::endl;
        std::cout << parser.getOneCommandLine().getOneParameter(1) << std::endl;
        std::cout << parser.getOneCommandLine().getOneParameter(2) << std::endl;
        std::cout << parser.getOneCommandLine().getOneParameter(3) << std::endl;
        std::cout << parser.getOneCommandLine().getOneParameter(4) << std::endl;
        std::cout << parser.getOneCommandLine().getOneParameter(5) << std::endl;
        std::cout << parser.getOneCommandLine().getOneParameter(6) << std::endl;
        parser.popOneCommandLine();
//        parser._tasks.pop();
    }

	return EXIT_SUCCESS;
}


//
//bool IsOdd (int i) {
//    return ((i%2)==1);
//}

//int main() {
//    std::string str = "    :   Angel PrIVMSg       Wiz,          Den,    Kolya Hello are you receiving this message ?    !";
////    std::string str = "QUIT :Gone to have lunch";
////    std::string cmd = str.substr(str.find(':') + 1, str.rfind(':') - str.find(':') - 1);
//    std::string cmd = str.substr(0, -1);
////    std::vector<int>::iterator it = std::find_if (myvector.begin(), myvector.end(), IsOdd);
////    std::cout << "The first odd value is " << *it << '\n';
//    std::cout << "|" << cmd << "|" << std::endl;
//    return 0;
//}
