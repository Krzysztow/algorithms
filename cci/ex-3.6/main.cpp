#include <iostream>
#include <stack>

//note: fron is peek
//isEmpty is 0 != q.size()
void sort(std::stack<int> &q) {
    std::stack<int> res;

    while (0 != q.size()) {
        int v = q.top();
        q.pop();

        //we try to keep head of the res as the smallest element
        //them, when eventually copied to q, q head will be the largest

        int cnt = 0;
        while (0 != res.size() &&
                res.top() < v) {
            q.push(res.top());
            res.pop();
            ++cnt;
        }

        res.push(v);
        for (; cnt > 0; --cnt) {
            res.push(q.top());
            q.pop();
        }
    }

    //the sorted (in reverse order) elements are in res
    //by pushing them to q, ew reverse order
    while (0 != res.size()) {
        q.push(res.top());
        res.pop();
    }
}

void print(std::stack<int> &q) {
    std::stack<int> temp;

    while (0 != q.size()) {
        std::cout << " -> " << q.top();
        temp.push(q.top());
        q.pop();
    }

    q = temp;
}

int main(int argc, const char *argv[]) {
    std::stack<int> q;

    q.push(0);
    q.push(2);
    q.push(3);
    q.push(1);

    std::cout << "Before: ";
    print(q);

    sort(q);

    std::cout << std::endl << "After :";
    print(q);

    return 0;
}
