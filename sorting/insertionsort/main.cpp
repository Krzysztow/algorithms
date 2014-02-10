#include <iostream>

#include <cstring>//for memcpy

void printUsage(const char *progName) {
    std::cout << "Usage: " << progName << " [fileName]" << std::endl;
    std::cout << "If fileName not provided, interactive console will be used";
}

int enlargeArray(int currentCapacity, int **arrayPtr) {
    const int initSize = 10;

    int newCapacity = (0 == currentCapacity) ? initSize : (2 * currentCapacity);
    int *newArray = new int[currentCapacity];

    const int newHalfByteWidth = currentCapacity * sizeof(int);
    //copy elements
    memcpy(newArray, *arrayPtr, newHalfByteWidth);
    //zero other elements
    memset(newArray + newHalfByteWidth, 0, newHalfByteWidth);

    delete []*arrayPtr;
    *arrayPtr = newArray;

    return newCapacity;
}

int *createAndPopulateInput(int &arraySize) {
    int arrayCapacity = 0;
    int *array = 0;
    arraySize = 0;

    std::cout << "Insert values, each separated with [ENTER]. Write some text to stop." << std::endl;

    int newValue = 0;
    std::cin >> newValue;
    while (!std::cin.fail()) {
        if (arraySize >= arrayCapacity) {
            //there is no more space, enlarge it
            arrayCapacity = enlargeArray(arrayCapacity, &array);
        }

        //set new array elemetn
        array[arraySize++] = newValue;

        //get another value
        std::cin >> newValue;
    }

    return array;
}

#include "insertsort.h"

int main(int argc, char const **argv) {
    int *inputArray = 0;
    int inputSize = 0;

    if (2 == argc) {
        //file name provided
        //TODO: open file and parse, otherwise show usage
        //
        std::cout << "Not implemented yet!" << std::endl;
        return -1;
    }
    else if (1 != argc) {
        //no file provided, but some additional argument
        printUsage(argv[0]);
        return 1;
    }

    //here, we assume input array contains
    inputArray = createAndPopulateInput(inputSize);

    K::insertsort2Min(inputArray, inputSize);

    std::cout << "Sort result:" << std::endl;
    for (int i = 0; i < inputSize; ++i) {
        std::cout << "[" << i << "] : " << inputArray[i] << std::endl;
    }

    //clean after yourself
    delete []inputArray;

    return 0;
}
