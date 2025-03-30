#include "sortingAlgorithm.h"

using namespace std;
template<class T>
void heapify(T arr[], int n, int i) {
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
template<class T>
void heapSort(T arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
template<class T>
int partition(T arr[], int low, int high) {
    T pivot = arr[high]; 
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
template<class T>
void helpquicksort(T arr[], int low, int high, int depthLimit) {
    if (low < high) {
        if (depthLimit == 0) {
            sort(arr + low, arr + high + 1);  
            return;
        }
        int pivot = partition(arr, low, high);
        quickSort(arr, low, pivot - 1, depthLimit - 1);
        quickSort(arr, pivot + 1, high, depthLimit - 1);
    }
}
template<class T>
void quicksort(T arr[], int n) {
    int maxDepth = 2 * log2(n);  
    helpquicksort(arr, 0, n - 1, maxDepth);
}
template<class T>
void helpinsertionSort(T arr[], int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        T key = arr[i];
        int j = i - 1;

        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
template<class T>
void insertionSort(T arr[], int n) {
    insertionSort(arr, 0, n - 1);
}
template <class T>
void introSort(T arr[], int n) {
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

template <class T>
void shakerSort(T arr[], int n) { // it is like doing bubble sort in both directions (left to right and right to left) alternatively
    int maxIdx = n - 1;
    int minIdx = 0;
    int i = 0;
    while (maxIdx > minIdx) {
        if (i % 2 == 0) { // i is a counter to know when to loop from left to right or right to left
            for (int j = minIdx; j < maxIdx; j++) { // loop from left to right (find max)
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
            maxIdx--;
        } else {
            for (int j = maxIdx; j > minIdx; j--) { // loop from right to left (find min)
                if (arr[j] < arr[j - 1]) {
                    swap(arr[j], arr[j - 1]);
                }
            }
            minIdx++;
        }
        i++;
    }
}

template<class T>
void Merge(T a[], int left, int right, int mid)
{
	int n1 = mid - left + 1;
	int n2 = right - mid;
	T *b = new T[n1];
	T *c = new T[n2];
	for (int i = 0; i < n1; i++)
		b[i] = a[left + i];
	for (int j = 0; j < n2; j++)
		c[j] = a[mid + 1 + j];
	int i = 0;
	int j = 0;
	int k = left;
	while (j < n2 && i < n1)
	{
		if (b[i] <= c[j])
		{
			a[k] = b[i];
			i++;
		}
		else
		{
			a[k] = c[j];
			j++;
		}
		k++;
	}
	while (i < n1)
	{
		a[k++] = b[i++];
	}
	while (j < n2)
	{
		a[k++] = c[j++];
	}
	delete[]b;
	delete[]c;
}
template<class T>
void HelpMerge(T a[], int left, int right)
{
	if (left < right)
	{
		int mid = left + (right-left) / 2;
		HelpMerge(a, left, mid);
		HelpMerge(a, mid+1, right);
		Merge(a, left, right, mid);
	}
}
template<class T>
void MergeSort(T a[], int n)
{
	HelpMerge(a, 0, n - 1);
}
template<class T>
int findMax(T arr[], int n) {
    int maxNum = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxNum) {
            maxNum = arr[i];
        }
    }
    return maxNum;
}
template<class T>
void countingSort(T arr[], int n, int exp) {
    int* output = new int[n];
    int count[10] = {0};  

    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) { 
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
    delete[] output;
}
template<class T>
void radixSort(T arr[], int n) {
    int maxNum = findMax(arr, n);

    for (int exp = 1; maxNum / exp > 0; exp *= 10) {
        countingSort(arr, n, exp);
    }
}
