#pragma once
#ifndef TEXT_ANALYZER_H
#define TEXT_ANALYZER_H

#include "yuwen_bst.h"
#include "WordEntry.h"
#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

class TextAnalyzer
{
private:
    string fileName;
    long numWords;
    WordEntry **mostUsedWords;
    WordEntry **leastUsedWords;
    BST<string> *tree;
    BST<string> *treeOfFrequencies;
    void makeTreeOfFrequencies();
    void findMostUsedWords();  // helper method
    void findLeastUsedWords(); // helper method

public:
    TextAnalyzer();
    TextAnalyzer(string fileName);
    ~TextAnalyzer();
    string getFileName();
    long getNumWords();
    long numUniqueWords();
    WordEntry **getMostUsedWords();
    WordEntry **getLeastUsedWords();
    BST<string> *getTree();
    BST<string> *getTreeOfFrequencies();
    string *alphabeticalList();
    string *listByDecreasingFrequency();
    long frequencyOfWord(string word);
    void outputSummaryToFile();
    void outputSummaryToFile(string fileName);
};

#endif
