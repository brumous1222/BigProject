#include "sortingAlgorithm.h"
#include "generateArrays.h"
#include "commandLineArguments.h"
#include "commandLineArguments.cpp"

int main(int argc, char* argv[]) {
    locale::global(locale(""));
    wcout.imbue(locale(""));
    showHelp();
    processArg(argc, argv);
    return 0;
}