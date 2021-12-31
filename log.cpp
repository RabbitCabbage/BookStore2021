//
// Created by lu'ren'jia'd's on 2021/12/17.
//

#include "log.h"
#include "blocklist.h"
#include "book.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <vector>

const char line[61]{"=================================="};
extern People *current_account;
extern std::map<People *, bookInfo> selected_book;
extern BlockList work_log_list;
extern BlockList account_list;

void RecordAnEntry(double price) {
    std::fstream log_file;
    log_file.open("FinanceRecord");
    log_file.seekp(0, std::ios::end);
    log_file.write(reinterpret_cast<char *>(&price), sizeof(double));
    log_file.close();
}

std::string ShowEntry(int num) {
    std::fstream log_file;
    if (num == 0)return "\n";
    std::string report;
    double income = 0, expense = 0, sum;
    log_file.open("FinanceRecord");
    log_file.seekg(0, std::ios::end);
    int location = log_file.tellg();
    location -= num * sizeof(double);
    if (location < 0) {
        return "Invalid\n";
    }
    log_file.seekg(location);
    for (int i = 0; i < num; ++i) {
        log_file.read(reinterpret_cast<char *>(&sum), sizeof(double));
        if (sum > 0)income += sum;
        if (sum < 0)expense += sum;
    }
    log_file.close();
    std::stringstream ss;
    std::string price_str;
    ss.clear();
    price_str.clear();
    ss.setf(std::ios::fixed);
    ss << std::setprecision(2) << income;
    ss >> price_str;
    report += "+ " + price_str;
    ss.clear();
    price_str.clear();
    ss.setf(std::ios::fixed);
    ss << std::setprecision(2) << (-1.0) * expense;
    ss >> price_str;
    if (price_str == "-0.00")price_str = "0.00";
    report += " - " + price_str;
    report += "\n";
    return report;
}

std::string ShowAllEntry() {
    std::fstream log_file;
    std::string report;
    double expense = 0, income = 0, sum;
    log_file.open("FinanceRecord");
    log_file.seekg(0);
    while (log_file.peek() != EOF) {
        log_file.read(reinterpret_cast<char *>(&sum), sizeof(double));
        if (sum > 0)income += sum;
        if (sum < 0)expense += sum;
    }
    log_file.close();
    std::stringstream ss;
    std::string price_str;
    ss.clear();
    price_str.clear();
    ss.setf(std::ios::fixed);
    ss << std::setprecision(2) << income;
    ss >> price_str;
    report += "+ " + price_str;
    ss.clear();
    price_str.clear();
    ss.setf(std::ios::fixed);
    ss << std::setprecision(2) << (-1.0) * expense;
    ss >> price_str;
    if (price_str == "-0.00")price_str = "0.00";
    report += " - " + price_str;
    report += "\n";
    return report;
}

void Buy_record(int num, double cost, bookInfo to_buy) {
    std::fstream finance;
    finance.setf(std::ios::fixed);
    finance.open("FinanceReport", std::ios::app);
    finance.setf(std::ios::fixed);
    finance << "User: Name: " << current_account->GetInfo().Username << "\tID: " << current_account->GetInfo().UserID
            << "\t\n";
    finance << "Buy \nBook-ISBN: " << selected_book[current_account].ISBN << "\tNumber: " << num << "\t\n";
    finance << "Income: " << std::setprecision(2) << cost << "\n";
    finance << "\n";
    finance.close();
}

void Import_record(int num, double cost) {
    std::fstream finance;
    finance.open("FinanceReport", std::ios::app);
    finance.setf(std::ios::fixed);
    finance << "User: Name: " << current_account->GetInfo().Username << "\t" << "ID: "
            << current_account->GetInfo().UserID << "\t\n";
    finance << "Import \nBook-ISBN: " << selected_book[current_account].ISBN << "\t" << "\nNumber: " << num << "\t\n";
    finance << "Expense: -" << std::setprecision(2) << cost << "\n";
    finance << "\n";
    finance.close();
}

void ReportFinanceLog() {
    std::fstream finance;
    finance.open("FinanceReport");
    finance.seekp(0, std::ios::end);
    std::string total = ShowAllEntry();
    finance << line;
    finance << '\n';
    finance << "Total:     " << total;
    finance.close();
    std::cout << "The report is in the file named \"Finance Report\"\n";
}

