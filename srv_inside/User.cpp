#include "../includes/User.hpp"

User::User(std::string nickname, int id,
           std::string realname, std::string clientname)
{
    this->user_nickname = nickname;
    this->user_id = id;
    this->user_realname = realname;
    this->client_name = clientname;
    this->user_params = initUserParams();
    std::cout   << LogIdentifier::info("FROM_USERCLASS_" + this->user_nickname + "_")
                << "User: \n\t\t\t  | nick:\t["
                << nickname
                << "]\t|\n \t\t\t  | id: \t["
                << id
                << "]\t|\n \t\t\t  has been created"
                << std::endl;
}

std::map<std::string, bool> User::initUserParams(){
    std::map<std::string, bool> tmp_room_params;
    tmp_room_params.insert(std::pair<std::string, bool>("i", false));
    tmp_room_params.insert(std::pair<std::string, bool>("s", false));
    tmp_room_params.insert(std::pair<std::string, bool>("w", false));
    return (tmp_room_params);
}

User::~User() {
    std::cout   << LogIdentifier::info("FROM_USERCLASS_" + this->user_nickname + "_")
                << "User: \n\t\t\t  | nick:\t["
                << this->user_nickname
                << "]\t|\n\t\t\t  | id: \t["
                << this->user_id
                << "]\t|\n\t\t\t  has been deleted"
                << std::endl;
}

void User::set_nickname(std::string new_nickname) {
    std::cout   << LogIdentifier::debug("FROM_USERCLASS_" + this->user_nickname + "_")
                << "user with id " << user_id
                << " changed nickname ";
    if (user_nickname.empty())
        std::cout   << "on " << new_nickname << std::endl;
    else
        std::cout   << user_nickname << " on "
                    << new_nickname << std::endl;
    user_nickname = new_nickname;
}

std::string User::get_user_nickname() const {return (this->user_nickname);}

std::string User::get_user_realname() const {return (this->user_realname);}

int User::get_user_id() const {return (this->user_id);}

bool User::getUserParamValue(std::string param){
    if (this->user_params.find(param) != this->user_params.end())
        return (this->user_params.find(param)->second);
    return (false);
}

void User::setUserParamValue(std::string param, bool value) {
    if (this->user_params.find(param) != this->user_params.end())
        this->user_params.find(param)->second = value;
}

void User::setAwayMsg(std::string away_msg){
    this->away_msg = away_msg;
}
void User::setAwayMsg(){
    this->away_msg.clear();
}
bool User::isAwayMsg(){
    return (this->away_msg.empty());
}
std::string User::getAwayMsg()const{
    return (this->away_msg);
}

std::string User::get_client_name() const {return (this->client_name);}

User *User::clone() const{
    return (new User(this->user_nickname,
                     this->user_id,
                     this->user_realname,
                     this->client_name));
}