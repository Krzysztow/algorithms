#include <iostream>
#include <cstring>//for strlen

void reverseString(char *s) {
    if (0 == s) {
        std::cout << "Empty string" << std::endl;
        return;
    }

    char *first = s;
    char *last = s;
    //set last to the last but one value
    while ('\0' != *last) {
        last++;
    }
    last--;//we don't want to move null-erminator

    while (first < last) {
        char tmp = *first;
        *first = *last;
        *last = tmp;
        last--;
        first++;
    }
}

int main(int argc, char** argv) {
    if (2 != argc) {
        std::cout << "Usage: " << argv[0] << "\"<text>\"" << std::endl;
        return 1;
    }

    const int inputSize = strlen(argv[1]);
    char input[inputSize + 1];
    memcpy(input, argv[1], inputSize + 1);//copy string with the termination symbol

    reverseString(input);

    std::cout << "Result: " << input;

    return 0;
}
