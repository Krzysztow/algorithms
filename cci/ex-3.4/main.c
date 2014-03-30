#include <stdio.h>

#include "arraystack.h"

int other(int from, int to) {
    int otherTower;
    if (1 == from + to)
        otherTower = 2;
    else if (2 == from + to)
        otherTower = 1;
    else if (3 == from + to)
        otherTower = 0;

    return otherTower;
}

void printStacks(Stack *stacks[], int stacksNo, int maxSize) {
    Stack *tempStack = as_create(sizeof(int), maxSize);

    int el;
    printf("-------------------------------");
    int i = 0;
    for (i = 0; i < stacksNo; ++i) {
        printf("\nStacks [%d]: ", i);
        while (0 != stacks[i]->size(stacks[i])) {
            stacks[i]->pop(stacks[i], &el);
            printf("%d, ", el);
            tempStack->push(tempStack, &el);
        }

        //restore stack
        while (0 != tempStack->size(tempStack)) {
            tempStack->pop(tempStack, &el);
            stacks[i]->push(stacks[i], &el);
        }
    }
    printf("\n");

    as_free((ArrayStack*)tempStack);
}

void move(Stack *stacks[], int no, int from, int to) {
    if (no > 1) {
        ArrayStack *s0 = (ArrayStack*)stacks[0]; ArrayStack *s1 = (ArrayStack*)stacks[1]; ArrayStack *s2 = (ArrayStack*)stacks[2];
        int otherTower = other(from, to);
        move(stacks, no - 1, from, otherTower);
        if (5 == no) printStacks(stacks, 3, 5);
        move(stacks, 1, from, to);
        if (5 == no) printStacks(stacks, 3, 5);
        move(stacks, no - 1, otherTower, to);
    }
    else {
        int el;
        stacks[from]->pop(stacks[from], &el);
        stacks[to]->push(stacks[to], &el);
    }
}

int main(int argc, const char *argv) {
    const int N = 5;
    const int StacksNo = 3;

    Stack *s[StacksNo];
    int i = 0;
    for (i = 0; i < StacksNo; ++i) {
        s[i] = as_create(sizeof(int), N);
    }

    for (i = N-1; i >= 0; --i) {
        s[0]->push(s[0], &i);
    }

    printStacks(s, StacksNo, N);
    move(s, N, 0, 2);
    printStacks(s, StacksNo, N);

    return 0;
}
