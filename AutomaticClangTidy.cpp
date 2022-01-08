//
// Created by lu'ren'jia'd's on 2022/1/8.
//

#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

int main() {
    system("sudo apt install clang-tidy\n");
    system("y\n");
    system("echo Lint Check for RabbitCabbage BookStore2021\n");
    system("cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .");
    system("echo   \n");
    system("echo   \n");
    system("echo =============================MAIN.CPP=============================\n");
    system("clang-tidy --checks='' main.cpp \n");
    system("echo   \n");
    system("echo   \n");
    system("echo =============================PARSER.CPP=============================\n");
    system("clang-tidy --checks='Checks' parser.cpp \n");
    system("echo All cpp check Completed\n");
    system("echo   \n");
    system("echo   \n");
    system("echo =============================BOOK.CPP=============================\n");
    system("clang-tidy --checks='Checks' book.cpp \n");
    system("echo   \n");
    system("echo   \n");
    system("echo =============================ACCOUNT.CPP=============================\n");
    system("clang-tidy --checks='Checks' account.cpp \n");
    system("echo   \n");
    system("echo   \n");
    system("echo =============================BLOCKLIST.CPP=============================\n");
    system("clang-tidy --checks='Checks' blocklist.cpp \n");
    system("echo   \n");
    system("echo   \n");
    system("echo =============================LOG.CPP=============================\n");
    system("clang-tidy --checks='Checks' log.cpp \n");
    system("echo   \n");
    system("echo   \n");
    system("rm compile_commands.json\nrm auto\nrm makefile\nrm cmake_install.cmake\nrm cmakecache.txt\n");
    return 0;
}