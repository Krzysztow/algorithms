#include <stdio.h>
#include <string.h>

struct Stack;
typedef struct Stack Stack;

typedef int (*StackPush)(Stack*, void*);
typedef int (*StackPop)(Stack*, void*);
typedef int (*StackSize)(Stack*);

struct Stack {
    StackPush push;
    StackPop pop;
    StackSize size;
};

typedef struct ListNode ListNode;
typedef struct ListNode {
    ListNode *next;
    char data[0];
} ListNode;

typedef struct {
    Stack base;

    int _nodeDataSize;

    int _size;
    ListNode **_freeListPtr;
    ListNode *_head;
} ArrayStack;

int as_size(Stack *stack) {
    ArrayStack *as = (ArrayStack*)stack;
    return as->_size;
}

int as_pop(Stack *stack, void *data) {
    ArrayStack *s = (ArrayStack*)stack;
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

int as_push(Stack *stack, void *data) {
    ArrayStack *s = (ArrayStack*)stack;

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

ListNode *listFromBuffer(void *buffer, int bufferSize, int dataItemSize) {
    const int NodeSize = sizeof(ListNode) + dataItemSize;

    if (bufferSize < NodeSize)
        return 0;

    ListNode *head = (ListNode*)buffer;
    head->next = 0;

    void *prev = 0;//no matter what here initially is
    void *next = head;
    int consumedBytes = NodeSize;
    while (consumedBytes < bufferSize) {
        prev = next;
        next = prev + NodeSize;
        ((ListNode*)prev)->next = (ListNode*)next;

        consumedBytes += NodeSize;
    }

    //prev points to the last element
    ((ListNode*)prev)->next = 0;

    return head;
}

void as_init(ArrayStack *stack, int dataItemSize, ListNode **freeListPtr) {
    stack->base.push = as_push;
    stack->base.pop = as_pop;
    stack->base.size = as_size;

    stack->_nodeDataSize = dataItemSize;
    stack->_size = 0;

    stack->_head = 0;
    stack->_freeListPtr = freeListPtr;
}
//void void stack_init(Stack *stack, char *buffer, int buffSize)



int main(int argc, const char *argv[]) {
    const int BufferSize = 50;
    char buffer[BufferSize];
    ListNode *list = listFromBuffer(buffer, BufferSize, sizeof(int));

    ArrayStack as;
    as_init(&as, sizeof(int), &list);

    Stack *s = (Stack*)&as;//could be also s = &(as.base)

    int i = 0;
    for (i = 0; i < 8; ++i) {
        if (0 != s->push(s, &i)) {
            fprintf(stderr, "Error: can't insert %d\n", i);
        }
    }

    int data;
    while (0 != s->size(s)) {
        if (0 == s->pop(s, &data)) {
            printf("Data: %d\n", data);
        }
        else {
            fprintf(stderr, "Error: can't pop data.\n");
        }
    }

    return 0;
}
