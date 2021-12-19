//
// Created by lu'ren'jia'd's on 2021/12/15.
//

#ifndef UNTITLED1_ACCOUNT_H
#define UNTITLED1_ACCOUNT_H

#include <vector>
#include "book.h"
#include "account.h"

void InvalidReport();


struct accountInfo {
    int rank = 0;
    char Username[40];
    char UserID[40];
    char Password[40];
};

class People {
public:
    People() = default;

    ~People() = default;

   virtual accountInfo GetInfo() = 0;

    virtual void InputInfo(accountInfo &tmp) = 0;


    virtual void Su(char *id, char *pass_word) = 0;//以栈来维护，登入账号推入栈

    virtual void Register(char *id, char *pass_word, char *user_name) = 0;//以块链维护账户信息

    virtual void Passwd(char *id, char *passwd1, char *passwd2) = 0;//通过块链找到账户信息

    virtual void Useradd(char *id, char *pass_word, int priority, char *user_name) = 0;//以块链维护账户信息

    virtual void Delete(char *id) = 0;//先通过栈寻找是否登陆，再通过块链删除

    virtual void Show(char *isbn, char *name, char *author, char *keyword) = 0;//图书信息由另一个文件的块链储存

    virtual void Buy(char *isbn, int quantity) = 0;//通过块链找到信息并修改

    virtual void Select(char *isbn) = 0;//通过块链找到信息，同时在该类中记录选中的图书

    virtual void Modify(char *isbn, char *name, char *author, char *keyword, double price) = 0;//通过记录的信息在块链中修改

    virtual void Import(int quantity, double cost) = 0;//通过记录的信息在块链中修改

    virtual void ReportMyself() = 0;//以二进制文件储存，用链表维护（每一个节点的信息为操作以及下一个这个员工的操作在文件中的位置）

    virtual void ShowFinance(int time) = 0;

    virtual void ShowFinance() = 0;

    virtual void ReportFinance() = 0;

    virtual void ReportEmployee() = 0;

    virtual void Log() = 0;//以上三个操作均存一个不同的ASCLL文件
};

class Manager : public People {
private:
    accountInfo info;

public:
    Manager();

    ~Manager() = default;

    accountInfo GetInfo();

    void InputInfo(accountInfo &tmp);

    void Su(char *id, char *pass_word);//以栈来维护，登入账号推入栈

    void Register(char *id, char *pass_word, char *user_name);//以块链维护账户信息

    void Passwd(char *id, char *passwd1, char *passed2);//通过块链找到账户信息

    void Useradd(char *id, char *pass_word, int priority, char *user_name);//以块链维护账户信息

    void Delete(char *id);//先通过栈寻找是否登陆，再通过块链删除

    void Show(char *isbn, char *name, char *author, char *keyword);//图书信息由另一个文件的块链储存

    void Buy(char *isbn, int quantity);//通过块链找到信息并修改

    void Select(char *isbn);//通过块链找到信息，同时在该类中记录选中的图书

    void Modify(char *isbn, char *name, char *author, char *keyword, double price);//通过记录的信息在块链中修改

    void Import(int quantity, double cost);//通过记录的信息在块链中修改

    void ReportMyself();//以二进制文件储存，用链表维护（每一个节点的信息为操作以及下一个这个员工的操作在文件中的位置）

    void ShowFinance(int time);

    void ShowFinance();

    void ReportFinance();

    void ReportEmployee();

    void Log();//以上三个操作均存一个不同的ASCLL文件
};

class Employee : public People {
private:
    accountInfo info;

public:
    Employee();

    ~Employee() = default;

    accountInfo GetInfo();

    void InputInfo(accountInfo &tmp);

    void Su(char *id, char *pass_word);//以栈来维护，登入账号推入栈

    void Register(char *id, char *pass_word, char *user_name);//以块链维护账户信息

    void Passwd(char *id, char *passwd1, char *passwd2);//通过块链找到账户信息

