#include "sortingAlgorithm.h"
#include "generateArrays.h"
#include "generateArrays.cpp"
#include "sortingAlgorithm.cpp"
#include "commandLineArguments.h"

//using namespace std;

int main(int argc, char* argv[]) {
    locale::global(locale(""));
    wcout.imbue(locale(""));
    showHelp();
    processArg(argc, argv);
    return 0;
}