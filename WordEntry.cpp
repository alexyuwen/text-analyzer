#include "WordEntry.h"
#include "BST.h"
#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

WordEntry::WordEntry()
{
    WordEntry("");
}

WordEntry::WordEntry(string word)
{
    this->word = word;
    this->frequency = 0;
}

string WordEntry::getWord()
{
    return word;
}

long WordEntry::getFrequency()
{
    return frequency;
}

void WordEntry::setFrequency(long frequency)
{
    this->frequency = frequency;
}

void WordEntry::incrementFrequency()
{
    frequency++;
}
