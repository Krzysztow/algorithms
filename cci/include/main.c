#include <stdio.h>

#include "stack.h"
#include "liststack.h"
#include "arraystack.h"

int main(int argc, const char *argv[]) {
	const int StacksNo = 2;
	Stack *stacks[StacksNo];

    stacks[0] = ls_create(sizeof(int), 5);
	stacks[1] = as_create(sizeof(int), 5);

	int stackIt = 0;
	for (stackIt = 0; stackIt < StacksNo; ++stackIt) {
		Stack *s = stacks[stackIt];
		int i = 0;
		for (i = 0; i < 8; ++i) {
			if (0 != s->push(s, &i)) {
				fprintf(stderr, "Error on pushing %d\n", i);
			}
		}

        int peekData;
		int data;
		while (0 != s->size(s)) {
            s->peek(s, &peekData);
			if (0 == s->pop(s, &data)) {
				printf("Popped %d, peeked %d\n", data, peekData);
			}
			else {
				fprintf(stderr, "Cannot get element\n");
			}
		}
	}

    return 0;
}
