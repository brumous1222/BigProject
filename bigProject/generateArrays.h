#ifndef generateArrays_h
#define generateArrays_h

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <string>
#include "sortingAlgorithm.h"
#include "sortingAlgorithm.cpp"

using namespace std;

template <class T>
bool isSorted(T arr[], int n);

template <class T>
void reverseArray(T arr[], int n);

template <class T>
void generateRandomArray(T arr[], int n, int k);

template <class T>
void generateSortedArray(T arr[], int n, int k);

template <class T>
void generateReverseArray(T arr[], int n, int k);

template <class T>
void generateNearlySortedArray(T arr[], int n, int k);

// template <class T>
// typedef void(*sortFunc)(T arr[], int n);

template <class T>
void generateData(T arr[], int n, const int order);

template <class T>
void outputResultToFile(const string& outputFile, void (*sortFunc)(T[], int), T arr[], int n,
    const string& algoName, const string& order);
#endif // !generateArrays.h