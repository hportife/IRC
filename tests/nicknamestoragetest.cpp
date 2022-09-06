#include "../includes/LogIdentifier.hpp"
#include "../includes/NicknameStorageOld.hpp"
#include "../includes/NicknameStorage.hpp"
//compile: c++ -std=c++98 ./nicknamestoragetest.cpp ../tools/LogIdentifier.cpp ../srv_inside/NicknameStorage.cpp

int main(void)
{
    NicknameStorage *storage = new NicknameStorage;

    std::cout << LogIdentifier::info() << "Simple test to add Nicknames\n";
    storage->add_nickname("Will");
    storage->add_nickname("Pasta");
    storage->add_nickname("Oliver21");
    storage->add_nickname("442mfcker");
    storage->add_nickname("Kern");
    storage->add_nickname("Alexa");

    std::cout   << "\n\n\n"
                << LogIdentifier::info()
                << "Test to add >9 symbols nickname\n";
    storage->add_nickname("Herrrrrrrrrr");

    std::cout   << "\n\n\n"
                << LogIdentifier::info()
                << "Test to add empty nickname\n";
    storage->add_nickname("");

    std::cout   << "\n\n\n"
                << LogIdentifier::info()
                << "Test to search a conflicts\n";
    storage->search_a_conflict("Pasta");
    storage->search_a_conflict("Loid");

    std::cout   << "\n\n\n"
                << LogIdentifier::info()
                << "Test to get storage\n";
    storage->print_storage();

    std::cout   << "\n\n\n"
                << LogIdentifier::info()
                << "Test to delete nicknames\n";
    storage->delete_nickname("Kern");
    storage->delete_nickname("Lern");

    std::cout   << "\n\n\n"
                << LogIdentifier::info()
                << "Test to get storage\n";
    storage->print_storage();
    std::cout << "The size of storage = " << storage->get_capacity() << std::endl;

    delete storage;
}