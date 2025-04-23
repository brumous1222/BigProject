#include "Dictionary.h"
#include "../sortingAlgorithm.h"
#include "../sortingAlgorithm.cpp"

void insertionSort(vector<string> &arr) { // because this dictionary is nearly sorted (dictionary order), to convert it to cpp order, insertion sort is a great choice
    int len = arr.size();
    for (int i = 1; i < len; i++) {
        int j = i;
        string currString = arr[i];
        while (j > 0 && arr[j - 1] > currString) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = currString;
    }
}

void deleteAllDigits(string &word) { // delete all the digit at the beginning of a string
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
        if (delimIdx != string::npos) { // found, extract substring from first char to delimIdx - 1, not found -> current line does not contain any word
            string word = line.substr(0, delimIdx); // extract the word
            if (word[delimIdx - 1] == '-' || word[0] == '-') { // skip all suffixs and prefixs
                continue;
            }
            // process word format
            deleteAllDigits(word);
            deleteAllSpaces(word);
            toLowerCase(word);

            if (word.length() <= 0) {
                continue;
            } else if (!dictionary.empty()) {
                if (word == dictionary[dictionary.size() - 1]) { // check if it is duplicated
                    continue;
                }
                if (word == USAGE) { // special case, the word "usage"
                    int wordType = line.find(SPECIAL_USAGE); // check if it is the real "Usage" word which on the line "Usage  n."
                    if (wordType != delimIdx) { // there is no word type -> this is not the word "usage with type .n", so skip it
                        continue;
                    }
                }
            }
            dictionary.push_back(word);
        }
    }
    input.close();
    // sort the dictionary
    insertionSort(dictionary);
    return dictionary;
}

void deleteAllSpaces(string &word) { // delete all space from the beginning of a string
    while (word[0] == ' ') {
        for (int i = 0; i < word.length(); i++) {
            word[i] = word[i + 1];
        }
    }
}

void toLowerCase(string &word) { // turn every upper case char to tower
    for (int i = 0; i < word.length(); i++) {
        word[i] = tolower(word[i]);
    }
}

void exportDict(const string &outFile, const vector<string> &dict) { // export dictionary vector into a file (each line is a word)
    ofstream output;
    output.open(outFile, ios::out);
    if (!output.is_open()) { // failed to open
        cout << "Failed to open file" << endl;
        return;
    }
    int len = dict.size();
    output << len << endl; // added a line that tells the len of dict array
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
    input.ignore(); // skip '\n' char of the first line
    arr = new string[n];
    if (!arr) { // safety
        return;
    }
    for (int i = 0; i < n; i++) {
        getline(input, arr[i]); // because each line is a word, we read line by line
    }
    input.close();
}

void generateRandom(const string dict[], const int &dictLen, string *&arr, const int &arrLen) {
    srand((unsigned)time(NULL));
    arr = new string[arrLen];
    if (!arr) {
        cout << "Failed on creating array" << endl;
        return;
    }
    for (int i = 0; i < arrLen; i++) {
        int randIdx = rand() % (dictLen);
        arr[i] = dict[randIdx];
    }
}

void generateSorted(const string dict[], const int &dictLen, string *&arr, const int &arrLen) {
    generateRandom(dict, dictLen, arr, arrLen); // generate a random array, then sort it
    mergeSort(arr, arrLen);
}

void generateNearlySorted(const string dict[], const int &dictLen, string *&arr, const int &arrLen) {
    // we have 2 parts, first part (which length is 80% total len) is sorted, the remain (20% of total len) is random
    srand((unsigned)time(NULL));
    int sortedLen = 0.8 * arrLen; // 80% sorted
    generateRandom(dict, dictLen, arr, arrLen); // generate a whole random array
    mergeSort(arr, sortedLen); // sort 80% of that array
    for (int i = 0; i < arrLen; i++) {
        cout << arr[i] << endl;
    }
}

void generateReversed(const string dict[], const int &dictLen, string *&arr, const int &arrLen) {
    // with reversed array, we will generate a sorted array, then reversed it
    generateSorted(dict, dictLen, arr, arrLen);
    for (int i = 0; i < arrLen / 2; i++) {
        swap(arr[i], arr[arrLen - i - 1]);
    }
    for (int i = 0; i < arrLen; i++) {
        cout << arr[i] << endl;
    }
}