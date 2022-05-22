#include "UserStorage.hpp"

UserStorage::UserStorage() {
    std::cout   << LogIdentifier::info()
                << "User storage has been created"
                << std::endl;
}

UserStorage::~UserStorage() {
    std::cout   << LogIdentifier::debug()
                << "User storage has been deleted"
                << std::endl;
}

void UserStorage::add_user(user user_for_add) {
    user_storage.push_back(user_for_add);
    std::cout   << LogIdentifier::debug()
                << "user "
                << user_for_add.get_user_nickname()
                << " has been added to user storage"
                << std::endl;
}

user *UserStorage::search_by_nickname(std::string searched_nickname) {
    for (int i = 0; i < user_storage.size(); ++i){
        if (user_storage[i].get_user_nickname().compare(searched_nickname) == 0)
        {
            std::cout   << LogIdentifier::debug()
                        << "UserStorage Searcher by nickname "
                           "found a nickname "
                        << searched_nickname
                        << std::endl;
            return (&user_storage[i]);
        }
    }
    std::cout   << LogIdentifier::error()
                << "UserStorage Searcher by nickname "
                      "not found a nickname "
                << searched_nickname
                << std::endl;
    return (nullptr);
}

user *UserStorage::search_by_id(int searched_id) {
    for (int i = 0; i < user_storage.size(); ++i){
        if (user_storage[i].get_user_id() == (searched_id))
        {
            std::cout   << LogIdentifier::debug()
                        << "UserStorage Searcher by id "
                           "found a id "
                        << searched_id
                        << std::endl;
            return (&user_storage[i]);
        }
    }
    std::cout   << LogIdentifier::error()
                << "UserStorage Searcher by id "
                   "not found a id "
                << searched_id
                << std::endl;
    return (nullptr);
}