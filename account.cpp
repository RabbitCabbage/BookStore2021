//
// Created by lu'ren'jia'd's on 2021/12/15.
//
#include "blocklist.h"
#include "account.h"
#include "log.h"
#include "parser.h"
#include <iostream>
#include <set>
#include <vector>
#include <fstream>
#include <cstring>
#include <map>

extern std::vector<People *> Login;
extern People *current_account;
extern BlockList account_list;
extern BlockList isbn_book_list;
extern BlockList name_book_list;
extern BlockList author_book_list;
extern BlockList keyword_book_list;

std::map<People *, bookInfo> selected_book;

//std::fstream file;

Manager::Manager() {
    info.rank = 7;
    memset(info.Password, '\0', sizeof(info.Password));
    memset(info.UserID, '\0', sizeof(info.UserID));
    memset(info.Username, '\0', sizeof(info.Username));
}

accountInfo Manager::GetInfo() {
    return this->info;
}

void Manager::InputInfo(accountInfo &tmp) {
    this->info.rank = tmp.rank;
    strcpy(this->info.Password, tmp.Password);
    strcpy(this->info.UserID, tmp.UserID);
    strcpy(this->info.Username, tmp.Username);
}

void Manager::Su(char *id, char *pass_word) {
    std::fstream file;
    int location = account_list.FindPairs(id);
    if (location == -100000) {
        InvalidReport();
        return;
    } else {
        accountInfo tmp;
        file.open("AccountFile");
        file.seekg(location);
        file.read(reinterpret_cast<char *>(&tmp), sizeof(accountInfo));
        file.close();//把它的信息读出来
        if (pass_word == nullptr) {
            if (tmp.rank == 0)current_account = new Visitor;
            else if (tmp.rank == 1)current_account = new Customer;
            else if (tmp.rank == 3)current_account = new Employee;
            else if (tmp.rank == 7)current_account = new Manager;
            current_account->InputInfo(tmp);
            Login.push_back(current_account);

        } else {
            if (strcmp(tmp.Password, pass_word) == 0) {
                if (tmp.rank == 0)current_account = new Visitor;
                else if (tmp.rank == 1)current_account = new Customer;
                else if (tmp.rank == 3)current_account = new Employee;
                else if (tmp.rank == 7)current_account = new Manager;
                current_account->InputInfo(tmp);
                Login.push_back(current_account);

            } else InvalidReport();
        }
    }
}


void Manager::Register(char *id, char *pass_word, char *user_name) {
    std::fstream file;
    int location = account_list.FindPairs(id);
    if (location != -100000) {
        InvalidReport();
        return;
    }
    accountInfo regi;
    regi.rank = 1;
    strcpy(regi.Password, pass_word);
    strcpy(regi.UserID, id);
    strcpy(regi.Username, user_name);
    file.open("AccountFile");
    file.seekp(0, std::ios::end);
    int write_location = file.tellp();
    file.write(reinterpret_cast<char *>(&regi), sizeof(accountInfo));
    file.close();
    account_list.InsertPair(id, write_location);
}

void Manager::Passwd(char *id, char *passwd1, char *passwd2) {
    std::fstream file;
    //传参数进来的时候传了1和2，也即是passwd2有可能是空的，这种情况是满足条件的
    int location = account_list.FindPairs(id);
    if (location == -100000) {
        InvalidReport();
        return;
    }
    accountInfo right_info;
    file.open("AccountFile");
    file.seekg(location);
    file.read(reinterpret_cast<char *>(&right_info), sizeof(accountInfo));
    if (passwd2 == nullptr) {//则第一个就是新密码
        strcpy(right_info.Password, passwd1);
        file.seekp(location);
        file.write(reinterpret_cast<char *>(&right_info), sizeof(accountInfo));
    } else if (strcmp(passwd1, right_info.Password) == 0) {
        strcpy(right_info.Password, passwd2);
        file.seekp(location);
        file.write(reinterpret_cast<char *>(&right_info), sizeof(accountInfo));
    } else InvalidReport();
    file.close();
}

void Manager::Useradd(char *id, char *pass_word, int priority, char *user_name) {
    std::fstream file;
    if (priority >= current_account->GetInfo().rank) {
        InvalidReport();
        return;
    }
    int location = account_list.FindPairs(id);
    if (location != -100000) {
        InvalidReport();
        return;
    }
    accountInfo add;
    add.rank = priority;
    strcpy(add.Password, pass_word);
    strcpy(add.Username, user_name);
    strcpy(add.UserID, id);
    file.open("AccountFile");
    file.seekp(0, std::ios::end);
    int write_location = file.tellp();
    file.write(reinterpret_cast<char *>(&add), sizeof(accountInfo));
    file.close();
    account_list.InsertPair(id, write_location);
}

