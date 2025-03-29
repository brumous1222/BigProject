#include "sortingAlgorithm.h"

using namespace std;

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high, int depthLimit) {
    if (low < high) {
        if (depthLimit == 0) {
            heapSort(arr + low, high - low + 1);
            return;
        }

        int pivot = partition(arr, low, high);
        quickSort(arr, low, pivot - 1, depthLimit - 1);
        quickSort(arr, pivot + 1, high, depthLimit - 1);
    }
}

void insertionSort(int arr[], int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void introSort(int arr[], int n) {
    int depthLimit = 2 * log(n);
    quickSort(arr, 0, n - 1, depthLimit);
    insertionSort(arr, 0, n - 1);
}

template <class T>
void selectionSort(T arr[], int n) {
    for (int i = 0; i < n; i++) {
        int currMinIdx = i;
        for (int j = i + 1; j < n; j++) { // find the minIdx in [i, n-1]
            if (arr[j] < arr[currMinIdx]) {
                currMinIdx = j;
            }
        }
        swap(arr[i], arr[currMinIdx]); // swap [i] with [currMinIdx]
    }
}

template <class T>
int binarySearch(T arr[], int low, int high, const T &target) { // modified for insertion sort
    int mid = (low + high) / 2;
    if (arr[mid] == target) {
        return mid;
    } else if (low >= high) { // modified for insertion sort
        return max(0, low);
    } else if (arr[mid] < target) { // search right
        return binarySearch(arr, mid + 1, high, target);
    } else {
        return binarySearch(arr, low, mid - 1, target);
    }
}

template <class T>
void binaryInsertionSort(T arr[], int n) {
    for (int i = 1; i < n; i++) {
        T currVal = arr[i];
        int suitableIdx = binarySearch(arr, 0, i - 1, currVal); // search for suitable idx for currVal
        int j = i;
        if (arr[suitableIdx] <= arr[i]) { // check if currVal (arr[i]) is  >= to arr[suitableIdx]
            suitableIdx++; // if so, insert arr[i] add [suitableIdx + 1], else, insert arr[i] at arr[suitableIdx]
        }
        while (j > 0 && j > suitableIdx) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = currVal;
    }
}