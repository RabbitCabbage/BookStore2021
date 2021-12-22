//
// Created by lu'ren'jia'd's on 2021/12/17.
//
#include <cstring>
#include <vector>
#include <map>
#include <iomanip>
#include "account.h"
#include "parser.h"

const char *delim = " ";
extern std::map<People *, bookInfo> selected_book;
extern People *current_account;
extern std::vector<People *> Login;
extern Visitor *original_visitor;

bool KeywordExamine(const char *keyword) {
    if (strcmp(keyword, "quit") == 0 || strcmp(keyword, "exit") == 0 || strcmp(keyword, "su") == 0 ||
        strcmp(keyword, "logout") == 0 || strcmp(keyword, "register") == 0 || strcmp(keyword, "passwd") == 0 ||
        strcmp(keyword, "useradd") == 0 || strcmp(keyword, "delete") == 0 || strcmp(keyword, "show") == 0 ||
        strcmp(keyword, "buy") == 0 || strcmp(keyword, "select") == 0 || strcmp(keyword, "modify") == 0 ||
        strcmp(keyword, "import") == 0 || strcmp(keyword, "report myself") == 0 ||
        strcmp(keyword, "show finance") == 0 || strcmp(keyword, "report finance") == 0 ||
        strcmp(keyword, "report employee") == 0 || strcmp(keyword, "log") == 0) {
        return true;
    } else { return false; }
}

void WhiteSpace_head(char *command) {
    int index = 0, i;
    while (command[index] == ' ')++index;//得到首个不是空格的字符
    for (i = 0; command[index] != '\0'; ++index, ++i) {
        command[i] = command[index];
    }
    command[i] = '\0';
}

void WhiteSpace_end(char *command) {
    unsigned long index = strlen(command);
    while (command[index - 1] == ' ')index--;
    command[index] = '\0';
}

int SkipWhiteSpace(const char *command, int &index) {
    int i = index;
    while (command[i] == ' ')++i;
    return i;
}


void SuParser(char *command) {
    char *id = strtok(command, delim);
    if (id == nullptr) {
        InvalidReport();
        return;
    }
    char *passwd = strtok(nullptr, "\0");
    if (idCheck(id) && PassWordCheck(passwd)) {
        current_account->Su(id, passwd);//tomdo 之后的current信息已经发生了变化，类型变换了
    } else InvalidReport();
}

void Logout() {
    if (Login.empty())InvalidReport();
    else {
        Login.pop_back();
        selected_book.erase(current_account);
        if (Login.empty()) {
            accountInfo visitor;
            memset(visitor.Username, '\0', sizeof(visitor.Username));
            memset(visitor.UserID, '\0', sizeof(visitor.UserID));
            memset(visitor.Password, '\0', sizeof(visitor.Password));
            visitor.rank = 0;
            delete current_account;
            current_account = original_visitor;
            current_account->InputInfo(visitor);
        } else {
            delete current_account;
            accountInfo tmp = (Login.back())->GetInfo();
            //这里使用了多态，login里面的指针都是基类的指针，但是他们都指向某一个派生类，因此可以调用虚函数实现多态
            if (tmp.rank == 0) {
                Visitor *alt = nullptr;
                current_account = new Visitor;
                //搞一个临时的派生类指针，以便于current——account指针直接赋值为login里面的指针，然后析构，防止内存泄漏
                alt = dynamic_cast<Visitor *>(current_account);
                current_account = reinterpret_cast<Visitor *>(Login.back());
                delete alt;
            } else if (tmp.rank == 1) {
                Customer *alt = nullptr;
                current_account = new Customer;
                alt = dynamic_cast<Customer *>(current_account);
                delete alt;
                current_account = reinterpret_cast<Customer *>(Login.back());
            } else if (tmp.rank == 3) {
                Employee *alt;
                current_account = new Employee;
                alt = dynamic_cast<Employee *>(current_account);
                current_account = reinterpret_cast<Employee *>(Login.back());
                delete alt;
            } else if (tmp.rank == 7) {
                Manager *alt;
                current_account = new Manager;
                alt = dynamic_cast<Manager *>(current_account);
                current_account = reinterpret_cast<Manager *>(Login.back());
                delete alt;
            }
        }
    }
}

