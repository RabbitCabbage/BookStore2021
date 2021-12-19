//
// Created by lu'ren'jia'd's on 2021/12/15.
//

#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>

struct bookInfo {
    char name[70];
    char author[70];
    char ISBN[30];
    char keyword[70][70];
    int number = 0;
    double price=0;
};

bool operator<(const bookInfo &lhs, const bookInfo &rhs);


class book {
public:
    bookInfo info;

    book();

    void ShowABook();

};

void _ShowABook(bookInfo &info);

#endif //BOOK_H