void Manager::Delete(char *id) {
    int location = account_list.FindPairs(id);
    if (location == -100000) {
        InvalidReport();
        return;
    }
    auto ptr = Login.begin();
    for (; ptr != Login.end(); ++ptr) {
        if (strcmp(((*ptr)->GetInfo().UserID), id) == 0) {
            InvalidReport();
            return;
        }
    }
    account_list.DeletePair(id, location);
}

void Manager::Show(char *isbn, char *name, char *author, char *keyword) {
    std::fstream file;
    if (isbn == nullptr && name == nullptr && author == nullptr && keyword != nullptr) {
        int num;
        char keys[60][60];
        KeyWordParser(keyword, num, keys);
        if (num > 0) {
            InvalidReport();
            return;
        }
        std::vector<int> to_find = keyword_book_list.FindAllPairs(keyword);
        if (to_find.empty()) {
            std::cout << "\n";
            return;
        } else {
            std::set<bookInfo> to_show;
            file.open("BookFile");
            for (auto ptr = to_find.begin(); ptr != to_find.end(); ++ptr) {
                file.seekg(*ptr);
                book tmp;
                file.read(reinterpret_cast<char *>(&(tmp.info)), sizeof(bookInfo));
                to_show.insert(tmp.info);
            }
            file.close();
            for (auto ptr = to_show.begin(); ptr != to_show.end(); ++ptr) {
                bookInfo tmp = *ptr;
                _ShowABook(tmp);
            }
        }
    } else if (isbn == nullptr && name == nullptr && author != nullptr && keyword == nullptr) {
        std::vector<int> to_find = author_book_list.FindAllPairs(author);
        if (to_find.empty()) {
            std::cout << "\n";
            return;
        } else {
            std::set<bookInfo> to_show;
            file.open("BookFile");
            for (auto ptr = to_find.begin(); ptr != to_find.end(); ++ptr) {
                file.seekg(*ptr);
                book tmp;
                file.read(reinterpret_cast<char *>(&(tmp.info)), sizeof(bookInfo));
                to_show.insert(tmp.info);
            }
            file.close();
            for (auto ptr = to_show.begin(); ptr != to_show.end(); ++ptr) {
                bookInfo tmp = *ptr;
                _ShowABook(tmp);
            }
        }
    } else if (isbn == nullptr && name != nullptr && author == nullptr && keyword == nullptr) {
        std::vector<int> to_find = name_book_list.FindAllPairs(name);
        if (to_find.empty()) {
            std::cout << "\n";
            return;
        } else {
            std::set<bookInfo> to_show;
            file.open("BookFile");
            for (auto ptr = to_find.begin(); ptr != to_find.end(); ++ptr) {
                file.seekg(*ptr);
                book tmp;
                file.read(reinterpret_cast<char *>(&(tmp.info)), sizeof(bookInfo));
                to_show.insert(tmp.info);
            }
            file.close();
            for (auto ptr = to_show.begin(); ptr != to_show.end(); ++ptr) {
                bookInfo tmp = *ptr;
                _ShowABook(tmp);
            }
        }
    } else if (isbn != nullptr && name == nullptr && author == nullptr && keyword == nullptr) {
        int location = isbn_book_list.FindPairs(isbn);
        if (location == -100000) {
            std::cout << "\n";
            return;
        } else {
            book to_show;
            file.open("BookFile");
            file.seekg(location);
            file.read(reinterpret_cast<char *>(&(to_show.info)), sizeof(bookInfo));
            to_show.ShowABook();
            file.close();
        }
    } else if (isbn == nullptr && name == nullptr && author == nullptr && keyword == nullptr) {
        isbn_book_list.ShowAllBooks();
    } else {
        InvalidReport();
        return;
    }
}


void Manager::Buy(char *isbn, int quantity) {
    std::fstream file;
    int location = isbn_book_list.FindPairs(isbn);
    if (location == -100000) {
        InvalidReport();
        return;
    }
    file.open("BookFile");
    file.seekg(location);
    bookInfo to_buy;
    file.read(reinterpret_cast<char *>(&to_buy), sizeof(bookInfo));
    if (to_buy.number < quantity) {
        file.close();
        InvalidReport();
        return;
    }
    double total = quantity * to_buy.price;
    to_buy.number -= quantity;
    file.seekp(location);
    file.write(reinterpret_cast<char *>(&to_buy), sizeof(bookInfo));
    file.close();
    selected_book[current_account] = to_buy;
    std::stringstream ss;
    std::string total_str;
    ss.clear();
    ss << total;
    ss >> total_str;
    int counter = 0;
    for (counter = 0; counter < total_str.length(); ++counter) {
        if (total_str[counter] == '.')break;
    }
    if (counter == total_str.length()) {
        total_str += ".00";
    } else if (counter == total_str.length() - 1) {
        total_str += '0';
    }
    if (counter == total_str.length() - 2)total_str += '0';
    std::cout << total_str << std::endl;
    RecordAnEntry(total);
}