void RegisterParser(char *command) {
    char *id = strtok(command, delim);
    char *passwd = strtok(nullptr, delim);
    char *username = strtok(nullptr, "\0");
    if (id == nullptr || passwd == nullptr || username == nullptr) {
        InvalidReport();
        return;
    }
    if (UserNameCheck(username) && idCheck(id) && idCheck(passwd))current_account->Register(id, passwd, username);
    else InvalidReport();
}

void PasswdParser(char *command) {
    char *id = strtok(command, delim);
    char *passwd1 = strtok(nullptr, delim);
    if (id == nullptr || passwd1 == nullptr) {
        InvalidReport();
        return;
    }
    char *passwd2 = strtok(nullptr, "\0");
    if (idCheck(id) && PassWordCheck(passwd1) && PassWordCheck(passwd2))
        current_account->Passwd(id, passwd1, passwd2);
    else InvalidReport();
}

void UseraddParser(char *command) {
    char *id = strtok(command, delim);
    char *passwd = strtok(nullptr, delim);
    char *priority = strtok(nullptr, delim);
    char *username = strtok(nullptr, "\0");
    if (id == nullptr || passwd == nullptr || priority == nullptr || username == nullptr) {
        InvalidReport();
        return;
    }
    if (UserNameCheck(username) && idCheck(id) && idCheck(passwd) && PriorityCheck(priority))
        current_account->Useradd(id, passwd, priority[0] - '0', username);
    else InvalidReport();
}

void DeleteParser(char *command) {
    char *id = strtok(command, "\0");
    if (id == nullptr) {
        InvalidReport();
        return;
    }
    if (idCheck(id))current_account->Delete(id);
    else InvalidReport();
}

//to do 请仔细研读图书部分的报错方式，指令模式，注意鲁棒性
//to do 传入的参数可能是空指针，注意报错
//to do 你的鲁棒性，各种check
void ShowParser(char *command) {
    char *isbn = nullptr, *name = nullptr, *author = nullptr, *keyword = nullptr;
    if (strcmp(command, "\0") == 0)current_account->Show(isbn, name, author, keyword);
    else {
        char *invalid = strtok(command, "=");

        if (strcmp(invalid, "-ISBN") == 0) {
            isbn = strtok(nullptr, " ");
            if (isbn == nullptr || !ISBNCheck(isbn)) {
                InvalidReport();
                return;
            }
        } else if (strcmp(invalid, "-name") == 0) {
            name = strtok(nullptr, " ");
            RemoveQuotation(name);
            if (name == nullptr || !NameCheck(name)) {
                InvalidReport();
                return;
            }
        } else if (strcmp(invalid, "-author") == 0) {
            author = strtok(nullptr, " ");
            RemoveQuotation(author);
            if (author == nullptr || !NameCheck(author)) {
                InvalidReport();
                return;
            }
        } else if (strcmp(invalid, "-keyword") == 0) {
            keyword = strtok(nullptr, " ");
            RemoveQuotation(keyword);
            if (keyword == nullptr || !KeywordCheck(keyword)) {
                InvalidReport();
                return;
            }
        } else {
            InvalidReport();
            return;
        }
        invalid = strtok(nullptr, "=");
        if (invalid != nullptr) {
            InvalidReport();
            return;
        }
        current_account->Show(isbn, name, author, keyword);
    }
}

void BuyParser(char *command) {
    char *isbn = strtok(command, delim);
    char *quantity = strtok(nullptr, "\0");
    if (isbn == nullptr || quantity == nullptr) {
        InvalidReport();
        return;
    }
    if (ISBNCheck(isbn) && QuantityCheck(quantity)) {
        int quan = TransQuantity(quantity);
        current_account->Buy(isbn, quan);
    } else InvalidReport();
}

void SelectParser(char *command) {
    char *isbn = command;
    if (isbn == nullptr || strcmp(isbn, "\0") == 0) {
        InvalidReport();
        return;
    }
    if (ISBNCheck(isbn))current_account->Select(isbn);
    else InvalidReport();
}

