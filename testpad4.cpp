#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

int main() {
    
    std::string str0 = "Like a feather.txt";
    bool isTxtFile = str0.substr(str0.size() - 4) == ".txt";
    std::cout << str0.substr(str0.size() - 4) << std::endl << int(isTxtFile) << std::endl;
}