void Manager::Select(char *isbn) {
    std::fstream file;
    int location = isbn_book_list.FindPairs(isbn);
    if (location == -100000) {
        file.open("BookFile", std::ios::app);
        int add_loc = file.tellp();
        book add;
        strcpy(add.info.ISBN, isbn);
        file.write(reinterpret_cast<char *>(&add), sizeof(bookInfo));
        isbn_book_list.InsertPair(isbn, add_loc);
        file.close();
        selected_book[current_account] = add.info;
    } else {
        file.open("BookFile");
        file.seekg(location);
        bookInfo to_select;
        file.read(reinterpret_cast<char *>(&to_select), sizeof(bookInfo));
        file.close();
        selected_book[current_account] = to_select;
    }
}

void Manager::Modify(char *isbn, char *name, char *author, char *keyword, double price) {
    std::fstream file;
    if (selected_book.count(current_account) == 0) {
        InvalidReport();
        return;
    }
    bookInfo to_modify = selected_book[current_account];
    int location = isbn_book_list.FindPairs(to_modify.ISBN);
    file.open("BookFile");
    file.seekp(location);
    if (isbn != nullptr) {
        //修改在list文件以及存储文件里面的信息
        if (isbn_book_list.FindPairs(isbn) == -100000) {
            isbn_book_list.DeletePair(to_modify.ISBN, location);
            strcpy(to_modify.ISBN, isbn);
            isbn_book_list.InsertPair(isbn, location);
        } else {
            InvalidReport();
            return;
        }
    }
    if (name != nullptr) {
        name_book_list.DeletePair(to_modify.name, location);
        strcpy(to_modify.name, name);
        name_book_list.InsertPair(name, location);
    }
    if (author != nullptr) {
        author_book_list.DeletePair(to_modify.author, location);
        strcpy(to_modify.author, author);
        author_book_list.InsertPair(author, location);
    }
    if (keyword != nullptr) {
        if (KeywordRepeated(keyword)) {
            InvalidReport();
            return;
        }
        int num;
        char keys[60][60];
        KeyWordParser(keyword, num, keys);
        //先把原来的关键词键值对都删掉，然后再把新的关键词键值对加入进去
        for (int i = 0; strcmp(to_modify.keyword[i], "\0") != 0; ++i) {
            keyword_book_list.DeletePair(to_modify.keyword[i], location);
            memset(to_modify.keyword[i], '\0', sizeof(to_modify.keyword[i]));
        }
        for (int i = 0; i <= num; ++i) {
            strcpy(to_modify.keyword[i], keys[i]);
            keyword_book_list.InsertPair(to_modify.keyword[i], location);
        }
    }
    if (price != -1)to_modify.price = price;
    file.write(reinterpret_cast<char *>(&to_modify), sizeof(bookInfo));
    file.close();
    selected_book[current_account] = to_modify;
}

void Manager::Import(int quantity, double cost) {
    std::fstream file;
    if (selected_book.count(current_account) == 0) {
        InvalidReport();
        return;
    }
    bookInfo to_import = selected_book[current_account];
    int location = isbn_book_list.FindPairs(to_import.ISBN);
    file.open("BookFile");
    file.seekp(location);
    to_import.number += quantity;
    file.write(reinterpret_cast<char *>(&to_import), sizeof(bookInfo));
    file.close();
    RecordAnEntry((-1.0) * cost);
    selected_book[current_account] = to_import;
}

void Manager::ReportMyself() {
    return;
}

void Manager::ShowFinance(int time) {
    std::string s = ShowEntry(time);
    std::cout << s;
}

void Manager::ShowFinance() {
    std::string s = ShowAllEntry();
    std::cout << s;
}

void Manager::ReportFinance() {
    return;
}

void Manager::ReportEmployee() {
    return;
}

void Manager::Log() {
    return;
}

Employee::Employee() {
    info.rank = 3;
    memset(info.Password, '\0', sizeof(info.Password));
    memset(info.UserID, '\0', sizeof(info.UserID));
    memset(info.Username, '\0', sizeof(info.Username));
}

accountInfo Employee::GetInfo() {
    return this->info;
}

void Employee::InputInfo(accountInfo &tmp) {
    this->info.rank = tmp.rank;
    strcpy(this->info.Password, tmp.Password);
    strcpy(this->info.UserID, tmp.UserID);
    strcpy(this->info.Username, tmp.Username);
}

