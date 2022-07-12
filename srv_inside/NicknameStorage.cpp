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
    std::map<std::string, int>::iterator it;
    std::cout << LogIdentifier::debug("FROM_NICKNAME_STORAGE_")
              << "Осторожно, функция вывода хранилища может течь!\n";
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
                       "and don't add"
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
        std::cout   << LogIdentifier::debug("FROM_NICKNAMESTORAGE_")
                    << added_nickname
                    << " add to nickname storage"
                    << std::endl;
        storage[added_nickname] = USER_IS_NOT_OPER;
    }
}

/*
 * мапа при создании сама сортируется если имеет ключ-строку
 */
//void NicknameStorage::sort_a_storage() {
//    std::sort(storage.begin(), storage.end());
//    std::cout   << LogIdentifier::debug("FROM_NICKNAMESTORAGE_")
//                << "nickname storage has been sorted"
//                << std::endl;
//}

int NicknameStorage::delete_nickname(std::string deleted_nickname) {
    if (storage.erase(deleted_nickname) == 1) {
        std::cout   << LogIdentifier::debug("FROM_NICKNAMESTORAGE_")
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
        std::cout   << LogIdentifier::error("FROM_NICKNAMESTORAGE_")
                    << "nickname "
                    << searched_nickname
                    << " is not available in the storage, "
                       "the user needs to choose another nickname"
                    << std::endl;
        return (ERR_NICKNAMEINUSE);
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