#include <iostream>
#include <string>
#include <cstdlib>

const char * WHITE_SPACE = "\t ";

int main() {
    for (std::string line; std::getline(std::cin, line);) {
	 std::cout << line.erase(0, line.find_first_not_of(WHITE_SPACE)) << std::endl;
    }
    exit(EXIT_SUCCESS);
}