void Employee::Su(char *id, char *pass_word) {
    std::fstream file;
    int location = account_list.FindPairs(id);
    if (location == -100000) {
        InvalidReport();
        return;
    } else {
        accountInfo tmp;
        file.open("AccountFile");
        file.seekg(location);
        file.read(reinterpret_cast<char *>(&tmp), sizeof(accountInfo));
        file.close();//把它的信息读出来
        accountInfo your_info = current_account->GetInfo();
        if (pass_word == nullptr) {
            if (your_info.rank > tmp.rank) {

                if (tmp.rank == 0)current_account = new Visitor;
                else if (tmp.rank == 1)current_account = new Customer;
                else if (tmp.rank == 3)current_account = new Employee;
                else if (tmp.rank == 7)current_account = new Manager;
                current_account->InputInfo(tmp);
                Login.push_back(current_account);
            } else InvalidReport();
        } else {
            if (strcmp(tmp.Password, pass_word) == 0) {

                if (tmp.rank == 0)current_account = new Visitor;
                else if (tmp.rank == 1)current_account = new Customer;
                else if (tmp.rank == 3)current_account = new Employee;
                else if (tmp.rank == 7)current_account = new Manager;
                current_account->InputInfo(tmp);
                Login.push_back(current_account);
            } else InvalidReport();
        }
    }
}

void Employee::Register(char *id, char *pass_word, char *user_name) {
    std::fstream file;
    int location = account_list.FindPairs(id);
    if (location != -100000) {
        InvalidReport();
        return;
    }
    accountInfo regi;
    regi.rank = 1;
    strcpy(regi.Password, pass_word);
    strcpy(regi.UserID, id);
    strcpy(regi.Username, user_name);
    file.open("AccountFile");
    file.seekp(0, std::ios::end);
    int write_location = file.tellp();
    file.write(reinterpret_cast<char *>(&regi), sizeof(accountInfo));
    file.close();
    account_list.InsertPair(id, write_location);
}

void Employee::Passwd(char *id, char *passwd1, char *passwd2) {
    std::fstream file;
    //传参数进来的时候传了1和2，也即是passwd2有可能是空的，这种情况是满足条件的
    int location = account_list.FindPairs(id);
    if (location == -100000) {
        InvalidReport();
        return;
    }
    accountInfo right_info;
    file.open("AccountFile");
    file.seekg(location);
    file.read(reinterpret_cast<char *>(&right_info), sizeof(accountInfo));
    if (passwd2 == nullptr) {//则第一个就是新密码
        InvalidReport();
        return;
    } else if (strcmp(passwd1, right_info.Password) == 0) {
        strcpy(right_info.Password, passwd2);
        file.seekp(location);
        file.write(reinterpret_cast<char *>(&right_info), sizeof(accountInfo));
    } else InvalidReport();
    file.close();
}

void Employee::Useradd(char *id, char *pass_word, int priority, char *user_name) {
    std::fstream file;
    if (priority >= current_account->GetInfo().rank) {
        InvalidReport();
        return;
    }
    int location = account_list.FindPairs(id);
    if (location != -100000) {
        InvalidReport();
        return;
    }
    accountInfo add;
    add.rank = priority;
    strcpy(add.Password, pass_word);
    strcpy(add.Username, user_name);
    strcpy(add.UserID, id);
    file.open("AccountFile");
    file.seekp(0, std::ios::end);
    int write_location = file.tellp();
    file.write(reinterpret_cast<char *>(&add), sizeof(accountInfo));
    file.close();
    account_list.InsertPair(id, write_location);
}

void Employee::Delete(char *id) {
    InvalidReport();
}

void Employee::Show(char *isbn, char *name, char *author, char *keyword) {
    std::fstream file;
    if (isbn == nullptr && name == nullptr && author == nullptr && keyword != nullptr) {
        int num;
        char keys[60][60];
        KeyWordParser(keyword, num, keys);
        if (num > 0) {
            InvalidReport();
            return;
        }
        std::vector<int> to_find = keyword_book_list.FindAllPairs(keyword);
        if (to_find.empty()) {
            std::cout << "\n";
            return;
        } else {
            std::set<bookInfo> to_show;
            file.open("BookFile");
            for (auto ptr = to_find.begin(); ptr != to_find.end(); ++ptr) {
                file.seekg(*ptr);
                book tmp;
                file.read(reinterpret_cast<char *>(&(tmp.info)), sizeof(bookInfo));
                to_show.insert(tmp.info);
            }
            file.close();
            for (auto ptr = to_show.begin(); ptr != to_show.end(); ++ptr) {
                bookInfo tmp = *ptr;
                _ShowABook(tmp);
            }
        }
    } else if (isbn == nullptr && name == nullptr && author != nullptr && keyword == nullptr) {
        std::vector<int> to_find = author_book_list.FindAllPairs(author);
        if (to_find.empty()) {
            std::cout << "\n";
            return;
        } else {
            std::set<bookInfo> to_show;
            file.open("BookFile");
            for (auto ptr = to_find.begin(); ptr != to_find.end(); ++ptr) {
                file.seekg(*ptr);
                book tmp;
                file.read(reinterpret_cast<char *>(&(tmp.info)), sizeof(bookInfo));
                to_show.insert(tmp.info);
            }
            file.close();
            for (auto ptr = to_show.begin(); ptr != to_show.end(); ++ptr) {
                bookInfo tmp = *ptr;
                _ShowABook(tmp);
            }
        }
    } else if (isbn == nullptr && name != nullptr && author == nullptr && keyword == nullptr) {
        std::vector<int> to_find = name_book_list.FindAllPairs(name);
        if (to_find.empty()) {
            std::cout << "\n";
            return;
        } else {
            std::set<bookInfo> to_show;
            file.open("BookFile");
            for (auto ptr = to_find.begin(); ptr != to_find.end(); ++ptr) {
                file.seekg(*ptr);
                book tmp;
                file.read(reinterpret_cast<char *>(&(tmp.info)), sizeof(bookInfo));
                to_show.insert(tmp.info);
            }
            file.close();
            for (auto ptr = to_show.begin(); ptr != to_show.end(); ++ptr) {
                bookInfo tmp = *ptr;
                _ShowABook(tmp);
            }
        }
    } else if (isbn != nullptr && name == nullptr && author == nullptr && keyword == nullptr) {
        int location = isbn_book_list.FindPairs(isbn);
        if (location == -100000) {
            std::cout << "\n";
            return;
        } else {
            book to_show;
            file.open("BookFile");
            file.seekg(location);
            file.read(reinterpret_cast<char *>(&(to_show.info)), sizeof(bookInfo));
            to_show.ShowABook();
            file.close();
        }
    } else if (isbn == nullptr && name == nullptr && author == nullptr && keyword == nullptr) {
        isbn_book_list.ShowAllBooks();
    } else {
        InvalidReport();
        return;
    }
}


