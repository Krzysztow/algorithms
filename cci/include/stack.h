#ifndef STACK_H
#define STACK_H

struct Stack;
typedef struct Stack Stack;

typedef int (*StackPush)(Stack*, void*);
typedef int (*StackPop)(Stack*, void*);
typedef int (*StackSize)(Stack*);
typedef int (*StackPeek)(Stack*, void*);

struct Stack {
    StackPush push;
    StackPop pop;
    StackSize size;
    StackPeek peek;
};

#endif //STACK_H
