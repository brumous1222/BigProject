#include "commandLineArguments.h"

template<class InputIterator, class T>
InputIterator find(InputIterator first, InputIterator last, const T& val) {
    while (first != last) {
        if (*first == val) return first;
        ++first;
    }
    return last;
}

bool isNumber(string s) {
    for (int i = 0; i < s.length(); i++) {
        if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

void showHelp() {
    cout << "Usage: ./program [OPTIONS]\n"
        << "Options:\n"
        << "  -h            Show this help message\n"
        << "  -i            Integer mode\n"
        << "  -d            Dictionary mode\n"
        << "  -o <file>     Output results to file\n"
        << "  <algorithm>   Algorithm name (bubbleSort, quickSort, mergeSort,...)\n"
        << "  <size>        Input size (integer)\n"
        << "  <order>       Input order (random, sorted, revSorted, nearlySorted)\n"
        << "  <file>        Input file path (if no size/order)\n"
        << "Examples:\n"
        << "  ./program quickSort 1000 random\n"
        << "  ./program bubbleSort mergeSort input.txt -o result.txt\n";
}

void parseArgs(int argc, char* argv[], string& mode, vector<string>& algs, int& inputSize,
    string& inputOrder, string& inputPath, string& outputParams, string& outputFile) {
    for (int i = 1; i < argc; i++) { // Skip argv[0]
        if (strcmp(argv[i], "-i") == 0) {
            mode = "-i";
        }
        else if (strcmp(argv[i], "-d") == 0) {
            mode = "-d";
        }
        if (strcmp(argv[i], "-h") == 0) {
            showHelp();
            exit(0);
        }
        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            outputFile = argv[i++];
        }
        else if (find(algorithmNames.begin(), algorithmNames.end(), argv[i]) != algorithmNames.end()) {
            algs.push_back(argv[i]);
        }
        else if (isNumber(argv[i])) {
            inputSize = stoi(argv[i]);
        }
        else if (find(inputOrders.begin(), inputOrders.end(), argv[i]) != inputOrders.end()) {
            inputOrder = argv[i];
        }
        else {
            inputPath = argv[i];
        }
    }
}

bool isError(const string& mode, const vector<string>& algs, int inputSize, const string& inputPath) {
    if (mode.empty()) {
        cout << "Error: No mode specified\n";
        return false;
    }
    if (algs.empty()) {
        cout << "Error: No algorithm specified\n";
        return false;
    }
    if (inputSize <= 0 && inputPath.empty()) {
        cout << "Error: No valid input size or file specified\n";
        return false;
    }
    return true;
}

void generateArray(const string& fileName, int n, int dataType) {
    ofstream file;
    file.open(fileName);
    int* arr = new int[n];
    generateData(arr, n, dataType);
    file << n << "\n";
    for (int i = 0; i < n; i++) {
        file << arr[i] << " ";
    }
    file.close();
}

void processSort(vector<string> algs,const string& inputFile, const string& outputFile, const string& inputType) {

    for (int i = 0; i < algs.size(); i++) {

        ifstream file;
        file.open(inputFile);
        int n;
        file >> n;
        int* arr = new int[n];
        for (int i = 0; i < n; i++) {
            file >> arr[i];
        }
        file.close();

        string alg = algs[i];
        if (alg == "selectionSort") {
            outputResulttoFile(outputFile, selectionSort, arr, n, "selectionSort", inputType);
        }
        if (alg == "insertionSort") {
            outputResulttoFile(outputFile, insertionSort, arr, n, "insertionSort", inputType);
        }
        if (alg == "binaryInsertionSort") {
            outputResulttoFile(outputFile, binaryInsertionSort, arr, n, "binaryInsertionSort", inputType);
        }
        if (alg == "bubbleSort") {
            outputResulttoFile(outputFile, bubbleSort, arr, n, "bubbleSort", inputType);
        }
        if (alg == "shakerSort") {
            outputResulttoFile(outputFile, shakerSort, arr, n, "shakerSort", inputType);
        }
        if (alg == "shellSort") {
            outputResulttoFile(outputFile, shellSort, arr, n, "shellSort", inputType);
        }
        if (alg == "heapSort") {
            outputResulttoFile(outputFile, heapSort, arr, n, "heapSort", inputType);
        }
        if (alg == "mergeSort") {
            outputResulttoFile(outputFile, heapSort, arr, n, "heapSort", inputType);
        }
        if (alg == "quickSort") {
            outputResulttoFile(outputFile, quickSort, arr, n, "quickSort", inputType);
        }
        //if (alg == "counting-sort") {
        //    record = getRecord(a, n, countingSort, countingSort);
        //}
        //if (alg == "radix-sort") {
        //    record = getRecord(a, n, radixSort, radixSort);
        //}
        //if (alg == "flash-sort") {
        //    record = getRecord(a, n, flashSort, flashSort);
        //}
        delete[] arr;
    }
}

void processArg(int argc, char* argv[]) {
    string mode, inputOrder, inputPath, outputFile;
    vector<string> algs;
    int inputSize = 0;

    parseArgs(argc, argv, mode, algs, inputSize, inputOrder, inputPath, outputFile);

    if (!isError(mode, algs, inputSize, inputPath)) {
        return;
    }

    if (inputSize > 0) {
        if (!inputOrder.empty()) {
            generateArray(inputPath, inputSize, distance(inputOrders.begin(), find(inputOrders.begin(), inputOrders.end(), inputOrder)));
            processSort(algs, inputPath, outputFile, inputOrder);
        }
        else {
            for (size_t i = 0; i < inputOrders.size(); i++) {
                cout << "Input order: " << inputOrders[i] << "\n";
                cout << "--------------------\n";
                int j = (i == 0 ? 1 : i == 1 ? 3 : i == 2 ? 4 : 2);
                string filename = "input_" + to_string(j) + ".txt";
                generateArray(filename, inputSize, i);
                processSort(algs, filename, outputFile, j);
            }
        }
    }
    else {
        ifstream file(inputPath);
        if (!file) {
            cout << "Error: File not found\n";
            return;
        }
        int n; file >> n;
        file.close();
        cout << "Input size: " << n << "\n";
        processSort(algs, inputPath, outputFile, inputOrder);
    }
}