void Employee::Buy(char *isbn, int quantity) {
    std::fstream file;
    int location = isbn_book_list.FindPairs(isbn);
    if (location == -100000) {
        InvalidReport();
        return;
    }
    file.open("BookFile");
    file.seekg(location);
    bookInfo to_buy;
    file.read(reinterpret_cast<char *>(&to_buy), sizeof(bookInfo));
    if (to_buy.number < quantity) {
        file.close();
        InvalidReport();
        return;
    }
    double total = quantity * to_buy.price;
    to_buy.number -= quantity;
    file.seekp(location);
    file.write(reinterpret_cast<char *>(&to_buy), sizeof(bookInfo));
    file.close();
    selected_book[current_account] = to_buy;
    std::stringstream ss;
    std::string total_str;
    ss.clear();
    ss << total;
    ss >> total_str;
    int counter = 0;
    for (counter = 0; counter < total_str.length(); ++counter) {
        if (total_str[counter] == '.')break;
    }
    if (counter == total_str.length()) {
        total_str += ".00";
    } else if (counter == total_str.length() - 1) {
        total_str += '0';
    }
    if (counter == total_str.length() - 2)total_str += '0';
    std::cout << total_str << std::endl;
    RecordAnEntry(total);

}

void Employee::Select(char *isbn) {
    std::fstream file;
    int location = isbn_book_list.FindPairs(isbn);
    if (location == -100000) {
        file.open("BookFile", std::ios::app);
        int add_loc = file.tellp();
        book add;
        strcpy(add.info.ISBN, isbn);
        file.write(reinterpret_cast<char *>(&add), sizeof(bookInfo));
        isbn_book_list.InsertPair(isbn, add_loc);
        file.close();
        selected_book[current_account] = add.info;
    } else {
        file.open("BookFile");
        file.seekg(location);
        bookInfo to_select;
        file.read(reinterpret_cast<char *>(&to_select), sizeof(bookInfo));
        file.close();
        selected_book[current_account] = to_select;
    }
}

void Employee::Modify(char *isbn, char *name, char *author, char *keyword, double price) {
    std::fstream file;
    if (selected_book.count(current_account) == 0) {
        InvalidReport();
        return;
    }
    bookInfo to_modify = selected_book[current_account];
    int location = isbn_book_list.FindPairs(to_modify.ISBN);
    file.open("BookFile");
    file.seekp(location);
    if (isbn != nullptr) {
        //修改在list文件以及存储文件里面的信息
        if (isbn_book_list.FindPairs(isbn) == -100000) {
            isbn_book_list.DeletePair(to_modify.ISBN, location);
            strcpy(to_modify.ISBN, isbn);
            isbn_book_list.InsertPair(isbn, location);
        } else {
            InvalidReport();
            return;
        }
    }
    if (name != nullptr) {
        name_book_list.DeletePair(to_modify.name, location);
        strcpy(to_modify.name, name);
        name_book_list.InsertPair(name, location);
    }
    if (author != nullptr) {
        author_book_list.DeletePair(to_modify.author, location);
        strcpy(to_modify.author, author);
        author_book_list.InsertPair(author, location);
    }
    if (keyword != nullptr) {
        if (KeywordRepeated(keyword)) {
            InvalidReport();
            return;
        }
        int num;
        char keys[60][60];
        KeyWordParser(keyword, num, keys);
        //先把原来的关键词键值对都删掉，然后再把新的关键词键值对加入进去
        for (int i = 0; strcmp(to_modify.keyword[i], "\0") != 0; ++i) {
            keyword_book_list.DeletePair(to_modify.keyword[i], location);
            memset(to_modify.keyword[i], '\0', sizeof(to_modify.keyword[i]));
        }
        for (int i = 0; i <= num; ++i) {
            strcpy(to_modify.keyword[i], keys[i]);
            keyword_book_list.InsertPair(to_modify.keyword[i], location);
        }
    }
    if (price != -1)to_modify.price = price;
    file.write(reinterpret_cast<char *>(&to_modify), sizeof(bookInfo));
    file.close();
    selected_book[current_account] = to_modify;
}

