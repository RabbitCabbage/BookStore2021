//
// Created by lu'ren'jia'd's on 2021/12/17.
//

#ifndef LOG_H
#define LOG_H

#include <string>
#include "account.h"
#include "book.h"

void RecordAnEntry(double price);

std::string ShowEntry(int num);

std::string ShowAllEntry();

#endif
