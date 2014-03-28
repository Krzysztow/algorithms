#include <stdio.h>

template <class T>
class Stack {
    public:
        virtual bool push(const T &item) = 0;
        //the safest thing is to not return reference, only copy
        virtual const T pop() = 0;

        virtual int size() = 0;
};

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

int main(int argc, const char * argv[]) {
    const int BuffSize = 8;
    int buffer[BuffSize];
    SimpleStack<int> stack(buffer, BuffSize);

    stack.push(1);
    stack.push(2);


    while (0 != stack.size()){
        printf("Pop: %d\n", stack.pop());
    }

    return 0;
}
