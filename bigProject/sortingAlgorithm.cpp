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
void Merge(int* a, int left, int right, int mid)
{
	int n1 = mid - left + 1;
	int n2 = right - mid;
	int* b = new int[n1];
	int* c = new int[n2];
	for (int i = 0; i < n1; i++)
		b[i] = a[left + i];
	for (int j = 0; j < n2; j++)
		c[j] = a[mid + 1 + j];
	int i = 0;
	int j = 0;
	int k = left;
	while (j < n2 && i < n1)
	{
		if (b[i] >= c[j])
		{
			a[k] = c[j];
			j++;
		}
		else if (b[i] < c[j])
		{
			a[k] = b[i];
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
void MergeSort(int* a, int left, int right)
{
	if (left < right)
	{
			int mid = left + (right - left) / 2;
			Sort(a, left, mid, k);
			Sort(a, mid + 1, right, k);
			Merge(a, left, right, mid);
		}
	
}
