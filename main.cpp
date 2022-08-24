#include <iostream>
//#include "vector"
//#include "algorithm"

#include "Parser.hpp"

// :Angel PRIVMSG Wiz :Hello are you receiving this message ?
// То КоммандЛайн должен выглядеть как:
// <PRIVMSG><Angel><Wiz><Hello are you receiving this message ?>


int main() {
//all comands:

//    std::string str = "PASS secretpassword";
//    std::string str = "NICK Wiz";		// Вступление нового никнейма "Wiz".
//    std::string str = ":WiZ NICK Kilroy"; // WiZ изменяет свой никнейм на Kilroy.

//    std::string str = "USER guest tolmoon tolsun :Ronnie Reagan";
// Пользователь зарегистрировал себя под именем "guest" и его реальное имя "Ronnie Reagan"

//    std::string str = "OPER foo bar";
// Попытка зарегистрироваться как IRC-оператор, используя имя пользователя "foo" и пароль "bar".

//    std::string str = "WHO jto* o";
// Список пользователей, соответствующие маске "jto*", если они являются операторами.
//    std::string str = "MODE #Finnish +im";
// Делает канал #Finnish модерируемым и 'invite-only'.

//  JOIN #foobar                      // вход на канал #foobar.
//  JOIN &foo fubar                   // вход на канал &foo, используя ключ "fubar".
//  JOIN #foo,&bar fubar              // вход на канал #foo, используя ключ "fubar" и на канал &bar без использования ключа.
//  JOIN #foo,#bar fubar,foobar       // вход на канал #foo, используя ключ "fubar" и на канал #bar, используя ключ "foobar".
//  JOIN #foo,#bar

    std::string str = "JOIN #foo,#bar";
//    std::string str = "LIST #twilight_zone,  #42  foobar";
//    std::string str = ":Angel PrIVMSg Wiz, Den,Jax :Hello are you receiving this message ?";
//    std::string str = "QUIT :Gone to have lunch";
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
