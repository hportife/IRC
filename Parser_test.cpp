#include <iostream>
//#include "vector"
//#include "algorithm"
//c++ Parser.cpp Parser_test.cpp Serv.cpp srv_inside/CommandLine.cpp srv_inside/NicknameStorage.cpp srv_inside/Room.cpp srv_inside/RoomStorage.cpp srv_inside/User.cpp tools/LogIdentifier.cpp srv_inside/UserStorage.cpp Commando.cpp
#include "includes/Parser.hpp"
#include "includes/Parser.hpp"

// :Angel PRIVMSG Wiz :Hello are you receiving this message ?
// То КоммандЛайн должен выглядеть как:
// <PRIVMSG><Angel><Wiz><Hello are you receiving this message ?>


int main() {
//all comands:

//  JOIN #foobar
//  JOIN &foo fubar
//  JOIN #foo,&bar fubar
//  JOIN #foo,#bar fubar,foobar
//  JOIN #foo,#bar

//    std::string str = "JOIN #foo,#bar";
//    std::string str = "LIST #twilight_zone,  #42  foobar";
//    std::string str = "PART #oz-ops,&group5";
//    std::string str = ":Angel PrIVMSg Wiz, Den,Jax :Hello are you receiving this message ?";
//    std::string str = "QUIT :Gone to have lunch";
//    std::string str = " :Angel PRIVMSG Wiz :Hello are you receiving this message ?";

//      std::string str = "MODE #Finnish +im";
//      std::string str = "MODE #Finnish +o Kilroy";
//      std::string str = "MODE #Finnish +v Wiz";
    //  MODE #Fins -s
//      std::string str = "MODE #42 +k";
//    std::string str = "MODE #eu-opers +l 10";
    //  MODE &oulu +b
    //  MODE &oulu +b *!*@*
      std::string str = "MODE &oulu +b *!*@*.edu";
      std::cout << str.

//      std::string str = "KICK #Finnish John :Speaking English";

    Parser parser("MODE #Finnish +im");
//    std::cout << parser.getCommandLine().getParameters() << std::endl;
    std::cout << "queue size = " << (int)parser.getAllCommandLine().size() << std::endl;
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
//    std::string str = "    :   Angel PrIVMSg       &Wiz,          #Den,    Kolya Hello are you receiving this message ?    !";
////    std::string str = "QUIT :Gone to have lunch";
////    std::string cmd = str.substr(str.find(':') + 1, str.rfind(':') - str.find(':') - 1);
////    if ((int)str.find('#') != -1 or (int)str.find('$') != -1)
//    const char *dollar = strchr(str.data(), '#');
//
//    std::vector<std::string> channels = find_channel(str);
////    std::string cmd = str.substr(0, -1);
////    std::vector<int>::iterator it = std::find_if (myvector.begin(), myvector.end(), IsOdd);
////    std::cout << "The first odd value is " << *it << '\n';
//    std::cout << (std::string)dollar << std::endl;
//    std::string sss = (std::string)dollar;
//    std::cout << sss.size() << std::endl;
//
//    for (int i = 0; i < channels.size(); ++i)
//        std::cout << "|" << channels[i] << "|" << std::endl;
//    //    std::cout << "|" << cmd << "|" << std::endl;
//    return 0;
//}
