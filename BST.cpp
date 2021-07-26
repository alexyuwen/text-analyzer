/*
Author: Alex Yuwen
Date: 4/20/21
Description:  This program creates a word frequency analyzer using BST as the underlying data structure.
              This file acts as "main"
Usage:        In the directory containing the Makefile, run "make".  This will create an executable file
              which you can run using the command "./cExe"
*/

#include "TextAnalyzer.h"
//#include "TextAnalyzer.cpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::string;
using std::vector;

int main(int argc, char *argv[])
{
    string fileName;
    cout << "Please enter the name of the file which you would like to analyze. Make sure it is in the same directory as the main.cpp file." << endl;
    getline(cin, fileName);
    TextAnalyzer *fileAnalysis = new TextAnalyzer(fileName);
    int option;
    bool done = false;
    while (!done)
    {
        // display options
        cout << "\nWhat would you like to do next?" << endl;
        cout << "\t(1) Output total number of words\n";
        cout << "\t(2) Output total number of unique words\n";
        cout << "\t(3) Output the 5 most and least frequently used words\n";
        cout << "\t(4) Retrieve frequency of a given word\n";
        cout << "\t(5) Output list of words used in increasing alphabetical order\n";
        cout << "\t(6) Output list of words used in order of increasing frequency\n";
        cout << "\t(7) Output summary statistics to file\n";
        cout << "\t(0) Quit\n";
        cout << "Please enter a number between 0 and 7" << endl;
        cin >> option;

        switch (option)
        {
            {
            case 1:
                cout << "Total words: " << fileAnalysis->getNumWords() << endl;
                break;
            }
            {
            case 2:
                cout << "Total unique words: " << fileAnalysis->numUniqueWords() << endl;
                break;
            }
            {
            case 3:
                string word;
                long frequency;
                cout << "The five most frequently used words, in decreasing order of appearance, were:" << endl;
                for (int i = 0; i < 5; i++)
                {
                    word = fileAnalysis->getMostUsedWords()[i]->getWord();
                    frequency = fileAnalysis->getMostUsedWords()[i]->getFrequency();
                    cout << "\t" << word << " (appeared " << frequency << " times)" << endl;
                }
                cout << "The five least frequently used words, in increasing order of appearance, were:" << endl;
                for (int i = 0; i < 5; i++)
                {
                    word = fileAnalysis->getLeastUsedWords()[i]->getWord();
                    frequency = fileAnalysis->getLeastUsedWords()[i]->getFrequency();
                    cout << "\t" << word << " (appeared " << frequency << " times)" << endl;
                }
                break;
            }
            {
            case 4:
                string word;
                cout << "Please enter a word." << endl;
                cin.ignore();
                getline(cin, word);
                cout << "The word \"" << word << "\" appeared " << fileAnalysis->frequencyOfWord(word) << " times." << endl;
                break;
            }
            {
            case 5:
                string word;
                for (int i = 0; i < fileAnalysis->getTree()->length(); i++)
                {
                    word = fileAnalysis->alphabeticalList()[i];
                    cout << word << endl;
                }
                break;
            }
            {
            case 6:
                string word;
                for (int i = 0; i < fileAnalysis->getTreeOfFrequencies()->length(); i++)
                {
                    word = fileAnalysis->listByDecreasingFrequency()[i];
                    cout << word << endl;
                }
                break;
            }
            {
            case 7:
                fileAnalysis->outputSummaryToFile();
                cout << "A new file — \"summary_statistics.txt\" - has been created." << endl;
                break;
            }
        default:
            done = true;
        } // end of switch block
    }     // end of while loop

    delete fileAnalysis;
    return 0;
}
