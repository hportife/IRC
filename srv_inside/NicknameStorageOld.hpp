#ifndef IRC_NICKNAMESTORAGEOLD_HPP
#define IRC_NICKNAMESTORAGEOLD_HPP

#define NICKNAMEISMAYBEGIVEN    1010
#define ERR_NICKNAMEINUSE       1011
#define ERR_NICKNAMEISTOOLONG   1012
#define ERR_NICKNAMEISEMPTY     1013
#define NICKNAMEHASBEENGIVEN    1014

#include <vector>
#include <algorithm>

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