void Employee::Import(int quantity, double cost) {
    std::fstream file;
    if (selected_book.count(current_account) == 0) {
        InvalidReport();
        return;
    }
    bookInfo to_import = selected_book[current_account];
    int location = isbn_book_list.FindPairs(to_import.ISBN);
    file.open("BookFile");
    file.seekp(location);
    to_import.number += quantity;
    file.write(reinterpret_cast<char *>(&to_import), sizeof(bookInfo));
    file.close();
    RecordAnEntry((-1.0) * cost);
    selected_book[current_account] = to_import;
}

void Employee::ReportMyself() {
    return;
}

void Employee::ShowFinance(int time) {
    InvalidReport();
}

void Employee::ShowFinance() {
    InvalidReport();
}

void Employee::ReportFinance() {
    InvalidReport();
}

void Employee::ReportEmployee() {
    InvalidReport();
}

void Employee::Log() {
    InvalidReport();
}

Customer::Customer() {
    info.rank = 1;
    memset(info.Password, '\0', sizeof(info.Password));
    memset(info.UserID, '\0', sizeof(info.UserID));
    memset(info.Username, '\0', sizeof(info.Username));
}

void Customer::Su(char *id, char *pass_word) {
    std::fstream file;
    int location = account_list.FindPairs(id);
    if (location == -100000) {
        InvalidReport();
        return;
    } else {
        accountInfo tmp;
        file.open("AccountFile");
        file.seekg(location);
        file.read(reinterpret_cast<char *>(&tmp), sizeof(accountInfo));
        file.close();//把它的信息读出来
        accountInfo your_info = current_account->GetInfo();
        if (pass_word == nullptr) {
            if (your_info.rank > tmp.rank) {

                if (tmp.rank == 0)current_account = new Visitor;
                else if (tmp.rank == 1)current_account = new Customer;
                else if (tmp.rank == 3)current_account = new Employee;
                else if (tmp.rank == 7)current_account = new Manager;
                current_account->InputInfo(tmp);
                Login.push_back(current_account);
            } else InvalidReport();
        } else {
            if (strcmp(tmp.Password, pass_word) == 0) {

                if (tmp.rank == 0)current_account = new Visitor;
                else if (tmp.rank == 1)current_account = new Customer;
                else if (tmp.rank == 3)current_account = new Employee;
                else if (tmp.rank == 7)current_account = new Manager;
                current_account->InputInfo(tmp);
                Login.push_back(current_account);

            } else InvalidReport();
        }
    }
}

accountInfo Customer::GetInfo() {
    return this->info;
}

void Customer::InputInfo(accountInfo &tmp) {
    this->info.rank = tmp.rank;
    strcpy(this->info.Password, tmp.Password);
    strcpy(this->info.UserID, tmp.UserID);
    strcpy(this->info.Username, tmp.Username);
}

void Customer::Register(char *id, char *pass_word, char *user_name) {
    std::fstream file;
    int location = account_list.FindPairs(id);
    if (location != -100000) {
        InvalidReport();
        return;
    }
    accountInfo regi;
    regi.rank = 1;
    strcpy(regi.Password, pass_word);
    strcpy(regi.UserID, id);
    strcpy(regi.Username, user_name);
    file.open("AccountFile");
    file.seekp(0, std::ios::end);
    int write_location = file.tellp();
    file.write(reinterpret_cast<char *>(&regi), sizeof(accountInfo));
    file.close();
    account_list.InsertPair(id, write_location);
}

void Customer::Passwd(char *id, char *passwd1, char *passwd2) {
    std::fstream file;
    //传参数进来的时候传了1和2，也即是passwd2有可能是空的，这种情况是满足条件的
    int location = account_list.FindPairs(id);
    if (location == -100000) {
        InvalidReport();
        return;
    }
    accountInfo right_info;
    file.open("AccountFile");
    file.seekg(location);
    file.read(reinterpret_cast<char *>(&right_info), sizeof(accountInfo));
    if (passwd2 == nullptr) {//则第一个就是新密码
        InvalidReport();
        return;
    } else if (strcmp(passwd1, right_info.Password) == 0) {
        strcpy(right_info.Password, passwd2);
        file.seekp(location);
        file.write(reinterpret_cast<char *>(&right_info), sizeof(accountInfo));
    } else InvalidReport();
    file.close();
}