void PasswdLog(char *id, char *passwd1, char *passwd2) {
    char s[400];
    strcpy(s, "Modify the password of User ");
    strcat(s, id);
    strcat(s, "\nform ");
    strcat(s, passwd1);
    strcat(s, "\nto ");
    strcat(s, passwd2);
    strcat(s, "\n");
    std::fstream work;
    work.open("WorkReport(binary)");
    work.seekp(0, std::ios::end);
    int location = work.tellp();
    work.write(reinterpret_cast<char *>(&s), sizeof(s));
    work.close();
    work_log_list.InsertPair(current_account->GetInfo().UserID, location);
}

void DeleteLog(char *id) {
    char s[400];
    strcpy(s, "Delete User ");
    strcat(s, id);
    strcat(s, "\n");
    std::fstream work;
    work.open("WorkReport(binary)");
    work.seekp(0, std::ios::end);
    int location = work.tellp();
    work.write(reinterpret_cast<char *>(&s), sizeof(s));
    work.close();
    work_log_list.InsertPair(current_account->GetInfo().UserID, location);
}

void UseraddLog(char *id, char *pass_word, int priority, char *user_name) {
    char s[400];
    strcpy(s, "Add User: \nID: ");
    strcat(s, id);
    strcat(s, "\nPassword: ");
    strcat(s, pass_word);
    strcat(s, "\nPriority: ");
    char pri[2];
    pri[0] = (char) ('0' + priority);
    pri[1] = '\0';
    strcat(s, pri);
    strcat(s, "\nUsername: ");
    strcat(s, user_name);
    strcat(s, "\n");
    std::fstream work;
    work.open("WorkReport(binary)");
    work.seekp(0, std::ios::end);
    int location = work.tellp();
    work.write(reinterpret_cast<char *>(&s), sizeof(s));
    work.close();
    work_log_list.InsertPair(current_account->GetInfo().UserID, location);

}

void RegisterLog(char *id, char *pass_word, char *user_name) {
    char s[400];
    strcpy(s, "Register User: \nID: ");
    strcat(s, id);
    strcat(s, "\nPassword: ");
    strcat(s, pass_word);
    strcat(s, "\nUsername: ");
    strcat(s, user_name);
    strcat(s, "\n");
    std::fstream work;
    work.open("WorkReport(binary)");
    work.seekp(0, std::ios::end);
    int location = work.tellp();
    work.write(reinterpret_cast<char *>(&s), sizeof(s));
    work.close();
    work_log_list.InsertPair(current_account->GetInfo().UserID, location);

}

void ShowLog(char *show_argv, char *type) {
    char s[400];
    strcpy(s, "Show books\n");
    strcat(s, type);
    strcat(s, " = ");
    strcat(s, show_argv);
    strcat(s, "\n");
    std::fstream work;
    work.open("WorkReport(binary)");
    work.seekp(0, std::ios::end);
    int location = work.tellp();
    work.write(reinterpret_cast<char *>(&s), sizeof(s));
    work.close();
    work_log_list.InsertPair(current_account->GetInfo().UserID, location);

}

