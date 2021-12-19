//
// Created by lu'ren'jia'd's on 2021/12/15.
//

#ifndef UNTITLED1_COMMAND_H
#define UNTITLED1_COMMAND_H

#include <string>
#include "account.h"

void Initialize();

void CommandCarryOut(char *command, bool &running);

char *CommandKeyword(char *command);//返回首个指令token

void InvalidReport();

bool Blank(const char *command);

void Conduct(bool &running, char *keyword, char *command);



#endif //UNTITLED1_COMMAND_H
