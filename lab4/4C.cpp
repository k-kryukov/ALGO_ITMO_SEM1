#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

enum {
    opening,
    closing
};

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
        begin = 0, size = 0;
    }
    size_t const get_size() {
        return size;
    }
    bool const empty() {
        return (size == 0);
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
    void free() {
        while (begin != NULL) {
            List* temp = begin->next;
            delete begin;
            begin = temp;
        }
        size = 0;
    }
};

int brackets_type(char c) {
    if (c == '(' || c == '[')
        return opening;
    else
        return closing;
}

bool check_brackets_pair(pair<char, char> brackets) {
    if (brackets.first == '(' && brackets.second == ')')
        return true;
    else if (brackets.first == '[' && brackets.second == ']')
        return true;
    else
        return false;
}

int main() {
    ifstream fin("brackets.in");
    ofstream fout("brackets.out");
    if (!fin) {
        cerr << "ERROR!";
        return -1;
    }

    Stack s;
    string str;
    bool good_brackets_flag = true;

    while (fin >> str) {
        for (auto c : str) {
            if (brackets_type(c) == opening) {
                s.push(c);
            }
            else {
                if (s.get_size() == 0) {
                    good_brackets_flag = false;
                    break;
                }
                else {
                    char cur_sym = s.extract();
                    if (!check_brackets_pair({cur_sym, c})) {
                        good_brackets_flag = false;
                        break;
                    }
                }
            }
        }
        if (good_brackets_flag && s.empty()) {
            fout << "YES\n";
        }
        else {
            fout << "NO\n";
        }
        s.free();
        good_brackets_flag = true;
    }

    return 0;
}