#ifndef Dictionary_h
#define Dictionary_h

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

// delim in dictionary
#define DELIM "  "
#define SPECIAL_USAGE "  n."

using namespace std;

void deleteAllDigits(string &word); // delete all digits from the last of word (this happens when in a dict, a word has >= 2 meanin
void deleteAllSpaces(string &word);
vector<string> loadDict(const string &inFile); // get all words from dictionary, put them into a vector
void exportDict(const string &outFile, const vector<string> &dict); // export dict to file (each line is a word)

#endif