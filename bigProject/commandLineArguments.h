#ifndef commandLineArguments_h
#define commandLineArguments_h

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
#include "generateArrays.h"
#include "generateArrays.cpp"

using namespace std;

vector<string> algorithmNames = { "selectionSort", "insertionSort", "binaryInsertionSort", "bubbleSort", "shakerSort", "shellSort",
"heapSort", "mergeSort", "naturalMergeSort", "quickSort", "radixSort", "countingSort" };
vector<string> inputOrders = { "-rand", "-sorted", "-rsorted", "-nsorted" };

template<class InputIterator, class T>
InputIterator find(InputIterator first, InputIterator last, const T& val);
bool isNumber(const string& s);
void showHelp();
bool isError(const string& mode, const vector<string>& algs, int inputSize, const string& inputPath);
// void parseArgs(int argc, char* argv[], string& mode, vector<string>& algs, int& inputSize,
//     string& inputOrder, string& inputPath, string& outputParams, string& outputFile);
void parseArgs(int argc, char* argv[], string& mode, vector<string>& algs, int& inputSize,
    string& inputOrder, string& inputPath, string& outputFile);
void generateArray(const string& fileName, int n, const int dataType);
void processSort(vector<string>& algs, const string& inputFile, const string& outputFile, const string& inputType);
void processArg(int argc, char* argv[]);

#endif // !commandLineArguments_h
