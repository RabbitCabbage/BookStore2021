//
// Created by lu'ren'jia'd's on 2021/12/17.
//
#include "book.h"
#include <cstring>
#include <iomanip>

book::book() {
    info.price = 0;
    for (int i = 0; i < 70; ++i)
        memset(info.keyword[i], '\0', sizeof(info.keyword[i]));
    strcpy(info.name, "\0");
    strcpy(info.ISBN, "\0");
    strcpy(info.author, "\0");
}

void book::ShowABook() {
    std::cout << info.ISBN << '\t';
    if (strcmp(info.name, "\0") != 0)std::cout << info.name << '\t';
    else std::cout << "\t";
    if (strcmp(info.author, "\0") != 0)std::cout << info.author << '\t';
    else std::cout << "\t";
    std::string keywords;
    for (int i = 0; strcmp(info.keyword[i], "\0") != 0; ++i) {
        int j = 0;
        while (info.keyword[i][j] != '\0') {
            keywords += info.keyword[i][j];
            ++j;
        }
        keywords += '|';
    }
    if (!keywords.empty())keywords.pop_back();
    std::cout << keywords << '\t';

    std::stringstream ss;
    std::string price_str;
    ss.clear();
    ss.setf(std::ios::fixed);
    ss << std::setprecision(2) << info.price;
    ss >> price_str;
    std::cout << price_str << '\t' << info.number << '\n';
}

bool operator<(const bookInfo &lhs, const bookInfo &rhs) {
    if (strcmp(lhs.ISBN, rhs.ISBN) < 0)return true;
    else return false;
}

void _ShowABook(bookInfo &info) {
    std::cout << info.ISBN << '\t';
    if (strcmp(info.name, "\0") != 0)std::cout << info.name << '\t';
    else std::cout << "\t";
    if (strcmp(info.author, "\0") != 0)std::cout << info.author << '\t';
    else std::cout << "\t";
    std::string keywords;
    for (int i = 0; strcmp(info.keyword[i], "\0") != 0; ++i) {
        int j = 0;
        while (info.keyword[i][j] != '\0') {
            keywords += info.keyword[i][j];
            ++j;
        }
        keywords += '|';
    }
    if (!keywords.empty())keywords.pop_back();
    std::cout << keywords << '\t';

    std::stringstream ss;
    std::string price_str;
    ss.clear();
    ss.setf(std::ios::fixed);
    ss << std::setprecision(2) << info.price;
    ss >> price_str;
    std::cout << price_str << '\t' << info.number << '\n';
}
