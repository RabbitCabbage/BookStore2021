#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "command.h"
#include "blocklist.h"

//to do 在你用完strtok之后字符串就被破换掉了，没有进行考虑
BlockList account_list("AccountList");
BlockList isbn_book_list("ISBN_BookList");
BlockList name_book_list("Name_BookList");
BlockList author_book_list("Author_BookList");
BlockList keyword_book_list("Keyword_BookList");
extern People *current_account;
extern std::vector<People *> Login;

int main() {
    Initialize();
    bool running = true;
    char *command;
    while (running) {
        std::string s;
        if (getline(std::cin, s)) {
            if (s.length() > 1024)std::cout << "Invalid\n";
            else {
                command = new char[1025];
                memset(command, '\0', 1025 * sizeof(char));
                std::stringstream ss;
                ss.clear();
                ss.str(s);
                ss >> command;
                CommandCarryOut(command, running);
            }
        } else exit(0);
    }
    delete command;
    return 0;
}
