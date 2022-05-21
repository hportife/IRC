#include "NicknameStorage.hpp"

NicknameStorage::NicknameStorage() {
    std::cout   << LogIdentifier::info()
                << "Nickname storage has been created"
                << std::endl;
}

NicknameStorage::~NicknameStorage() {
    std::cout   << LogIdentifier::debug()
                << "Nickname storage has been deleted"
                << std::endl;
}

int NicknameStorage::get_storage_capacity() {
    return (storage_capacity);
}

void NicknameStorage::get_storage() {
    for (int i = 0; i < storage.size(); i++)
        std::cout << storage[i] << std::endl;
}

void NicknameStorage::add_nickname(std::string added_nickname) {
    storage.push_back(added_nickname);
    std::cout   << LogIdentifier::debug()
                << added_nickname
                << "add to nickname storage"
                << std::endl;
    NicknameStorage::sort_a_storage();
}

void NicknameStorage::sort_a_storage() {
    std::sort(storage.begin(), storage.end());
    std::cout   << LogIdentifier::debug()
                << "nickname storage has been sorted"
                << std::endl;
}

int NicknameStorage::delete_nickname(std::string deleted_nickname) {
    for (int i = 0; i < storage.size(); ++i) {
        if (storage[i].compare(deleted_nickname) == 0){
            storage.erase(storage.begin() + i);
            std::cout   << LogIdentifier::debug()
                        << "nickname "
                        << deleted_nickname
                        << " has been deleted" << std::endl;
            NicknameStorage::sort_a_storage();
            return (0);
        }
    }
    std::cout   << LogIdentifier::error()
                << "When trying to delete, the nickname "
                << deleted_nickname
                << " was not found in the nickname storage"
                << std::endl;
    return (1);
}

int NicknameStorage::search_a_conflict(std::string searched_nickname) {
    for (int i = 0; i < storage.size(); ++i) {
        if (storage[i].compare(searched_nickname) == 0){
            storage.erase(storage.begin() + i);
            std::cout   << LogIdentifier::error()
                        << "nickname "
                        << searched_nickname
                        << " is available in the storage, "
                           "the user needs to choose another nickname"
                        << std::endl;
            return (ERR_NICKNAMEINUSE);
        }
    }
    std::cout   << LogIdentifier::debug()
                << "nickname "
                << searched_nickname
                << " is not in storage and may be taken"
                << std::endl;
    return (NICKNAMEISMAYBEGIVEN);
}

