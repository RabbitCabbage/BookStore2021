#include <iostream>
#include <vector>
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
        command = new char[1024];
        memset(command, '\0', 1024 * sizeof(char));
        if (std::cin.getline(command, 1024))CommandCarryOut(command, running);
        else exit(0);
    }
    delete command;
    return 0;
}
