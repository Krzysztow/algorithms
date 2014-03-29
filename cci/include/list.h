#ifndef LIST_H
#define LIST_H

typedef struct ListNode ListNode;
typedef struct ListNode {
    ListNode *next;
    char data[0];
} ListNode;

ListNode *listFromBuffer(void *buffer, int bufferSize, int dataItemSize);

#endif //LIST_H
