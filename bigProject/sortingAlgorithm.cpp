#include "sortingAlgorithm.h"
#include <string>

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
void helpQuickSort(T arr[], int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high);
        helpQuickSort(arr, low, pivot - 1);
        helpQuickSort(arr, pivot + 1, high);
    }
}
template<class T>
void quickSort(T arr[], int n) {
    helpQuickSort(arr, 0, n - 1);
}
template<class T>
void helpInsertionSort(T arr[], int low, int high) {
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
    helpInsertionSort(arr, 0, n - 1);
}
template <class T>
void introSort(T arr[], int n) {
    int depthLimit = 2 * log(n);
    quickSort(arr, 0, n - 1, depthLimit);
    insertionSort(arr, n);
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
void merge(T a[], int left, int right, int mid) {
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
void helpMerge(T a[], int left, int right)
{
	if (left < right)
	{
		int mid = left + (right-left) / 2;
		helpMerge(a, left, mid);
		helpMerge(a, mid+1, right);
		merge(a, left, right, mid);
	}
}
template<class T>
void mergeSort(T a[], int n)
{
	helpMerge(a, 0, n - 1);
}
int findMaxNum(int arr[], int n) {
    int maxNum = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxNum) {
            maxNum = arr[i];
        }
    }
    return maxNum;
}
int getMaxString(void *array, int n) {
    wstring *arr = (wstring*) array;
    int maxLen = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i].length() > maxLen)
            maxLen = arr[i].length();
    }
    return maxLen;
}
void countingSort(int arr[], int n) {
    int maxNum = findMaxNum(arr, n);
    int *counting = new int [maxNum + 1]; // create an array to store frequency of each num
    for (int i = 0; i < n; i++) { // update counting
        counting[arr[i]]++;
    }
    int currPrefixSum = 0;
    for (int i = 0; i <= maxNum; i++) { // use prefixSum to make counting[i] represent for end idx of it in sorted arr
        currPrefixSum += counting[i];
        counting[i] = currPrefixSum;
    }

    for (int i = maxNum; i > 0; i--) { // shift to right one cell, make counting[i] represents for it's begin idx in sorted arr
        counting[i] = counting[i - 1];
    }
    counting[0] = 0;
    int *res = new int[n]; // create an array to store the result
    for (int i = 0; i < n; i++) // sort the nums
    {
        res[counting[arr[i]++]] = arr[i];
    }
    for(int i = 0; i < n; i++) // copy result array to arr
    {
        arr[i] = res[i];
    }
}
void sortByDigit(int arr[], int n, int exp) {
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
// void sortByStringIndex(void *array, int n, int index) { // using void *arr because I can not use string *
//     wstring *arr = (wstring*) array; // cast to string*
//     wstring* output= new wstring[n];
//     int count[65536] = {0};

//     for (int i = 0; i < n; i++) {
//         wchar_t ch = (arr[i].length() > index) ? arr[i][arr[i].length() - 1 - index] : 0;
//         count[ch]++;
//     }

//     for (int i = 1; i < 65536; i++) {
//         count[i] += count[i - 1];
//     }

//     for (int i = n - 1; i >= 0; i--) {
//         wchar_t ch = (arr[i].length() > index) ? arr[i][arr[i].length() - 1 - index] : 0;
//         output[count[ch] - 1] = arr[i];
//         count[ch]--;
//     }

//     for (int i = 0; i < n; i++) {
//         arr[i] = output[i];
//     }
//     delete[] output;
// }
void radixSortNums(int arr[], int n) {
    int maxNum = findMaxNum(arr, n);
    for (int exp = 1; maxNum / exp > 0; exp *= 10) {
        sortByDigit(arr, n, exp);
    }
}
// void radixSortStrings(void *array, int n) { // using void *arr because I can not use string *
//     wstring *arr = (wstring*) array; // cast to string*
//     int maxLen = getMaxString(arr, n);
//     for (int index = maxLen - 1; index >= 0; index--) {
//         sortByStringIndex(arr, n, index);
//     }
// }
template<class T>
void bubbleSort(T arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

template<class T>
void shellSort(T arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i += 1)
        {
            T temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

template <class T>
void naturalMergeSort(T arr[], int n) {
    while (true) {
        int left = 0;
        bool sorted = true;

        while (left < n) {
            int mid = left;

            while (mid + 1 < n && arr[mid] <= arr[mid + 1]) {
                mid++;
            }

            if (mid == n - 1) {
                break;
            }

            int right = mid + 1;

            while (right + 1 < n && arr[right] <= arr[right + 1]) {
                right++;
            }

            merge(arr, left, mid, right);
            left = right + 1;

            sorted = false;
        }

        if (sorted) {
            break;
        }
    }
}
