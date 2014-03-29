#include "list.h"

ListNode *listFromBuffer(void *buffer, int bufferSize, int dataItemSize) {
    const int NodeSize = sizeof(ListNode) + dataItemSize;

    if (bufferSize < NodeSize)
        return 0;

    ListNode *head = (ListNode*)buffer;
    head->next = 0;

    void *prev = 0;//no matter what here initially is
    void *next = head;
    int consumedBytes = NodeSize;
    while (consumedBytes <= bufferSize) {
        prev = next;
        next = prev + NodeSize;
        ((ListNode*)prev)->next = (ListNode*)next;

        consumedBytes += NodeSize;
    }

    //prev points to the last element
    ((ListNode*)prev)->next = 0;

    return head;
}

