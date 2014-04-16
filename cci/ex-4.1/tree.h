#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include <sstream>

class TreePrinter {
    public:
        virtual void increaseDepth() = 0;
        virtual void decreaseDepth() = 0;

        virtual void print(const std::string &nodeString) = 0;
};

class IndentTreePrinter:
    public TreePrinter {
    public:
        IndentTreePrinter(int indentSize):
            _currentIndent(0),
            _indentSize(indentSize) {}

        virtual void increaseDepth() {
            ++_currentIndent;
            _indentStr.append(std::string(_indentSize, ' '));
        }

        virtual void decreaseDepth() {
            --_currentIndent;
            if (_currentIndent >= 0) {
                _indentStr.erase(_indentSize * _currentIndent, _indentSize * (_currentIndent + 2) );
            }
        }

        virtual void print(const std::string &nodeString) {
            std::cout << _indentStr << nodeString << std::endl;
        }

    private:
        int _currentIndent;
        int _indentSize;
        std::string _indentStr;
};

template <class T>
class BSTreeNode {
    public:
    BSTreeNode *parent;
    BSTreeNode *left;
    BSTreeNode *right;

    T data;

    public:
        BSTreeNode(T data);
        void add(BSTreeNode *node);
        void print(TreePrinter *printer);
};

template <class T>
BSTreeNode<T>::BSTreeNode(T data):
    parent(0),
    left(0),
    right(0),
    data(data) {}

template <class T>
void BSTreeNode<T>::add(BSTreeNode<T> *node) {
    if (node->data < data) {
        if (0 == left) {
            left = node;
            node->parent = this;
        }
        else {
            left->add(node);
        }
    }
    else {
        if (0 == right) {
            right = node;
            node->parent = this;
        }
        else
            right->add(node);
    }
}

template <class T>
void BSTreeNode<T>::print(TreePrinter *printer) {
    printer->increaseDepth();
    if (0 != left)
        left->print(printer);
    std::stringstream st;
    st << data;
    printer->print(st.str());
    if (0 != right)
        right->print(printer);
    printer->decreaseDepth();
}


#endif //TREE_H
