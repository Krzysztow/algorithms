#ifndef LISTSTACK_H
#define LISTSTACK_H

#include "stack.h"
#include "list.h"

typedef struct {
    Stack base;

    int _nodeDataSize;

    int _size;
    ListNode **_freeListPtr;
    ListNode *_ownedFreeList;//if created with external buffer, this will be 0
    ListNode *_head;
} ListStack;

/**
 * If extenral buffer is used for data items, first create a list out of it
 * with list::listFromBuffer() and then init the stack with ls_init().
 * 
 * If the stack should alloc memory by itself, use ls_create() function (don't invoke ls_init() then!). 
 */
void ls_init(ListStack *stack, int dataItemSize, ListNode **freeListPtr);

/**
 * Constructor.
 * @dataItemSize - size of the elements stored in the array. Eg. int - sizeof(int), ptr to int - sizeof(int*);
 * @capacity - maximum number of elements to be stored in a stack.
 */
Stack *ls_create(int dataItemSize, int capacity);

/**
 * Destructor.
 */
void ls_free(Stack *stack);

#endif //LISTSTACK_H
