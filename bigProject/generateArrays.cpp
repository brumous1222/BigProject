#include "generateArrays.h"
#include "sortingAlgorithm.h"

using namespace std;
using namespace chrono;

bool isSorted(int arr[], int n) {
	for (int i = 0; i < n - 1; i++) {
		if (arr[i] > arr[i + 1]) {
			return false;
		}
	}
	return true;
}

void reverseArray(int arr[], int n) {
	int left = 0;
	int right = n - 1;

	while (left < right) {
		int temp = arr[left];
		arr[left] = arr[right];
		arr[right] = temp;

		left++;
		right--;
	}
}

void generateRandomArray(int arr[], int n, int k) {
	if (k <= 1000000000) {
		cout << "The maximum value of k must be greater than 10^9\n";
		return;
	}
	else {
		srand((unsigned)time(NULL));
		for (int i = 0; i < n; ++i) {
			arr[i] = rand() % (k + 1);
		}
	}
}

void generateSortedArray(int arr[], int n, int k) {
	generateRandomArray(arr, n, k);
	introSort(arr, n);
}

void generateReverseArray(int arr[], int n, int k) {
	generateSortedArray(arr, n, k);
	reverseArray(arr, n);
}

void generateNearlySortedArray(int arr[], int n, int k) {
	generateSortedArray(arr, n, k);
	int swapCount = max(1, n / 10); //So lan trao doi (10% cua n)

	srand((unsigned)time(NULL));
	for (int i = 0; i < swapCount; ++i) {
		int idx1 = rand() % n; // Chon ngau nhien chi so thu nhat
		int idx2 = rand() % n; // Chon ngau nhien chi so thu hai
		swap(arr[idx1], arr[idx2]);
	}
}

void measureSortingTime(sortFunc sortName, int arr[], int n, const string& algoName, const string& inputType) {
	int* tempArr = new int[n];
	copy(arr, arr + n, tempArr);

	auto start = high_resolution_clock::now();
	sortName(tempArr, n);
	auto end = high_resolution_clock::now();

	auto duration = duration_cast<milliseconds>(end - start);

	cout << "Algorithm: " << algoName << endl;
	cout << "Input Type: " << inputType << endl;
	cout << "Input Size: " << n << endl;
	cout << "Execution Time: " << duration.count() << " ms" << endl;

	delete[] tempArr;
}