void ModifyParser(char *command) {
    char *isbn = nullptr, *name = nullptr, *author = nullptr, *keyword = nullptr, *price = nullptr;
    char *invalid = strtok(command, "=");
    while (invalid != nullptr) {
        if (strcmp(invalid, "-ISBN") == 0) {
            isbn = strtok(nullptr, " ");
            if (isbn == nullptr || !ISBNCheck(isbn)) {
                InvalidReport();
                return;
            }
        } else if (strcmp(invalid, "-name") == 0) {
            name = strtok(nullptr, " ");
            RemoveQuotation(name);
            if (name == nullptr || !NameCheck(name)) {
                InvalidReport();
                return;
            }
        } else if (strcmp(invalid, "-author") == 0) {
            author = strtok(nullptr, " ");
            RemoveQuotation(author);
            if (author == nullptr || !NameCheck(author)) {
                InvalidReport();
                return;
            }
        } else if (strcmp(invalid, "-keyword") == 0) {
            keyword = strtok(nullptr, " ");
            RemoveQuotation(keyword);
            if (keyword == nullptr || !KeywordCheck(keyword)) {
                InvalidReport();
                return;
            }
        } else if (strcmp(invalid, "-price") == 0) {
            price = strtok(nullptr, delim);
            if (price == nullptr || !PriceCheck(price)) {
                InvalidReport();
                return;
            }
        } else if (strcmp(invalid, "| -ISBN") == 0) {
            if (isbn != nullptr) {
                InvalidReport();
                return;
            } else {
                isbn = strtok(nullptr, " ");
                if (isbn == nullptr || !ISBNCheck(isbn)) {
                    InvalidReport();
                    return;
                }
            }
        } else if (strcmp(invalid, "| -name") == 0) {
            if (name != nullptr) {
                InvalidReport();
                return;
            } else {
                name = strtok(nullptr, " ");
                RemoveQuotation(name);
                if (name == nullptr || !NameCheck(name)) {
                    InvalidReport();
                    return;
                }
            }
        } else if (strcmp(invalid, "| -author") == 0) {
            if (author != nullptr) {
                InvalidReport();
                return;
            } else {
                author = strtok(nullptr, " ");
                RemoveQuotation(author);
                if (author == nullptr || !NameCheck(author)) {
                    InvalidReport();
                    return;
                }
            }
        } else if (strcmp(invalid, "| -keyword") == 0) {
            if (keyword != nullptr) {
                InvalidReport();
                return;
            } else {
                keyword = strtok(nullptr, " ");
                RemoveQuotation(keyword);
                if (keyword == nullptr || !KeywordCheck(keyword)) {
                    InvalidReport();
                    return;
                }
            }
        } else if (strcmp(invalid, "| -price") == 0) {
            if (price != nullptr) {
                InvalidReport();
                return;
            } else {
                price = strtok(nullptr, delim);
                if (price == nullptr || !PriceCheck(price)) {
                    InvalidReport();
                    return;
                }
            }
        } else {
            InvalidReport();
            return;
        }
        invalid = strtok(nullptr, "=");
    }
    double trans_price = -1;
    if (price != nullptr) trans_price = TransPrice(price);
    current_account->Modify(isbn, name, author, keyword, trans_price);
}
//to do 信息可能是空，这里没有处理

void ImportParser(char *command) {
    char *quantity = strtok(command, delim);
    char *total = strtok(nullptr, "\0");
    if (quantity == nullptr || total == nullptr) {
        InvalidReport();
        return;
    }
    if (QuantityCheck(quantity) && PriceCheck(total)) {
        double total_cost = TransPrice(total);
        int quan = TransQuantity(quantity);
        current_account->Import(quan, total_cost);
    } else {
        InvalidReport();
        return;
    }
}

void ShowFinanceParser(char *command) {
    if (strcmp(command, "\0") == 0)current_account->ShowFinance();
    else {
        if (QuantityCheck(command)) {
            int time = TransQuantity(command);
            current_account->ShowFinance(time);
        } else InvalidReport();
    }
}

bool UserNameCheck(const char *username) {
    if (username == nullptr)return false;
    for (int i = 0; i < strlen(username); ++i) {
        if (!IsVisibal(username[i]))return false;
    }
    if (strlen(username) > 30)return false;
    return true;
}

bool idCheck(const char *str) {
    if (str == nullptr)return false;
    for (int i = 0; i < strlen(str); ++i) {
        if (!(IsLetter(str[i]) || IsNum(str[i]) || str[i] == '_'))return false;
    }
    if (strlen(str) > 30)return false;
    return true;
}

bool PriorityCheck(const char *priority) {
    if (priority == nullptr || strlen(priority) > 1)return false;
    if (IsNum(priority[0])) {
        if (*priority - '0' == 3 || *priority - '0' == 1 || *priority == '0' || *priority - '0' == 7)return true;
        else return false;
    } else return false;
}

