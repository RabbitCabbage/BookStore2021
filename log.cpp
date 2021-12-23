//
// Created by lu'ren'jia'd's on 2021/12/17.
//

#include "log.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>

extern People *current_account;
extern std::map<People *, bookInfo> selected_book;

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

