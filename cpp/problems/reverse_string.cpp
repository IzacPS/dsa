#include <iostream>

int main (int argc, char *argv[]) {
    std::string s = {};     
    std::cout << "Digite uma string: ";
    std::cin >> s;
    
    for(int i = s.size() - 1, j = 0; j < s.size() / 2; i--, j++){
        const char c = s[i];
        s[i] = s[j];
        s[j] = c;
    }

    std::cout << s;
    
    return 0;
}

