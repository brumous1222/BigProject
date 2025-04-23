#include "Dictionary.h"
#include "../sortingAlgorithm.h"
#include "../sortingAlgorithm.cpp"

void deleteAllDigits(string &word) {
    int len = word.length();
    if (len <= 0) {
        return;
    }
    while (word[len - 1] >= '0' && word[len - 1] <= '9') {
        word[len - 1] = '\0';
        len--;
    }
}

vector<string> loadDict(const string &inFile) { // get all words from dictionary, put them into a vector
    ifstream input;
    input.open(inFile, ios::in);
    vector<string> dictionary;
    string line;
    int currIdx = 0;
    if (!input.is_open()) { // can not open the file
        cout << "Failed to open file" << endl;
        return dictionary;
    }
    while (getline(input, line)) { // try to read line by line
        int delimIdx = line.find(DELIM); // find if in current line has DELIM
        if (delimIdx != string::npos) { // found, extract substring from first char to delimIdx - 1
            string word = line.substr(0, delimIdx); // extract the word;
            if (word[delimIdx - 1] == '-' || word[0] == '-') { // skip all suffixs and prefixs
                continue;
            }
            deleteAllDigits(word); // delete all digits from a word
            deleteAllSpaces(word);
            toLowerCase(word);
            if (word.length() <= 0) { // no words
                continue;
            } else if (!dictionary.empty()) {
                if (word == dictionary[dictionary.size() - 1]) { // check if it is duplicated
                    continue;
                }
                if (word == USAGE) { // special case "usage"
                    int type = line.find(SPECIAL_USAGE); // check if it is the real "Usage" word which on the line "Usage  n."
                    if (type != delimIdx) {
                        continue;
                    }
                }
            }
            dictionary.push_back(word);
        }
    }
    input.close();
    return dictionary;
}

void deleteAllSpaces(string &word) {
    while (word[0] == ' ') {
        for (int i = 0; i < word.length(); i++) {
            word[i] = word[i + 1];
        }
    }
}

void toLowerCase(string &word) {
    for (int i = 0; i < word.length(); i++) {
        word[i] = tolower(word[i]);
    }
}

void exportDict(const string &outFile, const vector<string> &dict) { // export dict to file (each line is a word)
    ofstream output;
    output.open(outFile, ios::out);
    if (!output.is_open()) { // failed to open
        cout << "Failed to open file" << endl;
        return;
    }
    int len = dict.size();
    output << len << endl; // added a line for len of dict array
    for (int i = 0; i < len; i++) {
        output << dict[i] << endl;
    }
    output.close();
}

void loadShortenDictToArray(const string &shortenDict, string *&arr, int &n) {
    ifstream input;
    input.open(shortenDict);
    if (!input.is_open()) {
        cout << "Failed to open file" << endl;
        return;
    }
    if (!(input >> n)) { // safety
        return;
    }
    input.ignore(); // skip '\n' char
    arr = new string[n];
    if (!arr) { // safety
        return;
    }
    for (int i = 0; i < n; i++) {
        getline(input, arr[i]); // each line is a word, read line by line
    }
    input.close();
}

void generateRandom(const string dict[], const int &n, string *&arr, int &len, const int &randomLen) {
    srand((unsigned)time(NULL));
    arr = new string[randomLen];
    if (!arr) {
        cout << "Failed on creating array" << endl;
        return;
    }
    len = randomLen;
    for (int i = 0; i < randomLen; i++) {
        int randIdx = rand() % (n - 1);
        arr[i] = dict[randIdx];
    }
}

void generateSorted(const string dict[], const int &n, string *&arr, int &len, const int &sortedLen) {
    generateRandom(dict, n, arr, len, sortedLen);
    mergeSort(arr, len);
}

void generateNearlySorted(const string dict[], const int &n, string *&arr, int &len, const int &nearlyLen) {
    srand((unsigned)time(NULL));
    int sortedLen = 0.8 * nearlyLen;
    len = nearlyLen;
    arr = new string[nearlyLen];
    if (!arr) {
        cout << "Failed in creating array" << endl;
        return;
    }
    for (int i = 0; i < sortedLen; i++) {
        arr[i] = dict[rand() % n];
    }
    mergeSort(arr, sortedLen);
    for (int i = sortedLen; i < nearlyLen; i++) {
        arr[i] = dict[rand() % n];
    }
    for (int i = 0; i < len; i++) {
        cout << arr[i] << endl;
    }
}

void generateReversed(const string dict[], const int &n, string *&arr, int &len, const int &reverseLen) {
    generateSorted(dict, n, arr, len, reverseLen);
    for (int i = 0; i < len / 2; i++) {
        swap(arr[i], arr[len - i - 1]);
    }
    for (int i = 0; i < len; i++) {
        cout << arr[i] << endl;
    }
}