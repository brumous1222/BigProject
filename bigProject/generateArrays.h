#ifndef generateArrays_h
#define generateArrays_h

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <string>

using namespace std;

bool isSorted(int arr[], int n);
void reverseArray(int arr[], int n);

void generateRandomArray(int arr[], int n, int k);
void generateSortedArray(int arr[], int n, int k);
void generateReverseArray(int arr[], int n, int k);
void generateNearlySortedArray(int arr[], int n, int k);

typedef void(*sortFunc)(int arr[], int n);
void measureSortingTime(sortFunc sortName, int arr[], int n, const string& algoName, const string& inputType);
#endif // !generateArrays.h
