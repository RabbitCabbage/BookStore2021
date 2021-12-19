//
// Created by lu'ren'jia'd's on 2021/12/17.
//

#include "log.h"
#include <fstream>
#include <sstream>

std::fstream log_file;

void RecordAnEntry(double price) {
    log_file.open("FinanceRecord", std::ios::app);
    log_file.write(reinterpret_cast<char *>(&price), sizeof(double));
    log_file.close();
}

std::string ShowEntry(int num) {
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
    ss << income;
    ss >> price_str;
    int counter = 0;
    for (counter = 0; counter < price_str.length(); ++counter) {
        if (price_str[counter] == '.')break;
    }
    if (counter == price_str.length()) {
        price_str += ".00";
    } else if (counter == price_str.length() - 1) {
        price_str += '0';
    }
    report += "+ " + price_str;
    ss.clear();
    price_str.clear();
    ss << (-1.0) * expense;
    ss >> price_str;
    counter = 0;
    for (counter = 0; counter < price_str.length(); ++counter) {
        if (price_str[counter] == '.')break;
    }
    if (counter == price_str.length()) {
        price_str += ".00";
    } else if (counter == price_str.length() - 1) {
        price_str += '0';
    }
    report += " - " + price_str;
    report += "\n";
    return report;
}

std::string ShowAllEntry() {
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
    ss << income;
    ss >> price_str;
    int counter = 0;
    for (counter = 0; counter < price_str.length(); ++counter) {
        if (price_str[counter] == '.')break;
    }
    if (counter == price_str.length()) {
        price_str += ".00";
    } else if (counter == price_str.length() - 1) {
        price_str += '0';
    }
    report += "+ " + price_str;
    ss.clear();
    price_str.clear();
    ss << (-1.0) * expense;
    ss >> price_str;
    counter = 0;
    for (counter = 0; counter < price_str.length(); ++counter) {
        if (price_str[counter] == '.')break;
    }
    if (counter == price_str.length()) {
        price_str += ".00";
    } else if (counter == price_str.length() - 1) {
        price_str += '0';
    }
    report += " - " + price_str;
    report += "\n";
    return report;
}

