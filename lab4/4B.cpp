#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>

using namespace std;

struct List {
    int value;
    List* next;

    List(int x, List* next) {
        this->value = x;
        this->next = next;
    }
};

class Queue {
    List* begin;
    List* last;
    size_t size;
public:
    Queue() {
        begin = 0;
        last = 0;
        size = 0;
    }
    void push(int x) {
        List* temp = new List(x, 0);
        if (!size) {
            begin = temp;
            last = temp;
        }
        else if (size == 1) {
            last = temp;
            begin->next = last;
        }
        else {
            last->next = temp;
            last = temp;
        }
        ++size;
    }
    int extract() {
        if (size <= 0) {
            cerr << "ERROR!";
        }
        int res = begin->value;
        if (size == 1) {
            delete begin;
            begin = 0;
            last = 0;
        }
        else {
            List* temp = begin->next;
            delete begin;
            begin = temp;
        }
        --size;
        return res;
    }
};

int main() {
    ifstream fin("queue.in");
    ofstream fout("queue.out");
    if (!fin) {
        cerr << "Error!";
        return -1;
    }

    int n;
    Queue q;

    fin >> n;
    for (int i = 0; i < n; ++i) {
        char c;
        fin >> c;
        if (c == '+') {
            int x;
            fin >> x;
            q.push(x);
        }
        else {
            fout << q.extract() << '\n';
        }
    }

    return 0;
}