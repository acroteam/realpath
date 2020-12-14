// "Copyright [2020] <Taraymovich Igor>"
#include <iostream>
#include <string>
#include "realpath.hpp"

void usage(std::string name, std::ostream& os = std::cerr) {
    os << "Usage:" << std::endl;
    os << "  " << name << " <path>" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        usage(argv[0]);
        return EXIT_FAILURE;
    }
    
    std::cout << weakly_canonical(argv[1]) << std::endl;
    return EXIT_SUCCESS;
}
