//
// Created by lu'ren'jia'd's on 2021/12/17.
//
#include "book.h"
#include <cstring>

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
    ss << info.price;
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
    if (counter == price_str.length() - 2)price_str += '0';
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
    ss << info.price;
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
    if (counter == price_str.length() - 2)price_str += '0';
    std::cout << price_str << '\t' << info.number << '\n';
}
