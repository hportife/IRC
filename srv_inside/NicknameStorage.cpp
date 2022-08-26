#include "../includes/LogIdentifier.hpp"
#include "../includes/NicknameStorage.hpp"

NicknameStorage::NicknameStorage() {
    std::cout   << LogIdentifier::info("FROM_NICKNAMESTORAGE_")
                << "Nickname storage has been created"
                << std::endl;
}

NicknameStorage::~NicknameStorage() {
    std::cout   << LogIdentifier::debug("FROM_NICKNAMESTORAGE_")
                << "Nickname storage has been deleted"
                << std::endl;
}

void NicknameStorage::print_storage() {
    std::map<std::string, int>::iterator it;
    int i = 1;
    for (it = storage.begin(); it != storage.end(); ++it) {
        std::cout << i++ << ": " << (*it).first << "\n";
    }
}

int NicknameStorage::check_size_added_nickname(std::string added_nickname) {
    if (added_nickname.length() > 9)
    {
        std::cout   << LogIdentifier::error("FROM_NICKNAMESTORAGE_")
                    << added_nickname
                    << " too long, and don't add"
                       "to nickname storage"
                    << std::endl;
        return (ERR_NICKNAMEISTOOLONG);
    }
    else if (added_nickname.empty())
    {
        std::cout   << LogIdentifier::error("FROM_NICKNAMESTORAGE_")
                    << "added_nickname is empty, "
                       "and don't add "
                       "to nickname storage"
                    << std::endl;
        return(ERR_NICKNAMEISEMPTY);
    } else
        return (0);
}

void NicknameStorage::add_nickname(std::string added_nickname) {
    int checked_size = check_size_added_nickname(added_nickname);

    if (checked_size != ERR_NICKNAMEISTOOLONG &&
        checked_size != ERR_NICKNAMEISEMPTY)
    {
        std::cout   << LogIdentifier::info("FROM_NICKNAMESTORAGE_")
                    << "["
                    << added_nickname
                    << "] add to nickname storage"
                    << std::endl;
        storage[added_nickname] = SIMPLE_VALUE;
    }
}

int NicknameStorage::delete_nickname(std::string deleted_nickname) {
    if (storage.erase(deleted_nickname) == 1) {
        std::cout   << LogIdentifier::info("FROM_NICKNAMESTORAGE_")
                    << "nickname "
                    << deleted_nickname
                    << " has been deleted" << std::endl;
        return (0);
    }
    std::cout   << LogIdentifier::error("FROM_NICKNAMESTORAGE_")
                << "When trying to delete, the nickname "
                << deleted_nickname
                << " was not found in the nickname storage"
                << std::endl;
    return (1);
}

int NicknameStorage::search_a_conflict(std::string searched_nickname) {
    std::map<std::string, int>::iterator it;

    it = storage.find(searched_nickname);
    if (it != storage.end()) {
        std::cout   << LogIdentifier::debug("FROM_NICKNAMESTORAGE_")
                    << "nickname "
                    << searched_nickname
                    << " is available in the storage"
                    << std::endl;
        return (ERR_NICKNAMEINUSE);
    }
    std::cout   << LogIdentifier::debug("FROM_NICKNAMESTORAGE_")
                << "nickname "
                << searched_nickname
                << " is not in storage"
                << std::endl;
    return (NICKNAMEISMAYBEGIVEN);
}

int NicknameStorage::get_capacity() {
    return (storage.size());
}

int NicknameStorage::get_value(std::string checked_nickname){
    std::map<std::string, int>::iterator it = storage.find(checked_nickname);
    if (it != storage.end()){
        return (it->second);
    }
    return (-1);
}

int NicknameStorage::set_value(std::string nickname, int value){
    std::map<std::string, int>::iterator it = storage.find(nickname);
    if (it != storage.end()){
        it->second = value;
        return (it->second);
    }
    return (-1);
}