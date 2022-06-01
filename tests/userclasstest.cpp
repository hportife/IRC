#include "../tools/LogIdentifier.hpp"
#include "../srv_inside/User.hpp"
//c++ ./userclasstest.cpp ../tools/LogIdentifier.cpp ../srv_inside/NicknameStorage.cpp ../srv_inside/User.cpp ../srv_inside/UserCreator.cpp
//PLEASE, WRITE THE DOC!!!!!!!!!!!!!!
int main(void)
{
    NicknameStorage *storage = new NicknameStorage;
    std::cout << LogIdentifier::info() << "Simple test to add Nicknames\n";
    storage->add_nickname("Will");
    storage->add_nickname("Pasta");
    storage->add_nickname("Oliver21");
    storage->add_nickname("442mfcker");
    storage->add_nickname("Kern");
    storage->add_nickname("Alexa");

    std::cout << LogIdentifier::info << "Create 4 UserCreator\n";
    UserCreator *uc1 = new UserCreator(111, storage, "2109");
    UserCreator *uc2 = new UserCreator(222, storage, "2109");
    UserCreator *uc3 = new UserCreator(333, storage, "2109");
    UserCreator *uc4 = new UserCreator(444, storage, "2109");

    std::cout << LogIdentifier::info << "For 1 user insert wrong password\n";
    uc1->set_password("2108");
    uc2->set_password("2109");
    uc3->set_password("2109");
    uc4->set_password("2109");

    std::cout << LogIdentifier::info << "For 2 user insert wrong password\n";
    return (0);
}