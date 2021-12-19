//
// Created by lu'ren'jia'd's on 2021/12/15.
//

#ifndef UNTITLED1_BLOCKLIST_H
#define UNTITLED1_BLOCKLIST_H
#include <string>
#include <vector>

const int length = 66;

bool compare_char(const char *lhs, const char *rhs);
class BlockList {
    std::string FileName;
    long Start = 0;
public:
    struct Block {
        int CurrentSize = 0;
        const int MaxSize = 5000;
        char first_array[5000][length];
        int second_array[5000]; //maybe you need bigger array, to do
        char MaxValue[length];
        char MinValue[length];
        long Next = -100000;
        long MyLocation = -100000;
    };

    BlockList(const std::string &fn) : FileName(fn) {};

    void InsertPair(char *first_, int second_);

    void DeletePair(char *first_, int second_);

    int FindPairs(char *first_);

    std::vector<int> FindAllPairs(char *first_);

    void ShowAllBooks();

};

#endif //UNTITLED1_BLOCKLIST_H
