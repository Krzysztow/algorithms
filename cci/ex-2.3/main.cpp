#include <assert.h>
#include <iostream>
#include <cstring>

template <class T>
struct Node {
    public:
        Node(const T &data):
            data(data),
            next(0) {}

        Node *linkTo(Node *other) {
            next = other;

            return other;
        }

        static void print(Node *head) {
            if (0 != head)
                std::cout << head->data;

            head = head->next;
            while (0 != head) {
                std::cout <<  "->" << head->data;
                head = head->next;
            }

            std::cout << std::endl;
        }

        static void removeNode(Node *node) {
            if (0 == node->next) {
                assert(false);
                std::cerr << "Last list element being deleted!" << std::endl;
                return;
            }

            Node *next = node->next;
            memcpy(node, next, sizeof(Node<T>));

            delete next;
        }

private:
    T data;
    Node<T> *next;
};



typedef Node<int> NodeInt;

int main(int argc, const char *argv[]) {
    NodeInt *head(new NodeInt(0));

    NodeInt *rmd = head->linkTo(new NodeInt(1))->
        linkTo(new NodeInt(2));

    rmd->linkTo(new NodeInt(3))->
        linkTo(new NodeInt(4));

    Node<int>::print(head);

    Node<int>::removeNode(rmd);

    Node<int>::print(head);

    return 0;
}
