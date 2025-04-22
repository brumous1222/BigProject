#include "commandLineArguments.h"

template<class InputIterator, class T>
InputIterator find(InputIterator first, InputIterator last, const T& val) {
    while (first != last) {
        if (*first == val) return first;
        ++first;
    }
    return last;
}

bool isNumber(const string& s) {
    for (int i = 0; i < s.length(); i++) {
        if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

void showHelp() { // show the help menu
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
        << "  ./program quickSort -i 1000 random\n"
        << "  ./program bubbleSort mergeSort input.txt -o result.txt\n";
}

void parseArgs(int argc, char* argv[], string& mode, vector<string>& algs, int& inputSize,
    string& inputOrder, string& inputPath, string& outputFile) {
    if (argc <= 1) { // maybe that users do not know how to use this program, so they pass nothing to command line argument
        showHelp();
        exit(0);
    }

    for (int i = 1; i < argc; i++) { // Skip argv[0] because everything we need is from argv[1]
        if (strcmp(argv[i], "-h") == 0) { // check if user needs some help
            showHelp();
            exit(0);
        }
        if (strcmp(argv[i], "-i") == 0) { // sort integer mode
            mode = "-i";
        }
        else if (strcmp(argv[i], "-d") == 0) { // sort dictionary mode
            mode = "-d";
        }
        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) { // get output file name (or file path) if there is "-o" flag
            outputFile = argv[i++];
        }
        else if (find(algorithmNames.begin(), algorithmNames.end(), argv[i]) != algorithmNames.end()) { // get algo name from a list
            algs.push_back(argv[i]);
        }
        else if (isNumber(argv[i])) { // convert input size from string to int
            inputSize = stoi(argv[i]);
        }
        else if (find(inputOrders.begin(), inputOrders.end(), argv[i]) != inputOrders.end()) { // find input order option
            inputOrder = argv[i];
        }
        else {
            inputPath = argv[i]; // get input path
        }
    }
}

bool isError(const string& mode, const vector<string>& algs, int inputSize, const string& inputPath) {
    if (mode.empty()) { // no mode is provided
        cout << "Error: No mode specified\n";
        return true;
    }
    if (algs.empty()) { // no algorithm is specified
        cout << "Error: No algorithm specified\n";
        return true;
    }
    if (inputSize <= 0 && inputPath.empty()) { // ??
        cout << "Error: No valid input size or file specified\n";
        return true;
    }
    return false;
}

void generateArray(const string& fileName, int n, const int order) { // generate an array and put it into a file
    ofstream file;
    file.open(fileName);
    if (!file.is_open()) {
        cout << "Maybe we do not have a valid file name" << endl;
        exit(0);
    }
    int* arr = new int[n];
    generateData(arr, n, order);
    file << n << "\n";
    for (int i = 0; i < n; i++) {
        file << arr[i] << " ";
    }
    file.close();
}

void processSort(vector<string>& algs,const string& inputFile, const string& outputFile, const string& order) { // use sort algorithm to sort the array, measure the time
    for (int i = 0; i < algs.size(); i++) {
        ifstream file;
        file.open(inputFile);
        int n;
        file >> n;
        int* arr = new int[n];
        if (!arr) {
            cout << "Can not create the array" << endl;
            exit(0);
        }
        for (int i = 0; i < n; i++) {
            file >> arr[i];
        }
        file.close();

        string alg = algs[i];
        if (alg == "selectionSort") {
            outputResultToFile(outputFile, selectionSort, arr, n, "selectionSort", order);
        }
        if (alg == "insertionSort") {
            outputResultToFile(outputFile, insertionSort, arr, n, "insertionSort", order);
        }
        if (alg == "binaryInsertionSort") {
            outputResultToFile(outputFile, binaryInsertionSort, arr, n, "binaryInsertionSort", order);
        }
        if (alg == "bubbleSort") {
            outputResultToFile(outputFile, bubbleSort, arr, n, "bubbleSort", order);
        }
        if (alg == "shakerSort") {
            outputResultToFile(outputFile, shakerSort, arr, n, "shakerSort", order);
        }
        if (alg == "shellSort") {
            outputResultToFile(outputFile, shellSort, arr, n, "shellSort", order);
        }
        if (alg == "heapSort") {
            outputResultToFile(outputFile, heapSort, arr, n, "heapSort", order);
        }
        if (alg == "mergeSort") {
            outputResultToFile(outputFile, heapSort, arr, n, "heapSort", order);
        }
        if (alg == "quickSort") {
            outputResultToFile(outputFile, quickSort, arr, n, "quickSort", order);
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
    const string DEFAULT_NAME = "Array.txt";
    string mode, inputOrder, inputPath, outputFile;
    vector<string> algs; // a vector that stores all algorithms that user wants to use
    int inputSize = 0;

    // after we get the main arguments, we are gonna process that argv string to know what user wants to do
    parseArgs(argc, argv, mode, algs, inputSize, inputOrder, inputPath, outputFile);

    // something went wrong
    if (isError(mode, algs, inputSize, inputPath)) {
        return;
    }

    if (inputSize > 0) {
        if (!inputOrder.empty()) { // generate an array with the chosen input order from argv and sort it
            if (inputPath.empty()) { // maybe the user has not pass in a input file
                inputPath = DEFAULT_NAME;
            }
            generateArray(inputPath, inputSize, distance(inputOrders.begin(), find(inputOrders.begin(), inputOrders.end(), inputOrder)));
            processSort(algs, inputPath, outputFile, inputOrder);
        }
        else { // if user does not provide any order of the input, we will do every order
            for (size_t i = 0; i < inputOrders.size(); i++) {
                cout << "Input order: " << inputOrders[i] << "\n";
                cout << "--------------------\n";
                int j = (i == 0 ? 1 : i == 1 ? 3 : i == 2 ? 4 : 2); // ??
                string filename = "input_" + to_string(j) + ".txt";
                generateArray(filename, inputSize, i);
                processSort(algs, filename, outputFile, inputOrder);
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