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
}

