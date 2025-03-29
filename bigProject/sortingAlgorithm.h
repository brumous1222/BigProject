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
void quickSort(T arr[], int low, int high, int depthLimit);
template <class T>
void insertionSort(T arr[], int low, int high);
template <class T>
void introSort(T arr[], int n);
template <class T>
void MergeSort(T a[],int n);
template <class T>
int findMax(T arr[], int n);
template <class T>
void countingSort(T arr[], int n, int exp);
template <class T>
void radixSort(T arr[], int n);
#endif // !sortingAlgorithm_h