    void Useradd(char *id, char *pass_word, int priority, char *user_name);//以块链维护账户信息

    void Delete(char *id);//先通过栈寻找是否登陆，再通过块链删除

    void Show(char *isbn, char *name, char *author, char *keyword);//图书信息由另一个文件的块链储存

    void Buy(char *isbn, int quantity);//通过块链找到信息并修改

    void Select(char *isbn);//通过块链找到信息，同时在该类中记录选中的图书

    void Modify(char *isbn, char *name, char *author, char *keyword, double price);//通过记录的信息在块链中修改

    void Import(int quantity, double cost);//通过记录的信息在块链中修改

    void ReportMyself();//以二进制文件储存，用链表维护（每一个节点的信息为操作以及下一个这个员工的操作在文件中的位置）

    void ShowFinance(int time);

    void ShowFinance();

    void ReportFinance();

    void ReportEmployee();

    void Log();//以上三个操作均存一个不同的ASCLL文件
};

class Customer : public People {
private:
    accountInfo info;

public:
    Customer();

    ~Customer() = default;

    accountInfo GetInfo();

    void InputInfo(accountInfo &tmp);

    void Su(char *id, char *pass_word);//以栈来维护，登入账号推入栈

    void Register(char *id, char *pass_word, char *user_name);//以块链维护账户信息

    void Passwd(char *id, char *passwd1, char *passwd2);//通过块链找到账户信息

    void Useradd(char *id, char *pass_word, int priority, char *user_name);//以块链维护账户信息

    void Delete(char *id);//先通过栈寻找是否登陆，再通过块链删除

    void Show(char *isbn, char *name, char *author, char *keyword);//图书信息由另一个文件的块链储存

    void Buy(char *isbn, int quantity);//通过块链找到信息并修改

    void Select(char *isbn);//通过块链找到信息，同时在该类中记录选中的图书

    void Modify(char *isbn, char *name, char *author, char *keyword, double price);//通过记录的信息在块链中修改

    void Import(int quantity, double cost);//通过记录的信息在块链中修改

    void ReportMyself();//以二进制文件储存，用链表维护（每一个节点的信息为操作以及下一个这个员工的操作在文件中的位置）

    void ShowFinance(int time);

    void ShowFinance();

    void ReportFinance();

    void ReportEmployee();

    void Log();//以上三个操作均存一个不同的ASCLL文件
};

class Visitor : public People {
private:
    accountInfo info;

public:
    Visitor();

    ~Visitor() = default;

    accountInfo GetInfo();

    void InputInfo(accountInfo &tmp);

    void Su(char *id, char *pass_word);//以栈来维护，登入账号推入栈

    void Register(char *id, char *pass_word, char *user_name);//以块链维护账户信息

    void Passwd(char *id, char *passwd1, char *new_passwd2);//通过块链找到账户信息

    void Useradd(char *id, char *pass_word, int priority, char *user_name);//以块链维护账户信息

    void Delete(char *id);//先通过栈寻找是否登陆，再通过块链删除

    void Show(char *isbn, char *name, char *author, char *keyword);//图书信息由另一个文件的块链储存

    void Buy(char *isbn, int quantity);//通过块链找到信息并修改

    void Select(char *isbn);//通过块链找到信息，同时在该类中记录选中的图书

    void Modify(char *isbn, char *name, char *author, char *keyword, double price);//通过记录的信息在块链中修改

    void Import(int quantity, double cost);//通过记录的信息在块链中修改

    void ReportMyself();//以二进制文件储存，用链表维护（每一个节点的信息为操作以及下一个这个员工的操作在文件中的位置）

    void ShowFinance(int time);

    void ShowFinance();

    void ReportFinance();

    void ReportEmployee();

    void Log();//以上三个操作均存一个不同的ASCLL文件
};



#endif //UNTITLED1_ACCOUNT_H
