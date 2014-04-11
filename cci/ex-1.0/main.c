#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode ListNode;
struct ListNode {
    ListNode *next;
    char data[0];
};


typedef struct List List;
struct List {
    ListNode *head;
    int dataSize;
};
typedef void (*Printer)(List*, void*);

List *list_create(int elementSize) {
    List *list = (List*)malloc(sizeof(List));
    list->head = 0;
    list->dataSize = elementSize;

    return list;
}

void list_push_back(List *list, void *data) {
    ListNode *newNode = (ListNode*)malloc(sizeof(ListNode) + list->dataSize);
    newNode->next = 0;
    memcpy(newNode->data, data, list->dataSize);

    ListNode *node = list->head;
    if (0 == node)
        list->head = newNode;
    else {
        //finding last node could be optimized by keeping a pointer to it
        while (0 != node->next) {
            node = node->next;
        }
        node->next = newNode;
    }
}

int list_pop_back(List *list, void *data) {
    if (0 == list->head) {
        return -1;
    }

    ListNode *beforeBack = 0;
    ListNode *back = list->head;
    while (0 != back->next) {
        beforeBack = back;
        back = back->next;
    }

    memcpy(data, back->data, list->dataSize);

    if (list->head == back) {
        list->head = 0;
    }
    else {
        beforeBack->next = 0;
    }

    return 0;
}

void list_push_front(List *list, void *data) {
    ListNode *newNode = (ListNode*)malloc(sizeof(ListNode) + list->dataSize);
    memcpy(newNode->data, data, list->dataSize);

    newNode->next = list->head;
    list->head = newNode;
}

int list_pop_front(List *list, void *data) {
    ListNode *node = list->head;
    if (0 == node) {
        return -1;
   }

   memcpy(data, node, list->dataSize);
   list->head = node->next;
   free(node);

   return 0;
}

void list_print(List *list, Printer printFct) {
    ListNode *node = list->head;
    while (0 != node) {
        printFct(list, node->data);
        node = node->next;
    }
}

void list_reverse(List *list) {
    ListNode *currNode = list->head;
    ListNode *prevNode = 0;
    while (0 != currNode) {
        ListNode *next = currNode->next;
        currNode->next = prevNode;
        prevNode = currNode;

        currNode = next;
    }

    list->head = prevNode;
}

/**
 * Test
 */

void intPrinter(List *list, void *data) {
    int *intData = data;
    printf("-> %d ", *intData);
}

int main() {
    List *list = list_create(sizeof(int));

    printf("List: ");
    int data = 1;
    list_push_back(list, &data);
    data = 3;
    list_push_back(list, &data);
    data = 5;
    list_push_back(list, &data);
    data = 0;
    list_push_back(list, &data);
    list_print(list, intPrinter);

    printf("\r\nRevd: ");
    list_reverse(list);
    list_print(list, intPrinter);

    data = -1;
    list_push_front(list, &data);
    printf("\r\nFron: ");
    list_print(list, intPrinter);

    list_pop_back(list, &data);
    printf("\r\nPopb: ");
    list_print(list, intPrinter);

    list_pop_front(list, &data);
    printf("\r\nPopf: ");
    list_print(list, intPrinter);

    printf("\r\n");

    return 0;
}
