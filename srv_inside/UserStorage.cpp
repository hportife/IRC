#include "UserStorage.hpp"

UserStorage::UserStorage(NicknameStorage *ptr_to_nickname_storage) {
    this->ptr_to_nickname_storage = ptr_to_nickname_storage;
    std::cout   << LogIdentifier::info("FROM_USERSTORAGE_")
                << "User storage has been created"
                << std::endl;
}

UserStorage::~UserStorage() {
    std::cout   << LogIdentifier::debug("FROM_USERSTORAGE_")
                << "User storage has been deleted"
                << std::endl;
}

void UserStorage::add_user(User *user_for_add) {
    if (search_by_id(user_for_add->get_user_id()) == NULL) {
        user_storage.push_back(user_for_add);
        std::cout << LogIdentifier::info("FROM_USERSTORAGE_")
                  << "user ["
                  << user_for_add->get_user_nickname()
                  << "] has been added to user storage"
                  << std::endl;
        return;
    }
    std::cout   << LogIdentifier::debug("FROM_USERSTORAGE_")
                << "the user ["
                << user_for_add->get_user_nickname()
                << "] is already known"
                << std::endl;
}

User *UserStorage::search_by_nickname(std::string searched_nickname) {
    for (int i = 0; i < user_storage.size(); ++i){
        if (user_storage[i]->get_user_nickname().compare(searched_nickname) == 0)
        {
            std::cout   << LogIdentifier::debug("FROM_USERSTORAGE_")
                        << "UserStorage Searcher by nickname "
                           "found a nickname "
                        << searched_nickname
                        << std::endl;
            return (user_storage[i]);
        }
    }
    std::cout   << LogIdentifier::debug("FROM_USERSTORAGE_")
                << "UserStorage Searcher by nickname "
                      "not found a nickname "
                << searched_nickname
                << std::endl;
    return (nullptr);
}

User *UserStorage::search_by_id(int searched_id) {
    for (int i = 0; i < user_storage.size(); ++i){
        if (user_storage[i]->get_user_id() == (searched_id))
        {
            std::cout   << LogIdentifier::debug("FROM_USERSTORAGE_")
                        << "UserStorage Searcher by id "
                           "found a id ["
                        << searched_id
                        << "]" <<std::endl;
            return (user_storage[i]);
        }
    }
    std::cout   << LogIdentifier::debug("FROM_USERSTORAGE_")
                << "UserStorage Searcher by id "
                   "not found a id ["
                << searched_id
                << "]" <<std::endl;
    return (NULL);
}

int UserStorage::get_user_position_in_storage(User *user) {
    for (int i = 0; i < user_storage.size(); ++i) {
        if (user_storage[i]->get_user_id() == user->get_user_id())
            return i;
    }
    return (-1);
}

int UserStorage::delete_user_from_storage(User *user) {
    if (user && get_user_position_in_storage(user) != -1){
        user_storage.erase(user_storage.begin() +
                                   get_user_position_in_storage(user));
        std::cout   << LogIdentifier::debug("FROM_USERSTORAGE_")
                    << "User with id: "
                    << user->get_user_id()
                    << " and nickname: "
                    << user->get_user_nickname()
                    << " has been deleted"
                    << std::endl;
        this->ptr_to_nickname_storage->delete_nickname(user->get_user_nickname());
        return (1);
    }
    else{
        std::cout   << LogIdentifier::error("FROM_USERSTORAGE_")
                    << "parameter for the deleted user were passed incorrectly"
                    << std::endl;
        return (0);
    }
}