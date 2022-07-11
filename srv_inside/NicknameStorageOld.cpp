#include "../tools/LogIdentifier.hpp"
#include "NicknameStorage.hpp"

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
    std::vector<std::string> tmp = this->storage;
    std::sort(tmp.begin(), tmp.end());
    std::cout << LogIdentifier::debug("FROM_NICKNAME_STORAGE_")
                << "Осторожно, функция вывода хранилища может течь!\n";
    for (int i = 0; i < storage.size(); i++)
        std::cout   << i + 1
                    << ": "
                    << tmp[i]
                    << std::endl;
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
                       "and don't add"
                       "to nickname storage"
                    << std::endl;
        return(ERR_NICKNAMEISEMPTY);
    } else
        return (0);
}

void NicknameStorage::add_nickname(std::string added_nickname) {
    if (check_size_added_nickname(added_nickname) != ERR_NICKNAMEISTOOLONG &&
            check_size_added_nickname(added_nickname) != ERR_NICKNAMEISEMPTY)
    {
        std::cout   << LogIdentifier::debug("FROM_NICKNAMESTORAGE_")
                << added_nickname
                << " add to nickname storage"
                << std::endl;
        storage.push_back(added_nickname);
    }
}

void NicknameStorage::sort_a_storage() {
    std::sort(storage.begin(), storage.end());
    std::cout   << LogIdentifier::debug("FROM_NICKNAMESTORAGE_")
                << "nickname storage has been sorted"
                << std::endl;
}

int NicknameStorage::delete_nickname(std::string deleted_nickname) {
    for (int i = 0; i < storage.size(); ++i) {
        if (storage[i].compare(deleted_nickname) == 0){
            storage.erase(storage.begin() + i);
            std::cout   << LogIdentifier::debug("FROM_NICKNAMESTORAGE_")
                        << "nickname "
                        << deleted_nickname
                        << " has been deleted" << std::endl;
            return (0);
        }
    }
    std::cout   << LogIdentifier::error("FROM_NICKNAMESTORAGE_")
                << "When trying to delete, the nickname "
                << deleted_nickname
                << " was not found in the nickname storage"
                << std::endl;
    return (1);
}

int NicknameStorage::search_a_conflict(std::string searched_nickname) {
    for (int i = 0; i < storage.size(); ++i) {
        if (storage[i].compare(searched_nickname) == 0){
//            storage.erase(storage.begin() + i);
            std::cout   << LogIdentifier::error("FROM_NICKNAMESTORAGE_")
                        << "nickname "
                        << searched_nickname
                        << " is available in the storage, "
                           "the user needs to choose another nickname"
                        << std::endl;
            return (ERR_NICKNAMEINUSE);
        }
    }
    std::cout   << LogIdentifier::debug("FROM_NICKNAMESTORAGE_")
                << "nickname "
                << searched_nickname
                << " is not in storage and may be taken"
                << std::endl;
    return (NICKNAMEISMAYBEGIVEN);
}

int NicknameStorage::get_capacity() {
    return (storage.size());
}