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

int main(int argc, const char * argv[]) {
    const int BuffSize = 8;

    int buffer[BuffSize];
    SimpleStack<int> stack(buffer, BuffSize);

    const int BuffByteSize = BuffSize * sizeof(int);
    char buffer2[BuffByteSize];;
    ListStack<int>::StackNode *b2 = 0;
    b2 = ListStack<int>::initBuffer(buffer2, BuffByteSize);
    ListStack<int> stack2(&b2);

    std::list<Stack<int>*> stacks;
    stacks.push_back(&stack);
    stacks.push_back(&stack2);

    std::list<Stack<int>*>::iterator it = stacks.begin();

    for (; stacks.end() != it; ++it) {
        Stack<int> *s = *it;

        s->push(1);
        s->push(2);

        while (0 != s->size()){
            printf("Pop: %d\n", s->pop());
        }
    }

    return 0;
}
