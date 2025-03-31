#ifndef sortingAlgorithm_h
#define sortingAlgorithm_h

#include <iostream>
#include <cmath>
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

int findMax(int arr[], int n);
int findMax(string arr[], int n);
void countingSort(int arr[], int n, int exp);
void countingSort(string arr[], int n, int index);
void radixSort(int arr[], int n);
void radixSort(string arr[], int n);
template<class T>
void bubbleSort(T arr[], int n);
template<class T>
void shellSort(T arr[], int n);
template <class T>
void naturalMergeSort(T arr[], int n);
#endif // !sortingAlgorithm_h
