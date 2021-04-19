#include "yuwen_bst.h"
#include "TextAnalyzer.h"
#include "WordEntry.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

TextAnalyzer::TextAnalyzer()
{
    TextAnalyzer("");
}

TextAnalyzer::TextAnalyzer(string fileName)
{
    this->fileName = fileName;
    // Open input file
    ifstream infile;
    infile.open(fileName);
    // declare variables
    tree = new BST<string>();                  // create tree
    treeOfFrequencies = new BST<string>(true); // create treeOfFrequencies
    string word;
    long numWords = 0;
    Node<string> *node;
    // instantiate mostUsedWords and leastUsedWords
    WordEntry *dummyWordEntry1 = new WordEntry(), *dummyWordEntry2 = new WordEntry();
    dummyWordEntry1->setFrequency(-1);
    dummyWordEntry1->setFrequency(2147483647);
    mostUsedWords = new WordEntry *[5];
    leastUsedWords = new WordEntry *[5];
    for (int i = 0; i < 5; i++)
    {
        mostUsedWords[i] = dummyWordEntry1;
        leastUsedWords[i] = dummyWordEntry2;
    }

    // iterate over each word in file
    vector<string> words; // handles the case that multiple words are joined by hyphens or other delimiters
    int index;
    while (infile >> word)
    {
        std::transform(word.begin(), word.end(), word.begin(), tolower); // make word lowercase
        while (word.length() > 0)
        {
            if (!isalpha(word.back()) && word.back() != '\'')
            { // validate last char of string
                word = word.substr(0, word.size() - 1);
            }
            else if (!isalpha(word.front()))
            { // validate first char of string
                word = word.substr(1, word.size());
            }
            else
            {
                break;
            }
        }

        words.clear();
        // check for hyphens or other delimiters, and construct "words" vector
        index = word.find_first_not_of("abcdefghijklmnopqrstuvwxyz'");
        if (index < 0) // delimiter not found
        {
            words.push_back(word);
        }
        else
        {
            do
            {
                words.push_back(word.substr(0, index));
                word = word.substr(index + 1, word.size());
                index = word.find_first_not_of("abcdefghijklmnopqrstuvwxyz'");
            } while (index >= 0); // while delimiter was found
        }

        do // iterate through "words"
        {
            word = words.back();
            words.pop_back();
            // update tree
            node = tree->insert(word);
            node->wordEntry->incrementFrequency();

        } while (!words.empty());

        numWords++;
    }
    // close input file stream
    infile.close();

    this->fileName = fileName;
    this->numWords = numWords;

    // create treeOfFrequencies
    makeTreeOfFrequencies();
    // find leastUsedWords and mostUsedWords
    findLeastUsedWords();
    findMostUsedWords();

    delete dummyWordEntry1;
    delete dummyWordEntry2;
}

TextAnalyzer::~TextAnalyzer()
{
    delete mostUsedWords;
    delete leastUsedWords;
    delete tree;
    delete treeOfFrequencies;
}

string TextAnalyzer::getFileName()
{
    return fileName;
}

long TextAnalyzer::getNumWords()
{
    return numWords;
}

long TextAnalyzer::numUniqueWords()
{
    return tree->length();
}

void TextAnalyzer::makeTreeOfFrequencies()
{
    // complete in-order traversal of tree, adding each element to treeOfFrequencies
    // Note that the frequencies are copied from "tree", so that should be constructed before this method is called
    vector<Node<string> *> stack;
    Node<string> *curr = tree->getRoot();
    while (curr || !stack.empty())
    {
        while (curr != NULL)
        {
            stack.push_back(curr);
            curr = curr->left;
        }
        curr = stack.back();
        stack.pop_back();
        treeOfFrequencies->insert(curr->wordEntry->getWord(), curr->wordEntry->getFrequency());
        curr = curr->right;
    }
}

void TextAnalyzer::findMostUsedWords()
{
    // get last 5 elements of treeOfFrequencies using reverse inorder traversal
    int i = 0;
    Node<string> *curr = treeOfFrequencies->getRoot();
    vector<Node<string> *> stack;
    while ((curr || !stack.empty()) && i < 5)
    {
        while (curr)
        {
            stack.push_back(curr);
            curr = curr->right;
        }
        curr = stack.back();
        stack.pop_back();
        mostUsedWords[i] = curr->wordEntry;
        i++;
        curr = curr->left;
    }
}

void TextAnalyzer::findLeastUsedWords()
{
    // get first 5 elements of treeOfFrequencies using inorder traversal
    int i = 0;
    vector<Node<string> *> stack;
    Node<string> *curr = treeOfFrequencies->getRoot();
    while ((curr || !stack.empty()) && i < 5)
    {
        while (curr)
        {
            stack.push_back(curr);
            curr = curr->left;
        }
        curr = stack.back();
        stack.pop_back();
        leastUsedWords[i] = curr->wordEntry;
        i++;
        curr = curr->right;
    }
}

WordEntry **TextAnalyzer::getMostUsedWords()
{
    return mostUsedWords;
}

WordEntry **TextAnalyzer::getLeastUsedWords()
{
    return leastUsedWords;
}

BST<string> *TextAnalyzer::getTree()
{
    return tree;
}

BST<string> *TextAnalyzer::getTreeOfFrequencies()
{
    return treeOfFrequencies;
}

string *TextAnalyzer::alphabeticalList()
{
    return tree->toArr();
}

string *TextAnalyzer::listByDecreasingFrequency()
{
    return treeOfFrequencies->toArr();
}

long TextAnalyzer::frequencyOfWord(string word)
{
    if (!tree->elementExists(word))
    {
        return 0;
    }
    return tree->find(word)->wordEntry->getFrequency();
}

void TextAnalyzer::outputSummaryToFile()
{
    outputSummaryToFile("summary_statistics.txt");
}

void TextAnalyzer::outputSummaryToFile(string fileName)
{
    // Open output file stream
    ofstream outfile;
    outfile.open(fileName);
    // output header
    outfile << "Summary of " << this->getFileName() << endl;
    outfile << "-----------------------" << endl;
    // output total words as well as total unique words
    outfile << "Total words: " << numWords << endl;
    outfile << "Total unique words: " << numUniqueWords() << endl;
    // output the five most frequently used words
    string word;
    long frequency;
    outfile << "The five most frequently used words, in decreasing order of appearance, were:" << endl;
    for (int i = 0; i < 5; i++)
    {
        word = mostUsedWords[i]->getWord();
        frequency = mostUsedWords[i]->getFrequency();
        outfile << "\t" << word << " (appeared " << frequency << " times)" << endl;
    }
    outfile << "The five least frequently used words, in increasing order of appearance, were:" << endl;
    for (int i = 0; i < 5; i++)
    {
        word = leastUsedWords[i]->getWord();
        frequency = leastUsedWords[i]->getFrequency();
        outfile << "\t" << word << " (appeared " << frequency << " times)" << endl;
    }
    outfile << endl;

    // close output file stream
    outfile.close();
}
