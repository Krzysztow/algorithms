#include <assert.h>
#include <malloc.h>
#include <stdio.h>

typedef struct ListNode ListNode;

struct ListNode {
    int data;
    ListNode *next;
};

ListNode *ln_create(int data) {
    ListNode *node = (ListNode*)malloc(sizeof(ListNode));
    node->data = data;
    node->next = 0;

    return node;
}

ListNode *ln_append(ListNode *appendee, ListNode *appended) {
    appendee->next = appended;

    return appended;
}

void retVoid() {

}

/**
 * Returns nth to last node element (if exists), otherwise 0.
 * I take up on convention, that 0th to last is the last element.
 */
ListNode *findNthToLast(ListNode *head, int nthPos) {
    if (0 == head)
        return 0;

    ListNode *aheadPtr = head;
    for (int i = 0; i < nthPos; ++i) {
        if (0 == aheadPtr->next) {
            return 0;
        }
        aheadPtr = aheadPtr->next;
    }

    ListNode *nthToLastPtr = head;
    while (0 != aheadPtr->next) {
        aheadPtr = aheadPtr->next;
        nthToLastPtr = nthToLastPtr->next;
    }

    return nthToLastPtr;
}

int main(int argc, const char *argv[]) {
    ListNode *head = ln_create(0);
    ListNode *last = ln_append(head, ln_create(1));
    last = ln_append(last, ln_create(2));
    last = ln_append(last, ln_create(3));
    last = ln_append(last, ln_create(4));
    last = ln_append(last, ln_create(5));
    last = ln_append(last, ln_create(6));
    last = ln_append(last, ln_create(7));
    last = ln_append(last, ln_create(8));
    last = ln_append(last, ln_create(9));
    last = ln_append(last, ln_create(10));

    assert(0 == 0);
    ListNode *ret;
    //on an empty list
    ret = findNthToLast(0, 10);
    assert(0 == ret);
    //on a one element list
    ret = findNthToLast(last, 0);
    assert(ret == last);

    ret = findNthToLast(last, 1);
    assert(0 == ret);

    //normal working
    ret = findNthToLast(head, 0);
    assert(last == ret);

    ret = findNthToLast(head, 5);
    assert(0 != ret);
    assert(5 == ret->data);

    ret = findNthToLast(head, 10);
    assert(head == ret);

    ret = findNthToLast(head, 11);
    assert(0 == ret);

    printf("Success!\r\n");

    return 0;
}
