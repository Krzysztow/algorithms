#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "arraystack.h"

typedef struct MyQueue MyQueue;
/**
 * Used to enqueue data on the queue.
 * @return 0 if ok.
 */
typedef int (*Enqueue)(MyQueue*, void*);
/**
 * Used to dequque data from the queue
 * @return 0 if ok.
 */
typedef int (*Dequeue)(MyQueue*, void*);

struct MyQueue {
    Enqueue enqueue;
    Dequeue dequeue;
};

/**
 *************************************************
 * MyQueueSimple
 *************************************************
 * The Simplest implementation.
 * Assumes that the FIFO order is in the _stacks[0].
 * Whenever element is added, the order is reversed by moving elements into _stacks[1], then appending new one
 * and reversing again into _stacks[0].
 * Complexity for enqueueing-> O(n) (copying) + O(1) (adding) + O(n) (copying again) = O(n).
 * Memory complexity -> O(n) but with many allocations and deallocations (and it depends on stack implementaiton).
 *
 * Complexity for dequeueing O(1).
 */

#define MyQueueSimple_StacksNo 2

typedef struct MyQueueSimple MyQueueSimple;
struct MyQueueSimple {
    MyQueue base;

    Stack *_stacks[MyQueueSimple_StacksNo];
    int _elSize;
};

void mq_move_stacks(Stack *fs, Stack *ds, int elSize) {
    char item[elSize];
    while (0 != fs->size(fs)) {
        fs->pop(fs, &item);
        fs->push(ds, &item);
    }
}

void mqs_priv_move(MyQueueSimple *queue, int from, int to) {
    Stack *fs = queue->_stacks[from];
    Stack *ds = queue->_stacks[to];
    mq_move_stacks(fs, ds, queue->_elSize);
}

/**
 * Move all elements to the second queue (reversing order), append new one and
 * move elements back (so that good order is achieved)
 */
int mqs_enqueue(MyQueue *queue, void *data) {
    MyQueueSimple *mqs = (MyQueueSimple*)queue;
    //if there was space for existing  elements - there should be to move them
    mqs_priv_move(mqs, 0, 1);
    //this can fail, since we are adding new element
    int ret = mqs->_stacks[1]->push(mqs->_stacks[1], data);
    if (0 != ret)
        return -1;
    //again no error expected
    mqs_priv_move(mqs, 1, 0);

    return 0;
}

/**
 * _stacks[0] has proper FIFO order when popped.
 */
int mqs_dequeue(MyQueue *queue, void *data) {
    MyQueueSimple *mqs = (MyQueueSimple*)queue;
    Stack *fs = mqs->_stacks[0];
    return fs->pop(fs, data);
}

MyQueue *mqs_create(int elementSize, int capacity) {
    MyQueueSimple *mqs = (MyQueueSimple*)malloc(sizeof(MyQueueSimple));

    mqs->base.enqueue = mqs_enqueue;
    mqs->base.dequeue = mqs_dequeue;

    int i = 0;
    for (i = 0; i < MyQueueSimple_StacksNo; ++i) {
        mqs->_stacks[i] = as_create(elementSize, capacity);
    }

    mqs->_elSize = elementSize;

    return (MyQueue*)mqs;
}

void mqs_free(MyQueueSimple *queue) {
    int i = 0;
    for (i = 0; i < MyQueueSimple_StacksNo ; ++i) {
        as_free((ArrayStack*)queue->_stacks[i]);
    }

    free(queue);
}

/************************************************
 * MyQueueOptimized
 ************************************************
 * _stacks[1] is an enqueue stack. Data is moved to it on enqueue requests;
 * whenever dequeue is invoked, the data is taken from the reversed stack on _stacks[0]. If it's empty
 * then data is moved from _stacks[1].
 *
 * Complexity for enqueue is O(1), for dequeue is O(n) (worst case) and O(1) (best case).
 */

#define MyQueueAdvanced_StacksNo 2

typedef struct MyQueueAdvanced MyQueueAdvanced;
struct MyQueueAdvanced {
    MyQueue base;

    Stack *_stacks[MyQueueAdvanced_StacksNo];
    int _elSize;
};

int mqa_enqueue(MyQueue *queue, void *data) {
    MyQueueAdvanced *mqa = (MyQueueAdvanced*)queue;
    Stack *s = mqa->_stacks[1];

    return s->push(s, data);
}

int mqa_dequeue(MyQueue *queue, void *data) {
    MyQueueAdvanced *mqa = (MyQueueAdvanced*)queue;
    Stack *fs = mqa->_stacks[0];
    if (0 == fs->size(fs)) {//no elements in the first stack -> move from the second one (with reordering)
        mq_move_stacks(mqa->_stacks[1], fs, mqa->_elSize);
    }

    return fs->pop(fs, data);
}

MyQueue *mqa_create(int elSize, int capacity) {
    MyQueueAdvanced *mqa = (MyQueueAdvanced*)malloc(sizeof(MyQueueAdvanced));

    mqa->base.enqueue = mqa_enqueue;
    mqa->base.dequeue = mqa_dequeue;

    int i = 0;
    for (i = 0; i < MyQueueAdvanced_StacksNo; ++i) {
        mqa->_stacks[i] = as_create(elSize, capacity);
    }
    mqa->_elSize = elSize;

    return (MyQueue*)mqa;
}

/**
 * Main helper functions
 */
void enqueue(MyQueue *q, int data) {
    int ret = q->enqueue(q, &data);
    printf("\tenqueue %d\n", data);
    assert(0 == ret);
}

void dequeueExpect(MyQueue *q, int expData) {
    int el;
    int ret = q->dequeue(q, &el);
    printf("\tdequeue %d (?= %d)\n", el, expData);
    assert(el == expData);
}

int main(int argc, const char *argv[]) {
    const int ElementSize = sizeof(int);
    const int Capacity = 5;

    const int QueuesSize = 2;
    MyQueue *queues[QueuesSize];
    queues[0] = mqs_create(ElementSize, Capacity);
    queues[1] = mqa_create(ElementSize, Capacity);

    int el;
    int i;
    for (i = 0; i < QueuesSize; ++i) {
        printf("Test for queues[%d]\n", i);
        MyQueue *q = queues[i];

        enqueue(q, 0);
        enqueue(q, 1);
        dequeueExpect(q, 0);
        enqueue(q, 2);
        dequeueExpect(q, 1);
        dequeueExpect(q, 2);

        int j = 0;
        for (j = 0; j < Capacity; ++j) {
            enqueue(q, j);
        }

        for (j = 0; j < Capacity; ++j) {
            dequeueExpect(q, j);
        }
    }

    return 0;
}
