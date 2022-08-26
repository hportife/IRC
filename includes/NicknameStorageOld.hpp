#ifndef IRC_NICKNAMESTORAGEOLD_HPP
#define IRC_NICKNAMESTORAGEOLD_HPP

#include <vector>
#include <algorithm>
#include "defines.hpp"

class NicknameStorageOld{
private:
    std::vector<std::string>    storage;


public:
    NicknameStorageOld();
    ~NicknameStorageOld();

    void        print_storage();

    int         check_size_added_nickname(std::string added_nickname);
    void        add_nickname(std::string added_nickname);
    int         delete_nickname(std::string deleted_nickname);
    int         search_a_conflict(std::string searched_nickname);
    void        sort_a_storage();
    int         get_capacity();
};

#endif