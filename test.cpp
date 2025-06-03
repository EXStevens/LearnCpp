#include <iostream>
#include <string>

int main() {
    std::string name;
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    
    std::cout << "Hello, " << name << "! Welcome to the C++14 project." << std::endl;
    std::cout << "Press Enter to continue.";
    std::cin.get();
    
    return 0;
}
