#pragma once
#ifndef WORD_ENTRY_H
#define WORD_ENTRY_H

#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::string;

class WordEntry
{
private:
    string word;
    long frequency;

public:
    WordEntry();
    WordEntry(string word);
    string getWord();
    long getFrequency();
    void setFrequency(long frequency);
    void incrementFrequency();
};

#endif