void Customer::Useradd(char *id, char *pass_word, int priority, char *user_name) {
    InvalidReport();
}

void Customer::Delete(char *id) {
    InvalidReport();
}

void Customer::Show(char *isbn, char *name, char *author, char *keyword) {
    std::fstream file;
    if (isbn == nullptr && name == nullptr && author == nullptr && keyword != nullptr) {
        int num;
        char keys[60][60];
        KeyWordParser(keyword, num, keys);
        if (num > 0) {
            InvalidReport();
            return;
        }
        std::vector<int> to_find = keyword_book_list.FindAllPairs(keyword);
        if (to_find.empty()) {
            std::cout << "\n";
            return;
        } else {
            std::set<bookInfo> to_show;
            file.open("BookFile");
            for (auto ptr = to_find.begin(); ptr != to_find.end(); ++ptr) {
                file.seekg(*ptr);
                book tmp;
                file.read(reinterpret_cast<char *>(&(tmp.info)), sizeof(bookInfo));
                to_show.insert(tmp.info);
            }
            file.close();
            for (auto ptr = to_show.begin(); ptr != to_show.end(); ++ptr) {
                bookInfo tmp = *ptr;
                _ShowABook(tmp);
            }
        }
    } else if (isbn == nullptr && name == nullptr && author != nullptr && keyword == nullptr) {
        std::vector<int> to_find = author_book_list.FindAllPairs(author);
        if (to_find.empty()) {
            std::cout << "\n";
            return;
        } else {
            std::set<bookInfo> to_show;
            file.open("BookFile");
            for (auto ptr = to_find.begin(); ptr != to_find.end(); ++ptr) {
                file.seekg(*ptr);
                book tmp;
                file.read(reinterpret_cast<char *>(&(tmp.info)), sizeof(bookInfo));
                to_show.insert(tmp.info);
            }
            file.close();
            for (auto ptr = to_show.begin(); ptr != to_show.end(); ++ptr) {
                bookInfo tmp = *ptr;
                _ShowABook(tmp);
            }
        }
    } else if (isbn == nullptr && name != nullptr && author == nullptr && keyword == nullptr) {
        std::vector<int> to_find = name_book_list.FindAllPairs(name);
        if (to_find.empty()) {
            std::cout << "\n";
            return;
        } else {
            std::set<bookInfo> to_show;
            file.open("BookFile");
            for (auto ptr = to_find.begin(); ptr != to_find.end(); ++ptr) {
                file.seekg(*ptr);
                book tmp;
                file.read(reinterpret_cast<char *>(&(tmp.info)), sizeof(bookInfo));
                to_show.insert(tmp.info);
            }
            file.close();
            for (auto ptr = to_show.begin(); ptr != to_show.end(); ++ptr) {
                bookInfo tmp = *ptr;
                _ShowABook(tmp);
            }
        }
    } else if (isbn != nullptr && name == nullptr && author == nullptr && keyword == nullptr) {
        int location = isbn_book_list.FindPairs(isbn);
        if (location == -100000) {
            std::cout << "\n";
            return;
        } else {
            book to_show;
            file.open("BookFile");
            file.seekg(location);
            file.read(reinterpret_cast<char *>(&(to_show.info)), sizeof(bookInfo));
            to_show.ShowABook();
            file.close();
        }
    } else if (isbn == nullptr && name == nullptr && author == nullptr && keyword == nullptr) {
        isbn_book_list.ShowAllBooks();
    } else {
        InvalidReport();
        return;
    }
}


void Customer::Buy(char *isbn, int quantity) {
    std::fstream file;
    int location = isbn_book_list.FindPairs(isbn);
    if (location == -100000) {
        InvalidReport();
        return;
    }
    file.open("BookFile");
    file.seekg(location);
    bookInfo to_buy;
    file.read(reinterpret_cast<char *>(&to_buy), sizeof(bookInfo));
    if (to_buy.number < quantity) {
        file.close();
        InvalidReport();
        return;
    }
    double total = quantity * to_buy.price;
    to_buy.number -= quantity;
    file.seekp(location);
    file.write(reinterpret_cast<char *>(&to_buy), sizeof(bookInfo));
    file.close();
    selected_book[current_account] = to_buy;
    std::stringstream ss;
    std::string total_str;
    ss.clear();
    ss << total;
    ss >> total_str;
    int counter = 0;
    for (counter = 0; counter < total_str.length(); ++counter) {
        if (total_str[counter] == '.')break;
    }
    if (counter == total_str.length()) {
        total_str += ".00";
    } else if (counter == total_str.length() - 1) {
        total_str += '0';
    }
    if (counter == total_str.length() - 2)total_str += '0';
    std::cout << total_str << std::endl;
    RecordAnEntry(total);

}


