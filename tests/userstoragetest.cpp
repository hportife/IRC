//
// Created by grafsky on 7/30/22.
// compile: c++ userstoragetest.cpp ../srv_inside/User.cpp ../srv_inside/UserStorage.cpp ../srv_inside/NicknameStorage.cpp ../tools/LogIdentifier.cpp

#include "../srv_inside/UserStorage.hpp"
#include "../tools/LogIdentifier.hpp"

int main(){
    NicknameStorage *tmp_nickname_storage = new NicknameStorage();
    UserStorage     *user_storage = new UserStorage(tmp_nickname_storage);
    User *one, *two, *three;

    std::cout<< LogIdentifier::info("_____________________OK_CASE____________________") << std::endl;
    one = new User("kekman", 1111, "Vasily Petrovich", "Adium");
    tmp_nickname_storage->add_nickname(one->get_user_nickname());
    user_storage->add_user(one);//Ok-case

    std::cout<< LogIdentifier::info("_____________________OK_CASE____________________") << std::endl;
    two = new User("follo", 2222, "German Arkadievich", "Adium");
    tmp_nickname_storage->add_nickname(two->get_user_nickname());
    user_storage->add_user(two);//Ok-case

    std::cout<< LogIdentifier::info("_____________________OK_CASE____________________") << std::endl;
    three = new User("brabr", 3333, "Petya Salamon", "Zetto");
    tmp_nickname_storage->add_nickname(three->get_user_nickname());
    user_storage->add_user(three);//Ok-case

    std::cout<< LogIdentifier::error("_____________________NOK_CASE____________________") << std::endl;
    user_storage->add_user(one);//Nok-case

    std::cout<< LogIdentifier::info("_____________________OK_CASE____________________") << std::endl;
    std::cout << user_storage->search_by_id(two->get_user_id())->get_user_nickname() << std::endl;
    std::cout << user_storage->search_by_nickname(three->get_user_nickname())->get_user_nickname() << std::endl;
    user_storage->delete_user_from_storage(two);
}