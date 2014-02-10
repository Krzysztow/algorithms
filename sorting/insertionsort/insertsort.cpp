#include "insertsort.h"
#include <cstring>//for memmove
/**
 * Function sorts array in increasing order - first element is the minimum one.
 */

void K::insertsortMin(int *array, int size) {
    //outer loop - take first unsorted yet element
    for (int outer = 1; outer < size; ++outer) {
        //with that unsorted element, probe every earlier element for comparison
        for (int inner = outer - 1; inner >= 0; --inner) {
            //the element is larger or equal, we can leave it here
            if (array[inner] <= array[inner + 1]) {
                break;
            }
            else {
                //is smaller, replace positions
                int tmp = array[inner];
                array[inner] = array[inner + 1];
                array[inner + 1] = tmp;
            }
        }
    }
}

/**
 * Alternative to above function - don't perform places substitutions. When appropriate
 * position is found, move elements [foundPosition, last - 1] by one position to the end
 */
void K::insertsort2Min(int *array, int size) {
    //outer loop
    for (int outer = 1; outer < size; ++outer) {
        //again iterate over sorted elements and find a place where to put new element
        for (int inner = outer - 1; inner >= 0; --inner) {
            //if iterated element is smaller, we need to put the chosen one after
            if (array[inner] <= array[outer]) {
                //if below holds, there is nothing to move
                if (inner + 1 != outer) {
                    int tmp = array[outer];
                    memmove(&array[inner + 2], &array[inner + 1], sizeof(int) * (outer - inner - 1));
                    array[inner + 1] = tmp;
                }
                break;
            }
        }
    }
}
