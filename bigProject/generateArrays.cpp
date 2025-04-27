#include "generateArrays.h"

using namespace std;
using namespace chrono;

template <class T>
bool isSorted(T arr[], int n) {
	for (int i = 0; i < n - 1; i++) {
		if (arr[i] > arr[i + 1]) {
			return false;
		}
	}
	return true;
}

template <class T>
void reverseArray(T arr[], int n) {
	int left = 0;
	int right = n - 1;

	while (left < right) {
		T temp = arr[left];
		arr[left] = arr[right];
		arr[right] = temp;

		left++;
		right--;
	}
}

template <class T>
void generateRandomArray(T arr[], int n, int k) {
	const int MIN_VAL = 1e9;
	if (k <= MIN_VAL) {
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

template <class T>
void generateSortedArray(T arr[], int n, int k) {
	generateRandomArray(arr, n, k);
	introSort(arr, n);
}

template <class T>
void generateReverseArray(T arr[], int n, int k) {
	generateSortedArray(arr, n, k);
	reverseArray(arr, n);
}

template <class T>
void generateNearlySortedArray(T arr[], int n, int k) {
	generateSortedArray(arr, n, k);
	int swapCount = max(1, n / 10); // swap counts (10% of n)

	srand((unsigned)time(NULL));
	for (int i = 0; i < swapCount; ++i) {
		int idx1 = rand() % n; //  pick randomly first idx
		int idx2 = rand() % n; // pick randomly second idx;
		swap(arr[idx1], arr[idx2]);
	}
}

template <class T>
void generateData(T arr[], int n, const int order) {
	const int MIN_VAL = 2e9;
	switch (order) {
	case 0:
		generateRandomArray(arr, n, MIN_VAL);
		break;
	case 1:
		generateSortedArray(arr, n, MIN_VAL);
		break;
	case 2:
		generateReverseArray(arr, n, MIN_VAL);
		break;
	case 3:
		generateNearlySortedArray(arr, n, MIN_VAL);
		break;
	default:
		cout << ("Error: unknown input type!\n");
	}
}

template <class T>
void outputResultToFile(const string& outputFile, void (*sortFunc)(T[], int), T arr[], int n,
	const string& algoName, const string& order) {
	ofstream out;
	if (!outputFile.empty()) {
		out.open(outputFile, ios::app);
		if (!out) {
			cout << "Error: Cannot open output file " << outputFile << "\n";
			return;
		}
	}

	T* tempArr = new T[n];
	copy(arr, arr + n, tempArr);

	auto start = chrono::high_resolution_clock::now();
	sortFunc(tempArr, n);
	auto end = chrono::high_resolution_clock::now();

	auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

	string output = "Algorithm: " + algoName + "\n" +
		"Input Type: " + order + "\n" +
		"Input Size: " + to_string(n) + "\n" +
		"Execution Time: " + to_string(duration.count()) + " ms\n" +
		"-------------------------\n";

	if (!outputFile.empty()) {
		out << output;
		out.close();
	}
	else {
		cout << output;
	}

	if (!isSorted(tempArr, n)) {
		cout << "WARNING: " << algoName << " failed to sort correctly!\n";
	}

	delete[] tempArr;
}