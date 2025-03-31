#ifndef sortingAlgorithm_h
#define sortingAlgorithm_h

#include <iostream>
#include <cmath>
#include <string>

template <class T>
void reverseArray(T arr[], int n);
template <class T>
void heapify(T arr[], int n, int i);
template <class T>
void heapSort(T arr[], int n);
template <class T>
int partition(T arr[], int low, int high);
template <class T>
void quickSort(T arr[], int n);
template <class T>
void insertionSort(T arr[], int n);
template <class T>
void introSort(T arr[], int n);
template <class T>
void mergeSort(T a[],int n);

template <class T>
void selectionSort(T arr[], int n);

template <class T>
int binarySearch(T arr[], int low, int high, const T &target); // modified for insertion sort

template <class T>
void binaryInsertionSort(T arr[], int n);
template <class T>
void shakerSort(T arr[], int n);

int findMaxNum(int arr[], int n);
int getMaxString(void *array, int n);
void countingSortNums(int arr[], int n, int exp); // void countingSortStrings(string arr[], int n, int index);
void countingSortStrings(void *array, int n, int index);
void radixSortNums(int arr[], int n);
void radixSortStrings(void *array, int n);
template<class T>
void bubbleSort(T arr[], int n);
template<class T>
void shellSort(T arr[], int n);
template <class T>
void naturalMergeSort(T arr[], int n);
#endif // !sortingAlgorithm_h
