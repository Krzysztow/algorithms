#include "liststack.h"

#include <stdlib.h>
#include <string.h>

int ls_size(Stack *stack) {
    ListStack *as = (ListStack*)stack;
    return as->_size;
}

int ls_pop(Stack *stack, void *data) {
    ListStack *s = (ListStack*)stack;
    if (0 == s->_head) {
        return -1;
    }

    ListNode *node = s->_head;
    s->_head = node->next;

    memcpy(data, node->data, s->_nodeDataSize);

    node->next = *(s->_freeListPtr);
    *(s->_freeListPtr) = node;

    --(s->_size);

    return 0;
}

int ls_peek(Stack *stack, void *data) {
    ListStack *s = (ListStack*)stack;
    if (0 == s->_head) {
        return -1;
    }
		
	memcpy(data, s->_head->data, s->_nodeDataSize);
	return 0;
}

int ls_push(Stack *stack, void *data) {
    ListStack *s = (ListStack*)stack;

    if (0 == *(s->_freeListPtr)) {//no free space
        return -1;
    }

    //remove node from the free list
    ListNode *node = *(s->_freeListPtr);
    *(s->_freeListPtr) = node->next;

    //put it at the beginning of the stack
    node->next = s->_head;
    s->_head = node;
    ++(s->_size);

    //copy the data
    memcpy(node->data, data, s->_nodeDataSize);

    return 0;
}

void ls_priv_init(ListStack *stack, int dataItemSize, ListNode **freeListPtr, ListNode *ownedFreeList) {
    stack->base.push = ls_push;
    stack->base.pop = ls_pop;
    stack->base.size = ls_size;
    stack->base.peek = ls_peek;

    stack->_nodeDataSize = dataItemSize;
    stack->_size = 0;

    stack->_head = 0;
    stack->_freeListPtr = freeListPtr;
    stack->_ownedFreeList = ownedFreeList;
}

void ls_init(ListStack *stack, int dataItemSize, ListNode **freeListPtr) {
    ls_priv_init(stack, dataItemSize, freeListPtr, 0);
}

Stack *ls_create(int dataItemSize, int capacity) {
	ListStack *s = (ListStack*)malloc(sizeof(ListStack));
    int ListNodeSize = sizeof(ListNode);
	const int bufferSize = capacity * (sizeof(ListNode) + dataItemSize);
	void *buffer = malloc(bufferSize);
	s->_ownedFreeList = listFromBuffer(buffer, bufferSize, dataItemSize);
	ls_priv_init(s, dataItemSize, &(s->_ownedFreeList), s->_ownedFreeList);
	
	return (Stack*)s;
}

void ls_free(Stack *stack) {
	ListStack *s = (ListStack*)stack;
	if (0 != s->_ownedFreeList)
		free(s->_ownedFreeList);
	free(s);
}
