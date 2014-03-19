#include <stdio.h>
#include <cstring>

typedef unsigned char uchar;

void clearBit(uchar *bitArray, int bitPos) {
    uchar *ptr = bitArray + bitPos / 8;
    uchar mask = bitPos % 8;

    *ptr &= ~(mask);
}

void setBit(uchar *bitArray, int bitPos) {
    uchar *ptr = bitArray + bitPos / 8;
    uchar mask = (0x01 << bitPos % 8);

    *ptr |= mask;
}

int checkBit(uchar *bitArray, int bitPos) {
    uchar *ptr = bitArray + bitPos / 8;
    uchar mask = (0x01 << bitPos % 8);

    return (*ptr & mask);
}

int bitCharSize(int elementsNo) {
    int bitArraySize = elementsNo / 8;
    if (0 != elementsNo % 8)
        bitArraySize++;

    return bitArraySize;
}

/** This method assumes that restriction to no buffer
 *  is having a constant size array
 */
int removeDuplicates(char *array, int size) {
    //assume an ASCII character set )128 characters)
    int bas = bitCharSize(128);
    uchar bitArray[bas];
    memset(bitArray, 0, bas);

    char *currPtr = array;
    char *lastPtr = array;
    while ('\0' != *currPtr) {
        if (checkBit(bitArray, *currPtr)) {
            //bit set - there was already a character, dont advance pointers
        }
        else {
            //if not set, set it move value to duplicated positions
            setBit(bitArray, *currPtr);
            *lastPtr = *currPtr;
            ++lastPtr;
        }

        ++currPtr;
    }

    //copy the nullpointer
    *lastPtr = *currPtr;

    return currPtr - array - 1;
}

int removeDuplicates2(char *array, int size) {
    /*
     * There are two options on how to do it:
     * - having a length, we iterate over chars and for everyone
     * go over all following characters and check if they are not the same.
     * If they are, null them to '\0'. But afterwards we would have to squeeze array to remove nulls.
     * - iterate over all chars and for everyone go over all following characters
     *   with two pointers - one normally scanning input, and the other keeping a track
     *   over non-tduplicated characters. If one is the same, don't increemnet the second
     *   pointer. If the value is diffferent, copy it to the place where second one points
     *   and increment both.
     *
     *   Chosen second option, since seems more difficult compact.
    */

    char *ptr = array;
    char *nextPtr = ptr;
    char *copyPtr = ptr;

    while ('\0' != *ptr) {
        nextPtr = ptr + 1;
        copyPtr = nextPtr;
        while ('\0' != *nextPtr) {
            if (*nextPtr != *ptr) {//nonduplicated
                *copyPtr = *nextPtr;
                ++copyPtr;
            }
            ++nextPtr;
        }
        *copyPtr = '\0';
        ++ptr;
    }

    return nextPtr - array;
}

int main(int argc, const char *argv[]) {
    if (2 != argc) {
        printf("Usage: %s \"<string>\"", argv[0]);
        return 1;
    }

    //add 1 to the length to copy the '\0' character
    //we can run algorithm including that character
    int size = strlen(argv[1]) + 1;
    char data[size];
    memcpy(data, argv[1], size);

    int newSize = removeDuplicates(data, size);
    printf("Old value: %s\r\n", argv[1]);
    printf("New value: %s\r\n", data);

    memcpy(data, argv[1], size);
    newSize = removeDuplicates2(data, size);
    printf("New value2: %s\r\n", data);

    return 0;
}
