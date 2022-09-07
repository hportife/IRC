#include "../includes/User.hpp"
#include "../includes/UserStorage.hpp"
//c++ usercreatortest.cpp ../tools/LogIdentifier.cpp ../srv_inside/User.cpp ../srv_inside/UserCreator.cpp ../srv_inside/NicknameStorage.cpp ../srv_inside/UserStorage.cpp
int main() {
    //Pt1. Создание хранилища никнеймов
    NicknameStorage *tmp = new NicknameStorage();
    //Pt2. Создание хранилища пользователей
    UserStorage *testUserStorage = new UserStorage(tmp);
    //Pt3. Создание тестового пользователя через Криейтор
    UserCreator *testCreator = new UserCreator(4242, tmp, "pass");
    testCreator->set_password("pass");
    testCreator->set_nickname("UUS55555S");
    testCreator->set_realname("Alfred Testov Levi");//поле не должно быть пустым
    //Pt4. Добавление тестового пользователя в хранилище.
    testUserStorage->add_user(*testCreator->get_ready_user());
    //Pt5. махинации
    std::cout << testUserStorage->search_by_id(4242)->get_user_nickname() << std::endl<< "_______________________________________" << std::endl;
    testUserStorage->delete_user_from_storage(testUserStorage->search_by_id(4242)) ;
    testUserStorage->add_user(*testCreator->get_ready_user());
}