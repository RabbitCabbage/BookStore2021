//
// Created by lu'ren'jia'd's on 2021/12/15.
//
#include <vector>
#include <iostream>
#include <cstring>
#include <fstream>
#include <map>
#include "blocklist.h"
#include "command.h"
#include "parser.h"

std::vector<People *> Login;
People *current_account = nullptr;
Visitor *original_visitor;
extern std::map<People *, bookInfo> selected_book;
extern BlockList account_list;

void Initialize() {
    current_account = new Visitor;
    original_visitor = dynamic_cast<Visitor *>(current_account);
    //AccountList/Book List 里面存的是索引值对，在Account/Book File里面存的是书本具体信息
    std::fstream initialize;
    initialize.open("BookFile", std::ios::in);
    if (!initialize) {
        initialize.open("AccountFile", std::ios::out | std::ios::app);
        accountInfo super;
        strcpy(super.UserID, "root");
        super.rank = 7;
        strcpy(super.Password, "sjtu");
        memset(super.Username, '\0', sizeof(super.Username));
        account_list.InsertPair(super.UserID, 0);
        initialize.write(reinterpret_cast<char *>(&super), sizeof(accountInfo));
        initialize.close();
        initialize.open("BookFile", std::ios::out | std::ios::app);
        initialize.close();
        initialize.open("FinanceRecord", std::ios::out | std::ios::app);
        initialize.close();
    } else initialize.close();
}

void CommandCarryOut(char *command, bool &running) {
    if (Blank(command)) { return; }
    else {
        WhiteSpace_end(command);
        WhiteSpace_head(command);
        char *keyword = CommandKeyword(command);
        if (KeywordExamine(keyword)) {
            Conduct(running, keyword, command);
        } else { InvalidReport(); }
    }
}

void Conduct(bool &running, char *keyword, char *command) {
    if (strcmp(keyword, "quit") == 0 || strcmp(keyword, "exit") == 0) {
        delete current_account;
        running = false;
        return;
    } else if (strcmp(keyword, "su") == 0) { SuParser(command); }
    else if (strcmp(keyword, "logout") == 0) { Logout(command); }
    else if (strcmp(keyword, "register") == 0) { RegisterParser(command); }
    else if (strcmp(keyword, "passwd") == 0) { PasswdParser(command); }
    else if (strcmp(keyword, "useradd") == 0) { UseraddParser(command); }
    else if (strcmp(keyword, "delete") == 0) { DeleteParser(command); }
    else if (strcmp(keyword, "show") == 0) { ShowParser(command); }
    else if (strcmp(keyword, "buy") == 0) { BuyParser(command); }
    else if (strcmp(keyword, "select") == 0) { SelectParser(command); }
    else if (strcmp(keyword, "modify") == 0) { ModifyParser(command); }
    else if (strcmp(keyword, "import") == 0) { ImportParser(command); }
    else if (strcmp(keyword, "report myself") == 0) { current_account->ReportMyself(); }
    else if (strcmp(keyword, "show finance") == 0) { ShowFinanceParser(command); }
    else if (strcmp(keyword, "report finance") == 0) { current_account->ReportFinance(); }
    else if (strcmp(keyword, "report employee") == 0) { current_account->ReportEmployee(); }
    else if (strcmp(keyword, "log") == 0) { current_account->Log(); }
}

char *CommandKeyword(char *command) {
    static char keyword[20];
    memset(keyword, '\0', sizeof(keyword));
    if (strcmp(command, "logout") == 0 || strcmp(command, "quit") == 0 || strcmp(command, "exit") == 0 ||
        strcmp(command, "report myself") == 0 || strcmp(command, "show finance") == 0 ||
        strcmp(command, "report finance") == 0 || strcmp(command, "report employee") == 0 ||
        strcmp(command, "log") == 0 || strcmp(command, "show") == 0) {
        strcpy(keyword, command);
        command[0] = '\0';
        return keyword;
    }
    int i = 0, j;
    while (command[i] != ' ' && command[i] != '\0') {
        keyword[i] = command[i];
        ++i;
    }
    i = SkipWhiteSpace(command, i);//command第一个不是空格的地方就是i
    if (strcmp(keyword, "show") == 0) {
        //就是想看看下一个词是不是finance,这里只有两种可能
        char judge[10];
        int h = i, k;
        for (k = 0; command[h] != ' ' && k < 10; ++k, ++h) {
            judge[k] = command[h];
        }
        judge[k] = '\0';
        if (strcmp(judge, "finance") == 0) {
            strcpy(keyword, "show finance");
            i = h;//command  首个不是空格的地方
        }
    }
    for (j = 0; command[i] != '\0'; ++i, ++j) {
        command[j] = command[i];
    }
    command[j] = '\0';
    WhiteSpace_end(command);
    WhiteSpace_head(command);
    return keyword;//找到关键词，并且处理了command，command只留下了具体内容
}

void InvalidReport() {
    std::cout << "Invalid\n";
}

bool Blank(const char *command) {
    int index = 0;
    while (command[index] != '\0') {
        if (command[index] != ' ')return false;
        index++;
    }
    return true;
}


