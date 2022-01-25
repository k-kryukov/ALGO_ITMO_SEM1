#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct List {
    int value;
    List* next;

    List(int x, List* next) {
        this->value = x;
        this->next = next;
    }
};

class Stack {
    List* begin;
    size_t size;
public:
    Stack() {
        begin = 0;
        size = 0;
    }
    void push(int x) {
        if (!size) {
            begin = new List(x, 0);
        }
        else {
            List* temp = new List(x, begin);
            begin = temp;
        }
        ++size;
    }
    int extract() {
        int res = begin->value;
        if (size == 1) {
            delete begin;
            begin = 0;
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
    ifstream fin("stack.in");
    ofstream fout("stack.out");
    int n;
    Stack s;

    fin >> n;
    for (int i = 0; i < n; ++i) {
        char c;
        fin >> c;
        if (c == '+') {
            int x;
            fin >> x;
            s.push(x);
        }
        else {
            fout << s.extract() << '\n';
        }
    }

    return 0;
}