#include "Dictionary.h"

void deleteAllDigits(string &word)
{
    int len = word.length();
    if (len <= 0)
    {
        return;
    }
    while (word[len - 1] >= '0' && word[len - 1] <= '9')
    {
        word[len - 1] = '\0';
        len--;
    }
}

vector<string> loadDict(const string &inFile) // get all words from dictionary, put them into a vector
{
    ifstream input;
    input.open(inFile, ios::in);
    vector<string> dictionary;
    string line;
    int currIdx = 0;
    if (!input.is_open()) // can not open the file
    {
        cout << "Failed to open file" << endl;
        return dictionary;
    }
    while (getline(input, line)) // try to read line by line
    {
        int delimIdx = line.find(DELIM); // find if in current line has DELIM
        if (delimIdx != string::npos) // found, extract substring from first char to delimIdx - 1
        {
            string word = line.substr(0, delimIdx); // extract the word;
            if (word[delimIdx - 1] == '-' || word[0] == '-') // skip all suffixs and prefixs
            {
                continue;
            }
            deleteAllDigits(word); // delete all digits from a word
            if (word.length() <= 0) // no words
            {
                continue;
            }
            else if (!dictionary.empty())
            {
                if (word == dictionary[dictionary.size() - 1]) // check if it is duplicated
                {
                    continue;
                }
                if (word == "Usage")
                {
                    int type = line.find(SPECIAL_USAGE); // check if it is the real "Usage" word which on the line "Usage  n."
                    if (type != delimIdx)
                    {
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

void exportDict(const string &outFile, const vector<string> &dict) // export dict to file (each line is a word)
{
    ofstream output;
    output.open(outFile, ios::out);
    if (!output.is_open()) // failed to open
    {
        cout << "Failed to open file" << endl;
        return;
    }
    int len = dict.size();
    for (int i = 0; i < len; i++)
    {
        output << dict[i] << endl;
    }
    output.close();
}