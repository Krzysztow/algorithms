#include "stack.h"

typedef struct ArrayStack ArrayStack;

struct ArrayStack {
	Stack base;
	
	int _size;
	
	int _dataItemSize;
	void *_ownedArray;
	void *_arrayPtr;
	int _capacity;
}; 


Stack *as_create(int dataItemSize, int capacity);
void as_free(ArrayStack *stack);
