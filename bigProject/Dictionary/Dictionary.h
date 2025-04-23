#ifndef Dictionary_h
#define Dictionary_h

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <ctime>
#include <stdlib.h>

// delim in dictionary
#define DELIM "  "
#define USAGE "usage"
#define SPECIAL_USAGE "  n."

using namespace std;

void deleteAllDigits(string &word); // delete all digits from the last of word (this happens when in a dict, a word has >= 2 meanin
void deleteAllSpaces(string &word);
void toLowerCase(string &word);
vector<string> loadDict(const string &inFile); // get all words from dictionary, put them into a vector
void exportDict(const string &outFile, const vector<string> &dict); // export dict to file (each line is a word)
// void loadShortenDictToArray(const string &shortenDict, string arr[], int &n);
void loadShortenDictToArray(const string &shortenDict, string *&arr, int &n);
void generateRandom(const string dict[], const int &dictLen,  string *&arr, const int &arrLen);
void generateSorted(const string dict[], const int &dictLen, string *&arr, const int &arrLen);
void generateNearlySorted(const string dict[], const int &dictLen, string *&arr, const int &arrLen);
void generateReversed(const string dict[], const int &dictLen, string *&arr, const int &arrLen);

#endif