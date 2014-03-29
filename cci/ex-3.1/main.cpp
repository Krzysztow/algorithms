#include <stdio.h>
#include <list>

template <class T>
class Stack {
    public:
        virtual bool push(const T &item) = 0;
        //the safest thing is to not return reference, only copy
        virtual const T pop() = 0;

        virtual int size() = 0;
};

/**
 * Simple stack implementation assuming it's provided with static
 * buffer and its length. Guaranteed to be able to store that size of
 * elements. Access is O(n), no additional memory footprint.
 */

template <class T>
class SimpleStack:
    public Stack<T> {
public:
    SimpleStack(T buffer[], int size):
        _buffer(buffer),
        _size(size),
        _last(-1)
        {}

    virtual bool push(const T &item) {
        if (_last < _size - 1) {//we still have space
            _buffer[++_last] = item;
            //if there is no constructor for the class, we could use
            //memcpy(&_buffer[_last++], &item, sizeof(T));
            return true;
        }
        return false;
    }

    virtual const T pop() {
        if (-1 != _last) {//we still have data
            return _buffer[_last--];
        }

        return _defaultItem;
    }

    virtual int size() {
        return (1 + _last);
    }

    static void setDefaultValue(const T &defValue) {
        _defaultItem = defValue;
    }

private:
    T *_buffer;
    int _size;
    int _last;

    static T _defaultItem;
};

template <class T>
T SimpleStack<T>::_defaultItem;

/**
 * Linked list implementation that divides entire array to the StackNode elements.
 * Firstly they belong to the free list nodes. The pointer to such linked list is pointed
 * to all LinkedStack constructors.
 */
template <class T>
class ListStack:
    public Stack<T>
{
    public:
        struct StackNode {
            T data;
            StackNode *next;
    };

    static StackNode *initBuffer(char buffer[], int size) {
        const int NodesNo = size / sizeof(StackNode);

        StackNode *head = (StackNode*)buffer;
        StackNode *node = head;
        for (int i = 0; i < NodesNo - 1; ++i) {
            node->next = (node + 1);
            node = node->next;
        }

        node->next = 0;

        return head;
    }

    public:
        ListStack(StackNode **freePtr):
            _freeListPtr(freePtr),
            _size(0),
            _head(0)
        {}

        virtual bool push(const T &node) {
            StackNode *n = _takeBufferNode();
            if (0 != n) {
                n->data = node;//this uses copy constrctor
                //memcpy(&(n->data), &node, sizeof(T));//alternatively
                n->next = _head;
                _head = n;
                ++_size;
                return true;
            }
            else
                return false;
        }

        virtual const T pop() {
            //since _recycle* doesn't change the data, we may not copy the content
            //otherwise it would be necessary
            if (0 != _head) {
                StackNode *n = _head;
                _head = _head->next;
                _recycleBufferNode(n);
                --_size;
                return n->data;
            }
            else
                return _defaultData;
        }

        virtual int size() {
            return _size;
        }

    private:
        StackNode *_takeBufferNode() {
            if (0 == *_freeListPtr) {//no more free nodes
                return 0;
            }
            StackNode *node = *_freeListPtr;
            *_freeListPtr = node->next;

            return node;
        }

        void _recycleBufferNode(StackNode *node) {
            node->next = *_freeListPtr;
            *_freeListPtr = node;
        }

    private:
        StackNode **_freeListPtr;
        int _size;
        static T _defaultData;

        StackNode *_head;
};

template <class T>
T ListStack<T>::_defaultData;

template <class T, int C = 5>
class BlockStack:
    public Stack<T> {
    public:
        struct StackPage {
            T data[C];
            StackPage *next;
        };

    static StackPage *initBuffer(char data[], int size) {
        int no = size / sizeof(StackPage);
        StackPage *head = (StackPage*)data;
        StackPage *page = head;
        for (int i = 0; i < no - 1; ++i) {
            page->next = (page + 1);
            page = page->next;
        }

        page->next = 0;

        return head;
    }

    public:
        BlockStack(StackPage **freeList):
            _freeListPtr(freeList),
            _size(0),
            _head(0) {}

        virtual bool push(const T &node) {
            StackPage *p = _getPageWNextNode(_size);
            if (0 == p) {
                return false;
            }
            const int pIdx = _inPageIdx(_size);
            p->data[pIdx] = node;
            //alternatively memcpy(&(p->data[pIdx]), &node, sizeof(T));
            if (p != _head) {//this could be moved to _getPageWNextNode()
                p->next = _head;
                _head = p;
            }
            ++_size;
            return true;
        }

        virtual const T pop() {
            if (0 == _size)
                return _defaultData;

            const int pIdx = _inPageIdx(_size - 1);
            T value = _head->data[pIdx];
            if (0 == pIdx) {
                StackPage *next = _head->next;
                _returnPage(_head);
                _head = next;
            }
            --_size;
            return value;
        }

        virtual int size() {
            return _size;
        }

    private:
        StackPage *_getPageWNextNode(int nodeIdx) {
            int inPageIdx = _inPageIdx(nodeIdx);
            StackPage *p = 0;
            if (0 == inPageIdx) {//we require next page
                if (0 == *_freeListPtr) {
                    return 0;
                }
                p = *_freeListPtr;
                *_freeListPtr = (*_freeListPtr)->next;
            }
            else {
                p = _head;
            }

            return p;
        }

        void _returnPage(StackPage *p) {
            p->next = *_freeListPtr;
            *_freeListPtr = p;
        }

        int _pageIndex(int globalIdx) {
            return globalIdx / C;
        }

        int _inPageIdx(int globalIdx) {
            return globalIdx % C;
        }

    private:
        StackPage **_freeListPtr;
        int _size;

        StackPage *_head;
        static T _defaultData;
};

template<class T, int C>
T BlockStack<T, C>::_defaultData;

void pushNewData(Stack<int> *stack, int data) {
    if (! stack->push(data)) {
        fprintf(stderr, "Cannot add data %d\n", data);
    }
}

int main(int argc, const char * argv[]) {
    const int BuffSize = 16;

    int buffer[BuffSize];
    SimpleStack<int> stack(buffer, BuffSize);

    const int BuffByteSize = BuffSize * sizeof(int);
    char buffer2[BuffByteSize];;
    ListStack<int>::StackNode *b2 = 0;
    b2 = ListStack<int>::initBuffer(buffer2, BuffByteSize);
    ListStack<int> stack2(&b2);

    char buffer3[BuffByteSize];
    BlockStack<int, 2>::StackPage *b3 = BlockStack<int, 2>::initBuffer(buffer3, BuffByteSize);
    BlockStack<int, 2> stack3(&b3);

    std::list<Stack<int>*> stacks;
    stacks.push_back(&stack);
    stacks.push_back(&stack2);
    stacks.push_back(&stack3);

    std::list<Stack<int>*>::iterator it = stacks.begin();

    for (; stacks.end() != it; ++it) {
        printf("-------------------------------------\n");

        Stack<int> *s = *it;

        for (int i = 0; i < 10; ++i) {
            pushNewData(s, i);
        }

        while (0 != s->size()){
            printf("Pop: %d\n", s->pop());
        }
    }

    return 0;
}
