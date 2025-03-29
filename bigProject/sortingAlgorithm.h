#ifndef sortingAlgorithm_h
#define sortingAlgorithm_h

#include <iostream>
#include <cmath>

void reverseArray(int arr[], int n);

void heapify(int arr[], int n, int i);
void heapSort(int arr[], int n);

int partition(int arr[], int low, int high);
void quickSort(int arr[], int low, int high, int depthLimit);

void insertionSort(int arr[], int low, int high);

void introSort(int arr[], int n);
template <class T>
void MergeSort(T a[],int n);

template <class T>
void selectionSort(T arr[], int n);

template <class T>
int binarySearch(T arr[], int low, int high, const T &target); // modified for insertion sort

template <class T>
void binaryInsertionSort(T arr[], int n);
#endif // !sortingAlgorithm_h
