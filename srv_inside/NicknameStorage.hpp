#ifndef IRC_NICKNAMESTORAGE_HPP
#define IRC_NICKNAMESTORAGE_HPP

#define CORRPASS                1000
#define INCORRPASS              1001
#define NICKNAMEISMAYBEGIVEN    1010
#define ERR_NICKNAMEINUSE       1011
#define ERR_NICKNAMEISTOOLONG   1012
#define ERR_NICKNAMEISEMPTY     1013
#define NICKNAMEHASBEENGIVEN    1014

#include <vector>
#include <algorithm>
#include "../tools/LogIdentifier.hpp"
//#include "User.hpp"

// need to add check to size added nickname
class NicknameStorage{
private:
    std::vector<std::string>    storage;
    int                         storage_capacity;

public:
    NicknameStorage();
    ~NicknameStorage();

    int         get_storage_capacity();
    void        get_storage();

    void        add_nickname(std::string added_nickname);
    int         delete_nickname(std::string deleted_nickname);
    int         search_a_conflict(std::string searched_nickname);
    void        sort_a_storage();
};

#endif