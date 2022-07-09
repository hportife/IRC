#include "LogIdentifier.hpp"

LogIdentifier::LogIdentifier() {}

LogIdentifier::~LogIdentifier() {}

std::string LogIdentifier::debug() {
    return ("\033[1m\033[4m\033[33mDBG::\033[0m ");
}

std::string LogIdentifier::debug(std::string from) {
    std::string tmp = "\033[1m\033[4m\033[33m" + from + "DBG::\033[0m ";
    return (tmp);
}

std::string LogIdentifier::error() {
    return ("\033[1m\033[4m\033[31mERR::\033[0m ");
}

std::string LogIdentifier::error(std::string from) {
    std::string tmp = "\033[1m\033[4m\033[31m" + from + "ERR::\033[0m ";
    return (tmp);
}

std::string LogIdentifier::info() {
    return ("\033[1m\033[4m\033[32mINF::\033[0m ");
}

std::string LogIdentifier::info(std::string from) {
    std::string tmp = "\033[1m\033[4m\033[32m" + from + "INF::\033[0m ";
    return (tmp);
}