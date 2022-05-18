#include "LogIdentifier.hpp"

LogIdentifier::LogIdentifier() {}

LogIdentifier::~LogIdentifier() {}

std::string LogIdentifier::debug() {
    return ("\033[1m\033[4m\033[33mDBG::\033[0m ");
}

std::string LogIdentifier::error() {
    return ("\033[1m\033[4m\033[31mERR::\033[0m ");
}

std::string LogIdentifier::info() {
    return ("\033[1m\033[4m\033[32mINF::\033[0m ");
}