void ModifyLog(bookInfo old, bookInfo now) {
    char old_price[12];
    char now_price[12];
    std::stringstream ss;
    ss.setf(std::ios::fixed);
    ss.clear();
    ss << std::setprecision(2) << old.price;
    ss >> old_price;
    ss.clear();
    ss << std::setprecision(2) << now.price;
    ss >> now_price;
    char s[400];
    strcpy(s, "Modify the book\nFrom\n");
    if (strcmp(old.ISBN, now.ISBN) != 0) {
        strcat(s, "ISBN:   \t") ;
        if (strcmp(old.ISBN, "\0") == 0)strcat(s, "null");
        else strcat(s, old.ISBN);
        strcat(s, "\n");
    }
    if (strcmp(old.name, now.name) != 0) {
        strcat(s, "name:   \t");
        if (strcmp(old.name, "\0") == 0)strcat(s, "null");
        else strcat(s, old.name);
        strcat(s, "\n");
    }
    if (strcmp(old.author, now.author) != 0) {
        strcat(s, "author: \t");
        if (strcmp(old.author, "\0") == 0)strcat(s, "null");
        else strcat(s, old.author);
        strcat(s, "\n");
    }
    bool diff = false;
    int i;
    for (i = 0; strcmp(old.keyword[i], "\0") != 0; ++i) {
        if (strcmp(old.keyword[i], now.keyword[i]) != 0)diff = true;
    }
    if (strcmp(now.keyword[i], "\0") != 0)diff = true;
    if (diff) {
        strcat(s, "keyword:\t");
        if (strcmp(old.keyword[0], "\0") == 0)strcat(s, "null");
        else strcat(s, old.keyword[0]);
        for (int j = 1; strcmp(old.keyword[j], "\0") != 0; ++j) {
            strcat(s, "|");
            strcat(s, old.keyword[j]);
        }
        strcat(s, "\n");
    }
    if (strcmp(old_price, now_price) != 0) {
        strcat(s, "price:  \t");
        strcat(s, old_price);
        strcat(s, "\n");
    }
    strcat(s, "To\n");
    if (strcmp(old.ISBN, now.ISBN) != 0) {
        strcat(s, "ISBN:   \t");
        strcat(s, now.ISBN);
        strcat(s, "\n");
    }
    if (strcmp(old.name, now.name) != 0) {
        strcat(s, "name:   \t");
        strcat(s, now.name);
        strcat(s, "\n");
    }
    if (strcmp(old.author, now.author) != 0) {
        strcat(s, "author: \t");
        strcat(s, now.author);
        strcat(s, "\n");
    }

    if (diff) {
        strcat(s, "keyword:\t");
        strcat(s, now.keyword[0]);
        for (int j = 1; strcmp(now.keyword[j], "\0") != 0; ++j) {
            strcat(s, "|");
            strcat(s, now.keyword[j]);
        }
        strcat(s, "\n");
    }
    if (strcmp(old_price, now_price) != 0) {
        strcat(s, "price:  \t");
        strcat(s, now_price);
        strcat(s, "\n");
    }
    std::fstream work;
    work.open("WorkReport(binary)", std::ios::app);
    int location = work.tellp();
    work_log_list.InsertPair(current_account->GetInfo().UserID, location);
    work.write(reinterpret_cast<char *>(&s), sizeof(s));
    work.close();

}

void ImportLog(char *isbn, int quantity, double cost) {
    char quan[12];
    char expense[12];
    std::stringstream ss;
    ss.setf(std::ios::fixed);
    ss.clear();
    ss << quantity;
    ss >> std::setprecision(2) >> quan;
    ss.clear();
    ss << cost;
    ss >> std::setprecision(2) >> expense;
    char s[400];
    strcpy(s, "Import \nBook-ISBN ");
    strcat(s, isbn);
    strcat(s, "\nquantity: ");
    strcat(s, quan);
    strcat(s, "\nexpense: -");
    strcat(s, expense);
    strcat(s, "\n");
    std::fstream work;
    work.open("WorkReport(binary)");
    work.seekp(0, std::ios::end);
    int location = work.tellp();
    work.write(reinterpret_cast<char *>(&s), sizeof(s));
    work.close();
    work_log_list.InsertPair(current_account->GetInfo().UserID, location);

}

void BuyLog(char *isbn, int quantity, double total) {
    char quan[12];
    char income[12];
    std::stringstream ss;
    ss.setf(std::ios::fixed);
    ss.clear();
    ss << quantity;
    ss >> std::setprecision(2) >> quan;
    ss.clear();
    ss << total;
    ss >> std::setprecision(2) >> income;
    char s[400];
    strcpy(s, "Buy \nBook-ISBN: ");
    strcat(s, isbn);
    strcat(s, "\nquantity: ");
    strcat(s, quan);
    strcat(s, "\nincome: ");
    strcat(s, income);
    strcat(s, "\n");
    std::fstream work;
    work.open("WorkReport(binary)");
    work.seekp(0, std::ios::end);
    int location = work.tellp();
    work.write(reinterpret_cast<char *>(&s), sizeof(s));
    work.close();
    work_log_list.InsertPair(current_account->GetInfo().UserID, location);

}