void Customer::Select(char *isbn) {
    InvalidReport();
}

void Customer::Modify(char *isbn, char *name, char *author, char *keyword, double price) {
    InvalidReport();
}

void Customer::Import(int quantity, double cost) {
    InvalidReport();
}

void Customer::ReportMyself() {
    InvalidReport();
}

void Customer::ShowFinance(int time) {
    InvalidReport();
}

void Customer::ShowFinance() {
    InvalidReport();
}

void Customer::ReportFinance() {
    InvalidReport();
}

void Customer::ReportEmployee() {
    InvalidReport();
}

void Customer::Log() {
    InvalidReport();
}

Visitor::Visitor() {
    info.rank = 0;
    memset(info.Password, '\0', sizeof(info.Password));
    memset(info.UserID, '\0', sizeof(info.UserID));
    memset(info.Username, '\0', sizeof(info.Username));
}

accountInfo Visitor::GetInfo() {
    return this->info;
}

void Visitor::InputInfo(accountInfo &tmp) {
    this->info.rank = tmp.rank;
    strcpy(this->info.Password, tmp.Password);
    strcpy(this->info.UserID, tmp.UserID);
    strcpy(this->info.Username, tmp.Username);
}

void Visitor::Su(char *id, char *pass_word) {
    std::fstream file;
    int location = account_list.FindPairs(id);
    if (location == -100000) {
        InvalidReport();
        return;
    } else {
        accountInfo tmp;
        file.open("AccountFile");
        file.seekg(location);
        file.read(reinterpret_cast<char *>(&tmp), sizeof(accountInfo));
        file.close();//把它的信息读出来
        accountInfo your_info = current_account->GetInfo();
        if (pass_word == nullptr) {
            if (your_info.rank > tmp.rank) {

                if (tmp.rank == 0)current_account = new Visitor;
                else if (tmp.rank == 1)current_account = new Customer;
                else if (tmp.rank == 3)current_account = new Employee;
                else if (tmp.rank == 7)current_account = new Manager;
                current_account->InputInfo(tmp);
                Login.push_back(current_account);

            } else InvalidReport();
        } else {
            if (strcmp(tmp.Password, pass_word) == 0) {

                if (tmp.rank == 0)current_account = new Visitor;
                else if (tmp.rank == 1)current_account = new Customer;
                else if (tmp.rank == 3)current_account = new Employee;
                else if (tmp.rank == 7)current_account = new Manager;
                current_account->InputInfo(tmp);
                Login.push_back(current_account);

            } else InvalidReport();
        }
    }
}

void Visitor::Register(char *id, char *pass_word, char *user_name) {
    std::fstream file;
    int location = account_list.FindPairs(id);
    if (location != -100000) {
        InvalidReport();
        return;
    }
    accountInfo regi;
    regi.rank = 1;
    strcpy(regi.Password, pass_word);
    strcpy(regi.UserID, id);
    strcpy(regi.Username, user_name);
    file.open("AccountFile");
    file.seekp(0, std::ios::end);
    int write_location = file.tellp();
    file.write(reinterpret_cast<char *>(&regi), sizeof(accountInfo));
    file.close();
    account_list.InsertPair(id, write_location);
}

void Visitor::Passwd(char *id, char *passwd1, char *passwd2) {
    InvalidReport();
}

void Visitor::Useradd(char *id, char *pass_word, int priority, char *user_name) {
    InvalidReport();
}

void Visitor::Delete(char *id) {
    InvalidReport();
}

void Visitor::Show(char *isbn, char *name, char *author, char *keyword) {
    InvalidReport();
}

void Visitor::Buy(char *isbn, int quantity) {
    InvalidReport();
}

void Visitor::Select(char *isbn) {
    InvalidReport();
}

void Visitor::Modify(char *isbn, char *name, char *author, char *keyword, double price) {
    InvalidReport();
}

void Visitor::Import(int quantity, double cost) {
    InvalidReport();
}

void Visitor::ReportMyself() {
    InvalidReport();
}

void Visitor::ShowFinance(int time) {
    InvalidReport();
}

void Visitor::ShowFinance() {
    InvalidReport();
}

void Visitor::ReportFinance() {
    InvalidReport();
}

void Visitor::ReportEmployee() {
    InvalidReport();
}

void Visitor::Log() {
    InvalidReport();
}

//void Cast(People *&current_account, accountInfo &tmp) {
//    
//    if (tmp.rank == 0)current_account = new Visitor;
//    else if (tmp.rank == 1)current_account = new Customer;
//    else if (tmp.rank == 3)current_account = new Employee;
//    else if (tmp.rank == 7)current_account = new Manager;
//    current_account->InputInfo(tmp);
//}


