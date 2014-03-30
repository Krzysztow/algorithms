#include "arraystack.h"

#include <stdlib.h>
#include <string.h>

int as_pop(Stack *stack, void *data) {
	ArrayStack *s = (ArrayStack*)stack;
	if (0 == s->_size) {
		return -1;
	}
	
	--(s->_size);
	void *d = (s->_arrayPtr + (s->_size * s->_dataItemSize));
	memcpy(data, d, s->_dataItemSize);
		
	return 0;
}

int as_peek(Stack *stack, void *data) {
	ArrayStack *s = (ArrayStack*)stack;
	if (0 == as_size(stack))
		return -1;
	
	void *d = (s->_arrayPtr + ((s->_size - 1) * s->_dataItemSize));
	memcpy(data, d, s->_dataItemSize);
	
	return 0;
}

int as_push(Stack *stack, void *data) {
	ArrayStack *s = (ArrayStack*)stack;
	if (s->_capacity == s->_size) {
		return -1;
	}	
	
	void *dest = (s->_arrayPtr + (s->_size * s->_dataItemSize));
	memcpy(dest, data, s->_dataItemSize);
	
	++(s->_size);
	
	return 0; 
}

int as_size(Stack *stack) {
	ArrayStack *s = (ArrayStack*)stack;
	return s->_size;
}

void as_priv_init(ArrayStack *stack, int dataItemSize, int capacity, void *arrayPtr, void *ownedPtr) {
	ArrayStack *s = stack;
	s->base.pop = as_pop;
	s->base.push = as_push;
	s->base.size = as_size;
	s->base.peek = as_peek;
	
	s->_size = 0;
	s->_ownedArray = ownedPtr;
	
	s->_dataItemSize = dataItemSize;
	s->_arrayPtr = arrayPtr;
	s->_capacity = capacity;
}

Stack *as_create(int dataItemSize, int capacity) {
	ArrayStack *s = (ArrayStack*)malloc(sizeof(ArrayStack));
	int bufferSize = capacity * sizeof(dataItemSize);
	s->_ownedArray = malloc(bufferSize);
	
	as_priv_init(s, dataItemSize, capacity, s->_ownedArray, s->_ownedArray);
	
	return (Stack*)s;
}

void as_free(ArrayStack *stack) {
	if (0 != stack->_ownedArray) {
		free(stack->_ownedArray);
	}
	
	free(stack);
}
