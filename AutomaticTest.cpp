#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <fstream>

using namespace std;

int main() {
    int score = 0;
    char cmd[200];
    system("cd ../BookStore2021\n");
    system("echo  Test Report for RabbitCabbage BookStore2021\n");
    system("pwd\n");
    strcpy(cmd, "cmake CmakeLists.txt\n");
    system(cmd);
    strcpy(cmd, "make\n");
    system(cmd);
    for (int i = 1; i <= 6; ++i) {
        strcpy(cmd, "./code<./Data/BasicDataSet/testcase");
        char num = static_cast<char>('0' + i);
        char number[2] = {num, '\0'};
        strcat(cmd, number);
        strcat(cmd, ".txt >out.txt\n");
        system(cmd);
        strcpy(cmd, "diff out.txt ./Data/BasicDataSet/testcase");
        strcat(cmd, number);
        strcat(cmd, "_ans.txt\n");
        int judge = system(cmd);
        if (judge == 0)score++;
        strcpy(cmd, "echo BasicDataSet/testcase");
        strcat(cmd, number);
        strcat(cmd, " Checked\n");
        system(cmd);
//        cout << location << endl;

//        strcpy(cmd, "echo BasicDataSet/testcase");
//        strcat(cmd, number);
//        strcat(cmd, " Checked\n");
//        system(cmd);
        strcpy(cmd, "rm out.txt\n");
        system(cmd);
        strcpy(cmd, "rm Keyword_BookList\n");
        system(cmd);
        strcpy(cmd, "rm AccountFile\n");
        system(cmd);
        strcpy(cmd, "rm AccountList\n");
        system(cmd);
        strcpy(cmd, "rm Author_BookList\n");
        system(cmd);
        strcpy(cmd, "rm Name_BookList\n");
        system(cmd);
        strcpy(cmd, "rm BookFile\n");
        system(cmd);
        strcpy(cmd, "rm WorkList\n");
        system(cmd);
        strcpy(cmd, "rm ISBN_BookList\n");
        system(cmd);
        strcpy(cmd, "rm FinanceReport\n");
        system(cmd);
        strcpy(cmd, "rm FinanceRecord\n");
        system(cmd);
        strcpy(cmd, "rm WorkReportBinary\n");
        system(cmd);
    }

    system("touch out.txt");
    for (int i = 1; i <= 3; ++i) {
        strcpy(cmd, "./code<./Data/BasicDataSet/testcase7/");
        char num = static_cast<char>('0' + i);
        char number[2] = {num, '\0'};
        strcat(cmd, number);
        strcat(cmd, ".txt >out.txt\n");
        system(cmd);
    }
    strcpy(cmd, "diff out.txt ./Data/BasicDataSet/testcase7/ans.txt");
    int judge2 = system(cmd);
    if (judge2 == 0)score++;
    strcpy(cmd, "echo BasicDataSet/testcase7 Checked\n");
    system(cmd);
//    strcpy(cmd, "echo BasicDataSet/testcase7 Checked\n");
//    system(cmd);
    strcpy(cmd, "rm out.txt\n");
    system(cmd);
    strcpy(cmd, "rm Keyword_BookList\n");
    system(cmd);
    strcpy(cmd, "rm AccountFile\n");
    system(cmd);
    strcpy(cmd, "rm AccountList\n");
    system(cmd);
    strcpy(cmd, "rm Author_BookList\n");
    system(cmd);
    strcpy(cmd, "rm Name_BookList\n");
    system(cmd);
    strcpy(cmd, "rm BookFile\n");
    system(cmd);
    strcpy(cmd, "rm WorkList\n");
    system(cmd);
    strcpy(cmd, "rm ISBN_BookList\n");
    system(cmd);
    strcpy(cmd, "rm FinanceReport\n");
    system(cmd);
    strcpy(cmd, "rm FinanceRecord\n");
    system(cmd);
    strcpy(cmd, "rm WorkReportBinary\n");
    system(cmd);
    system("touch out.txt");
    for (int i = 1; i <= 100; ++i) {
        strcpy(cmd, "./code<./Data/BasicDataSet/testcase8/");
        char number[4];
        stringstream ss;
        ss << i;
        ss >> number;
        strcat(cmd, number);
        strcat(cmd, ".txt >>out.txt\n");
        system(cmd);
    }
    strcpy(cmd, "diff out.txt ./Data/BasicDataSet/testcase8/ans.txt");
    int judge3 = system(cmd);
    if (judge3 == 0)score++;
    strcpy(cmd, "echo BasicDataSet/testcase8 Checked\n");
    system(cmd);
//    strcpy(cmd, "echo BasicDataSet/testcase8 Checked\n");
//    system(cmd);
    strcpy(cmd, "rm out.txt\n");
    system(cmd);
    strcpy(cmd, "rm Keyword_BookList\n");
    system(cmd);
    strcpy(cmd, "rm AccountFile\n");
    system(cmd);
    strcpy(cmd, "rm AccountList\n");
    system(cmd);
    strcpy(cmd, "rm Author_BookList\n");
    system(cmd);
    strcpy(cmd, "rm Name_BookList\n");
    system(cmd);
    strcpy(cmd, "rm BookFile\n");
    system(cmd);
    strcpy(cmd, "rm WorkList\n");
    system(cmd);
    strcpy(cmd, "rm ISBN_BookList\n");
    system(cmd);
    strcpy(cmd, "rm FinanceReport\n");
    system(cmd);
    strcpy(cmd, "rm FinanceRecord\n");
    system(cmd);
    strcpy(cmd, "rm WorkReportBinary\n");
    system(cmd);
    for (int i = 1; i <= 2; ++i) {
        for (int j = 1; j <= 10; ++j) {
            strcpy(cmd, "./code<./Data/AdvancedDataSet/testcase");
            char num = static_cast<char>('0' + i);
            char number[2] = {num, '\0'};
            strcat(cmd, number);
            strcat(cmd, "/");
            char in_number[3];
            if (j <= 9) {
                char in_num = static_cast<char>('0' + j);
                in_number[0] = in_num;
                in_number[1] = '\0';
                strcat(cmd, in_number);
            } else {
                strcat(cmd, "10");
                strcpy(in_number, "10");
            }
            strcat(cmd, ".in >out.txt\n");
            system(cmd);
            strcpy(cmd, "diff out.txt ./Data/AdvancedDataSet/testcase");
            strcat(cmd, number);
            strcat(cmd, "/");
            strcat(cmd, in_number);
            strcat(cmd, ".out\n");
            int judge4 = system(cmd);
            if (judge4 == 0)score++;
            strcpy(cmd, "echo AdvancedDataSet/testcase");
            strcat(cmd, number);
            strcat(cmd, "/");
            strcat(cmd, in_number);
            strcat(cmd, ".in Checked\n");
            system(cmd);
//            strcpy(cmd, "echo AdvancedDataSet/testcase");
//            strcat(cmd, number);
//            strcat(cmd, "/");
//            strcat(cmd, in_number);
//            strcat(cmd, ".in Checked\n");
//            system(cmd);
            strcpy(cmd, "rm out.txt\n");
            system(cmd);

        }
        strcpy(cmd, "rm Keyword_BookList\n");
        system(cmd);
        strcpy(cmd, "rm AccountFile\n");
        system(cmd);
        strcpy(cmd, "rm AccountList\n");
        system(cmd);
        strcpy(cmd, "rm Author_BookList\n");
        system(cmd);
        strcpy(cmd, "rm Name_BookList\n");
        system(cmd);
        strcpy(cmd, "rm BookFile\n");
        system(cmd);
        strcpy(cmd, "rm WorkList\n");
        system(cmd);
        strcpy(cmd, "rm ISBN_BookList\n");
        system(cmd);
        strcpy(cmd, "rm FinanceReport\n");
        system(cmd);
        strcpy(cmd, "rm FinanceRecord\n");
        system(cmd);
        strcpy(cmd, "rm WorkReportBinary\n");
        system(cmd);
    }
    for (int i = 3; i <= 3; ++i) {
        for (int j = 1; j <= 5; ++j) {
            strcpy(cmd, "./code<./Data/AdvancedDataSet/testcase");
            char num = static_cast<char>('0' + i);
            char number[2] = {num, '\0'};
            strcat(cmd, number);
            strcat(cmd, "/");
            char in_num = static_cast<char>('0' + j);
            char in_number[2] = {in_num, '\0'};
            strcat(cmd, in_number);
            strcat(cmd, ".in >out.txt\n");
            system(cmd);
            strcpy(cmd, "diff out.txt ./Data/AdvancedDataSet/testcase");
            strcat(cmd, number);
            strcat(cmd, "/");
            strcat(cmd, in_number);
            strcat(cmd, ".out\n");
            int judge5 = system(cmd);
            if (judge5 == 0)score++;
            strcpy(cmd, "echo AdvancedDataSet/testcase");
            strcat(cmd, number);
            strcat(cmd, "/");
            strcat(cmd, in_number);
            strcat(cmd, ".in Checked\n");
            system(cmd);
//            strcpy(cmd, "echo AdvancedDataSet/testcase");
//            strcat(cmd, number);
//            strcat(cmd, "/");
//            strcat(cmd, in_number);
//            strcat(cmd, ".in Checked\n");
//            system(cmd);
            strcpy(cmd, "rm out.txt\n");
            system(cmd);

        }
        strcpy(cmd, "rm Keyword_BookList\n");
        system(cmd);
        strcpy(cmd, "rm AccountFile\n");
        system(cmd);
        strcpy(cmd, "rm AccountList\n");
        system(cmd);
        strcpy(cmd, "rm Author_BookList\n");
        system(cmd);
        strcpy(cmd, "rm Name_BookList\n");
        system(cmd);
        strcpy(cmd, "rm BookFile\n");
        system(cmd);
        strcpy(cmd, "rm WorkList\n");
        system(cmd);
        strcpy(cmd, "rm ISBN_BookList\n");
        system(cmd);
        strcpy(cmd, "rm FinanceReport\n");
        system(cmd);
        strcpy(cmd, "rm FinanceRecord\n");
        system(cmd);
        strcpy(cmd, "rm WorkReportBinary\n");
        system(cmd);
    }
    for (int i = 4; i <= 5; ++i) {
        for (int j = 1; j <= 10; ++j) {
            strcpy(cmd, "./code<./Data/AdvancedDataSet/testcase");
            char num = static_cast<char>('0' + i);
            char number[2] = {num, '\0'};
            strcat(cmd, number);
            strcat(cmd, "/");
            char in_number[3];
            if (j <= 9) {
                char in_num = static_cast<char>('0' + j);
                in_number[0] = in_num;
                in_number[1] = '\0';
                strcat(cmd, in_number);
            } else {
                strcat(cmd, "10");
                strcpy(in_number, "10");
            }
            strcat(cmd, ".in >out.txt\n");
            system(cmd);
            strcpy(cmd, "diff out.txt ./Data/AdvancedDataSet/testcase");
            strcat(cmd, number);
            strcat(cmd, "/");
            strcat(cmd, in_number);
            strcat(cmd, ".out\n");
            int judge6 = system(cmd);
            if (judge6 == 0)score++;
            strcpy(cmd, "echo AdvancedDataSet/testcase");
            strcat(cmd, number);
            strcat(cmd, "/");
            strcat(cmd, in_number);
            strcat(cmd, ".in Checked\n");
            system(cmd);
//            strcpy(cmd, "echo AdvancedDataSet/testcase");
//            strcat(cmd, number);
//            strcat(cmd, "/");
//            strcat(cmd, in_number);
//            strcat(cmd, ".in Checked\n");
//            system(cmd);
            strcpy(cmd, "rm out.txt\n");
            system(cmd);

        }
        strcpy(cmd, "rm Keyword_BookList\n");
        system(cmd);
        strcpy(cmd, "rm AccountFile\n");
        system(cmd);
        strcpy(cmd, "rm AccountList\n");
        system(cmd);
        strcpy(cmd, "rm Author_BookList\n");
        system(cmd);
        strcpy(cmd, "rm Name_BookList\n");
        system(cmd);
        strcpy(cmd, "rm BookFile\n");
        system(cmd);
        strcpy(cmd, "rm WorkList\n");
        system(cmd);
        strcpy(cmd, "rm ISBN_BookList\n");
        system(cmd);
        strcpy(cmd, "rm FinanceReport\n");
        system(cmd);
        strcpy(cmd, "rm FinanceRecord\n");
        system(cmd);
        strcpy(cmd, "rm WorkReportBinary\n");
        system(cmd);
    }
    for (int i = 1; i <= 5; ++i) {
        for (int j = 1; j <= 10; ++j) {
            strcpy(cmd, "./code<./Data/ComplexDataSet/testcase");
            char num = static_cast<char>('0' + i);
            char number[2] = {num, '\0'};
            strcat(cmd, number);
            strcat(cmd, "/");
            char in_number[3];
            if (j <= 9) {
                char in_num = static_cast<char>('0' + j);
                in_number[0] = in_num;
                in_number[1] = '\0';
                strcat(cmd, in_number);
            } else {
                strcat(cmd, "10");
                strcpy(in_number, "10");
            }
            strcat(cmd, ".in >out.txt\n");
            system(cmd);
            strcpy(cmd, "diff out.txt ./Data/ComplexDataSet/testcase");
            strcat(cmd, number);
            strcat(cmd, "/");
            strcat(cmd, in_number);
            strcat(cmd, ".out\n");
            int judge7 = system(cmd);
            if (judge7 == 0)score++;
            strcpy(cmd, "echo ComplexDataSet/testcase");
            strcat(cmd, number);
            strcat(cmd, "/");
            strcat(cmd, in_number);
            strcat(cmd, ".in Checked\n");
            system(cmd);
//            strcpy(cmd, "echo ComplexDataSet/testcase");
//            strcat(cmd, number);
//            strcat(cmd, "/");
//            strcat(cmd, in_number);
//            strcat(cmd, ".in Checked\n");
//            system(cmd);
            strcpy(cmd, "rm out.txt\n");
            system(cmd);

        }
        strcpy(cmd, "rm Keyword_BookList\n");
        system(cmd);
        strcpy(cmd, "rm AccountFile\n");
        system(cmd);
        strcpy(cmd, "rm AccountList\n");
        system(cmd);
        strcpy(cmd, "rm Author_BookList\n");
        system(cmd);
        strcpy(cmd, "rm Name_BookList\n");
        system(cmd);
        strcpy(cmd, "rm BookFile\n");
        system(cmd);
        strcpy(cmd, "rm WorkList\n");
        system(cmd);
        strcpy(cmd, "rm ISBN_BookList\n");
        system(cmd);
        strcpy(cmd, "rm FinanceReport\n");
        system(cmd);
        strcpy(cmd, "rm FinanceRecord\n");
        system(cmd);
        strcpy(cmd, "rm WorkReportBinary\n");
        system(cmd);
    }
    system("rm cmake_install.cmake\nrm cmakecache.txt\nrm auto\nrm code\nrm makefile\n");
    system("echo All Test Track Completed 103/103\n");
    system("echo SCORE: \n");
    char score_[20];
    stringstream sss;
    sss << score;
    sss >> score_;
    strcpy(cmd, "echo ");
    strcat(cmd, score_);
    strcat(cmd,"/103");
    system(cmd);
    return 0;
}