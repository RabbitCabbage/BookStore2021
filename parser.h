//
// Created by lu'ren'jia'd's on 2021/12/17.
//

#ifndef PARSER_H
#define PARSER_H
int SkipWhiteSpace(const char *command, int &index);//返回跳过空格后字符索引

void WhiteSpace_head(char *command);//处理行首空格

void WhiteSpace_end(char *command);//处理命令行后面的空格

bool KeywordExamine(const char *keyword);

void SuParser(char *command);//以栈来维护，登入账号推入栈

void Logout();//退出栈

void RegisterParser(char *command);//以块链维护账户信息

void PasswdParser(char *command);//通过块链找到账户信息

void UseraddParser(char *command);//以块链维护账户信息

void DeleteParser(char *command);//先通过栈寻找是否登陆，再通过块链删除

void ShowParser(char *command);//图书信息由另一个文件的块链储存

void BuyParser(char *command);//通过块链找到信息并修改

void SelectParser(char *command);//通过块链找到信息，同时在该类中记录选中的图书

void ModifyParser(char *command);//通过记录的信息在块链中修改

void ImportParser(char *command);//通过记录的信息在块链中修改

void ShowFinanceParser(char *command);

bool UserNameCheck(const char *username);//用于鲁棒性用户名检查

bool idCheck(const char *str);//用于id，密码这两类字符串检查

bool PriorityCheck(const char *priority);

bool ISBNCheck(const char *isbn);

bool NameCheck(const char *name);

bool KeywordCheck(const char *keyword);

bool QuantityCheck(const char* quantity);

bool PriceCheck(const char* price);

double TransPrice(const char *price);

long long TransQuantity(const char *quantity);

bool IsNum(char a);

bool IsLetter(char a);

bool IsVisibal(char a);

void KeyWordParser(const char *keyword,int& num,char keys[][60]);

bool KeywordRepeated(const char *keyword);

void RemoveQuotation(char* str);

bool PassWordCheck(char* passwd);
#endif
