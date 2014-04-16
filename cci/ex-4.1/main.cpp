#include <assert.h>
#include "tree.h"

typedef BSTreeNode<int> IntBsNode;

template <class T>
void findExtremeDepths(BSTreeNode<T> *node, int currDepth, int *max, int *min) {
    assert(0 != max);
    assert(0 != min);

    if (0 != node->left)
        findExtremeDepths(node->left, currDepth + 1, max, min);
    if (0 != node->right)
        findExtremeDepths(node->right, currDepth + 1, max, min);

    if (0 == node->right && 0 == node->left) { //leaf node
        if (-1 == *max)
            *max = currDepth;
        else if (*max < currDepth)
            *max = currDepth;

        if (-1 == *min)
            *min = currDepth;
        else if (*min > currDepth)
            *min = currDepth;
    }
}

template <class T>
bool checkTreeBalance(BSTreeNode<T> *root) {
    int max = -1;
    int min = -1;

    findExtremeDepths<T>(root, 0, &max, &min);
    std::cout << "Depths: max: " << max << ", min: " << min << std::endl;
    return (max - min <= 1);
}

int main(int argc, const char *argv[]) {

    IntBsNode root(4);
    root.add(new IntBsNode(2));
    root.add(new IntBsNode(6));
    root.add(new IntBsNode(1));
    root.add(new IntBsNode(3));
    root.add(new IntBsNode(5));
    root.add(new IntBsNode(7));
    root.add(new IntBsNode(8));
    root.add(new IntBsNode(3));
    root.add(new IntBsNode(9));

    IndentTreePrinter printer(3);

    root.print(&printer);

    std::cout << "The tree is balanced " << checkTreeBalance(&root) << std::endl;

    return 0;
}