bool IsNum(char a) {
    if (a >= '0' && a <= '9')return true;
    else return false;
}

bool IsLetter(char a) {
    if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z')) return true;
    else return false;
}

bool IsVisibal(char a) {
    if ((a >= 0 && a <= 32) || a == 127)return false;
    else return true;
}

bool ISBNCheck(const char *isbn) {
    if (strlen(isbn) > 20)return false;
    for (int i = 0; i < strlen(isbn); ++i) {
        if (!IsVisibal(isbn[i]))return false;
    }
    return true;
}

bool NameCheck(const char *name) {
    if (strlen(name) > 60)return false;
    for (int i = 0; i < strlen(name); ++i) {
        if ((!IsVisibal(name[i])) || name[i] == '\"')return false;
    }
    return true;
}

bool KeywordCheck(const char *keyword) {
    if (strlen(keyword) > 60)return false;
    for (int i = 0; i < strlen(keyword); ++i) {
        if ((!IsVisibal(keyword[i])) || keyword[i] == '\"')return false;
    }
    return true;
}

bool QuantityCheck(const char *quantity) {
    //   检查是否是全部是数字,以及是否合法
    if (quantity == nullptr)return false;
    if (strlen(quantity) > 10)return false;
    for (int i = 0; i < strlen(quantity); ++i) {
        if (!IsNum(quantity[i]))return false;
    }
    long long trans = TransQuantity(quantity);
    if (trans > 2147483647)return false;
    else return true;
}

bool PriceCheck(const char *price) {
    if (strlen(price) > 13)return false;
    bool have_dot = false;
    for (int i = 0; i < strlen(price); ++i) {
        if (!IsNum(price[i]) && price[i] != '.')return false;
        if (price[i] == '.')have_dot = true;
    }
    if (price != nullptr && have_dot) {
        int counter = 0;
        for (int i = strlen(price) - 1; price[i] != '.'; --i, ++counter);
        if (counter > 2)return false;
    }
    return true;
}

double TransPrice(const char *price) {
    if (price == nullptr)return 0;
    double trans = 0;
    std::stringstream ss;
    ss.clear();
    ss.setf(std::ios::fixed);
    ss << std::setprecision(2) << price;
    ss >> trans;
    return trans;
}

long long TransQuantity(const char *quantity) {
    if (quantity == nullptr)return 0;
    long long trans = 0;
    for (int i = 0; i < strlen(quantity); ++i) {
        trans *= 10;
        trans += quantity[i] - '0';
    }
    return trans;
}

void KeyWordParser(const char *keyword_, int &num, char keys[][60]) {
    char keyword[65];
    strcpy(keyword, keyword_);
//     std::vector<char *> keys;
//    if (keyword[0] == '|') {
//        keyword = &keyword[1];
//    }
    num = 0;
    char *token = strtok(keyword, "|");
    strcpy(keys[num], token);
    while (token != nullptr) {
        token = strtok(nullptr, "|");
        if (token != nullptr) {
            num++;
            strcpy(keys[num], token);
        }
    }

}

bool KeywordRepeated(const char *keyword) {
    char alt[65];
    std::vector<char *> parsed;
    strcpy(alt, keyword);
    char *token = strtok(alt, "|");
    while (token != nullptr) {
        if (parsed.empty())parsed.push_back(token);
        else {
            for (auto &ptr: parsed) {
                if (strcmp(ptr, token) == 0)return true;
            }
            parsed.push_back(token);
        }
        token = strtok(nullptr, "|");
    }
    return false;
}

void RemoveQuotation(char *str) {
    if (str != nullptr && str[0] == '\"' && str[strlen(str) - 1] == '\"') {
        unsigned long len = strlen(str);
        str[len - 1] = '\0';
        len--;
        for (int i = 1; i < len; ++i) {
            str[i - 1] = str[i];
        }
        str[len - 1] = '\0';
    }
}

bool PassWordCheck(char *str) {
    if (str == nullptr)return true;
    for (int i = 0; i < strlen(str); ++i) {
        if (!(IsLetter(str[i]) || IsNum(str[i]) || str[i] == '_'))return false;
    }
    if (strlen(str) > 30)return false;
    return true;
}