void ReportMyselfLog() {
    std::fstream work_log, my;
    std::string filename;
    std::stringstream ss;
    ss.clear();
    ss << current_account->GetInfo().UserID;
    ss >> filename;
    filename += "'s Work Report";
    my.open(filename, std::ios::out);
    work_log.open("WorkReport(binary)");
    my << filename << "\n\n\nName: ";
    my << current_account->GetInfo().Username;
    my << "\n";
    my << line;
    my << '\n';
    std::vector<int> my_work = work_log_list.FindAllPairs(current_account->GetInfo().UserID);
    for (auto ptr = my_work.end(); ptr != my_work.begin();) {
        --ptr;
        char entry[200];
        work_log.seekg(*ptr);
        work_log.read(reinterpret_cast<char *>(&entry), sizeof(char) * 200);
        for (int i = 0; entry[i] != '\0'; ++i) {
            my << entry[i];
        }
//        my<<line;
        my << '\n';
    }
    work_log.close();
    my.close();
    std::cout << "The report is in the file named \"" << filename << "\"\n";
}

void ReportAnEmployee(char *id) {
    std::fstream work_log, my;
    std::string filename;
    std::stringstream ss;
    my.open("EmployeeReport", std::ios::app);
    my << line;
    my << '\n';
    int location = account_list.FindPairs(id);
    std::fstream tmp("AccountFile");
    tmp.seekg(location);
    accountInfo myInfo;
    tmp.read(reinterpret_cast<char *>(&myInfo), sizeof(accountInfo));
    tmp.close();
    my << "Employee Name: ";
    my << myInfo.Username << "\n";
    work_log.open("WorkReport(binary)");
    std::vector<int> my_work = work_log_list.FindAllPairs(id);
    for (auto ptr = my_work.begin(); ptr != my_work.end(); ++ptr) {
        char entry[200];
        work_log.seekg(*ptr);
        work_log.read(reinterpret_cast<char *>(&entry), sizeof(char) * 200);
        for (int i = 0; entry[i] != '\0'; ++i) {
            my << entry[i];
        }
//        my<<line;
        my << '\n';
    }
    work_log.close();
    my.close();
}

void ReportAllEmployee() {
    std::fstream file, account_file;
    account_file.open("AccountFile");
    file.open("EmployeeReport", std::ios::out);
    file << "EmployeeReport\n\n";
    file.close();
    file.open("AccountList");
    BlockList::Block current_block;
    file.read(reinterpret_cast<char *>(&current_block), sizeof(BlockList::Block));
    while (1) {
        for (int i = 0; i < current_block.CurrentSize; ++i) {
            accountInfo acc;
            account_file.seekg(current_block.second_array[i]);
            account_file.read(reinterpret_cast<char *>(&acc), sizeof(accountInfo));
            if (acc.rank == 3)ReportAnEmployee(acc.UserID);
        }
        if (current_block.Next != -100000)file.read(reinterpret_cast<char *>(&current_block), sizeof(BlockList::Block));
        else break;
    }
    file.close();
    account_file.close();

}

void LogLog() {
    std::fstream file;
    file.open("LogFile", std::ios::out);
    file << "LogFile\n\nPart1:\t Finance\nPart2:\tEmployee work\n";
    file << line;
    file << "\n";
//    std::string s = ShowAllEntry();
//    file << "Total: ";
//    file << s;
//    file << line;
    file << '\n';
    file << "\\(^_^)/  Part1:\nFinance\n\n\n";
    std::string s;
    std::fstream finance("FinanceReport");
    finance.seekg(0);
    getline(finance, s);
    getline(finance, s);
    getline(finance, s);
    getline(finance, s);
    getline(finance, s);
    while (getline(finance, s)) {
        file << s;
        file << '\n';
    }
    file << "\n\n";
    file << line;
    file << "\n";
    file << "\\(^_^)/  Part2:\n";
    ReportAllEmployee();
    std::fstream report;
    report.open("EmployeeReport");
    report.seekg(0);
    while (getline(report, s)) {
        file << s;
        file << '\n';
    }
    report.close();
    std::cout << "The log is in the file named \"LogFile\"\n";
}