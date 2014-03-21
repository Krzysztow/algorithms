#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <assert.h>
#include <cstring>

typedef struct ListNode ListNode;

struct ListNode {
    ListNode(int data, ListNode* next = 0):
        data(data),
        next(next) {}

    int data;
    ListNode *next;
};

/**
 * removes duplicates from the list by iterating over it
 * and checking if the value hasn't occured earlier. If has
 * it's getting removed.
 */
void ln_removeDuplicates(ListNode *head) {
    std::map<int, int> pastData;
    ListNode *ptr = head;
    ListNode *lastPtr = 0;
    while (0 != ptr) {
        if (0 == pastData.count(ptr->data)) {
            pastData[ptr->data] = 1;
            lastPtr = ptr;
        }
        else {
            //remove the element
            ListNode *rmdNode = ptr;
            assert(0 != lastPtr);
            lastPtr->next = ptr->next;
            ptr = lastPtr;

            delete rmdNode;
        }

        ptr = ptr->next;
    }
}

void ln_rmAheadWith(ListNode *bPtr, int data) {
    if (0 == bPtr)
        return;

    ListNode *beforePtr = bPtr;
    ListNode *ptr = bPtr->next;

    while (0 != ptr) {
        if (data == ptr->data) {
            ListNode *rmdNode = ptr;
            beforePtr->next = ptr->next;
            ptr = beforePtr;

            delete rmdNode;
        }
        else {
            beforePtr = ptr;
        }

        ptr = ptr->next;
    }
}

void ln_removeDuplicates2(ListNode *head) {
    if (0 == head)
        return;

    ListNode *ptr = head;
    while (0 != ptr) {
        ln_rmAheadWith(ptr, ptr->data);
        ptr = ptr->next;
    }
}

void ln_print(ListNode *head) {
    if (0 == head)
        return;

    while (0 != head) {
        printf("%d\r\n", head->data);
        head = head->next;
    }
}

int main(int argc, const char *argv[]) {
    if (2 != argc && 3 != argc) {
        std::cout << "Usage: " << argv[0] << " <link-list-file> [1,2]" << std::endl;
        return 1;
    }

    int BuffSize = 256;
    char line[BuffSize];
    int readNo;
    std::ifstream f(argv[1]);

    std::list<int> input;
    input.push_back(1);
    input.push_back(2);
    input.push_back(1);
    input.push_back(3);
    input.push_back(2);

    std::list<int>::iterator it = input.begin();
    ListNode *head = 0;
    ListNode *lastPtr = 0;
    for (; input.end() != it; ++it) {
        ListNode *nodePtr = new ListNode(*it);

        if (0 == head)  {
            head = nodePtr;
            lastPtr = head;
        }
        else {
            lastPtr->next= nodePtr;
            lastPtr = nodePtr;
        }
    }

    printf("Before: \r\n");
    ln_print(head);

    if (0 == strcmp(argv[2], "1")) {
        printf("Algorithm 1\r\n");
        ln_removeDuplicates(head);
    }
    else if (0 == strcmp(argv[2], "2")) {
        printf("Algorithm 2\r\n");
        ln_removeDuplicates2(head);
    }
    else {
        std::cerr << "Unrecognized algoithm - could be 1 or 2" << std::endl;
    }

    printf("After: \r\n");
    ln_print(head);


    return 0;
}
