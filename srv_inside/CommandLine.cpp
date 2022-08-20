
#include "../tools/LogIdentifier.hpp"
#include "CommandLine.hpp"

CommandLine::CommandLine() {}

CommandLine::CommandLine(std::string cmdln, int number_of_params){
    this->parameters = cmdln;
    this->number_of_params = number_of_params;
    std::cout   << LogIdentifier::info("FROM_COMMNADLINE_CLASS_")
                << "create new CommandLine "
                << getOneParameter(1) << "\'s type"
                << std::endl;
}
CommandLine::~CommandLine(){

}

int CommandLine::getNumberOfParameter() const{
    return (this->number_of_params);
}

std::string CommandLine::getOneParameter(int position){
    if (position > 0 && position <= this->number_of_params){
        for (int i = 0; i < this->parameters.size(); ++i) {
            if (this->parameters[i] == '<'){
                position--;
            }
            if (position == 0){
                int end_arg_sym = i;
                while (this->parameters[end_arg_sym] != '>')
                    end_arg_sym++;
                return (this->parameters.substr(i + 1,  end_arg_sym - (i + 1)));
            }
        }
    }
    return ("NULL");
}

std::string CommandLine::getParameter() const {
    return this->parameters;
}
