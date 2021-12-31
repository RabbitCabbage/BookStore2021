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

void Import_record(int num, double cost);

void Buy_record(int num, double cost, bookInfo to_buy);

void ReportFinanceLog();

void BuyLog(char *isbn, int quantity, double total);

void ImportLog(char *isbn, int quantity, double cost);

void ShowLog(char *show_argv, char *type);

void ModifyLog(bookInfo old,bookInfo now);

void RegisterLog(char *id, char *pass_word, char *user_name);

void UseraddLog(char *id, char *pass_word, int priority, char *user_name);

void DeleteLog(char *id);

void PasswdLog(char *id, char *passwd1, char *passwd2);

void ReportMyselfLog();

void ReportAnEmployee(char *id);

void ReportAllEmployee();

void LogLog();


#endif
