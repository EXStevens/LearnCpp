#include <iostream>
#include <string>
#include <limits>


std::string * toMA(std::string& n);

struct User {
    std::string name;
    short age;
    std::string alias;
};

int main() {
    User user;
    user.age = 0;

    std::cout << "Enter your name: ";
    std::getline(std::cin, user.name);
    std::cout << "Enter your age: ";
    std::cin >> user.age;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if(user.age < 18) {
        user.alias = "Kiddo";
    } else {
        user.alias = "Dummy";
    }

    std::cout << "Hello, " << user.name << " " << user.alias << "! Welcome to the C++ project. And your name stores at " << toMA(user.name) << "." << std::endl;
    std::cout << "Press Enter to continue...";
    std::cin.get();
    
    return 0;
}

std::string * toMA(std::string& n) {
    return &n;
}