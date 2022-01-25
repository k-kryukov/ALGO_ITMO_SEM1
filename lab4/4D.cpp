#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct List {
    string value;
    List* next;

    List(string x, List* next) {
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
    void push(string x) {
        if (!size) {
            begin = new List(x, 0);
        }
        else {
            List* temp = new List(x, begin);
            begin = temp;
        }
        ++size;
    }
    string extract() {
        string res = begin->value;
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

bool is_num(string c) {
    return (c[0] >= '0' && c[0] <= '9');
}

int calculate(string a, string op, string b) {
    if (op == "+") {
        return (stoi(a) + stoi(b));
    }
    else if (op == "-") {
        return (stoi(a) - stoi(b));
    }
    else
        return stoi(a) * stoi(b);
}

string itos(int x) {
    if (x == 0)
        return "0";
    string s = "";
    bool negative = (x < 0);
    if (x < 0)
        x = -x;
    while (x > 0) {
        s += (x % 10 + '0');
        x /= 10;
    }
    if (negative)
        s += '-';
    reverse(s.begin(), s.end());

    return s;
}

int main() {
    ifstream fin("postfix.in");
    ofstream fout("postfix.out");
    if (!fin) {
        cerr << "ERROR!";
        return -1;
    }

    Stack staque;
    string s;

    while (fin >> s) {
        if (is_num(s)) {
            staque.push(s);
        }
        else {
            string operand1 = staque.extract();
            string operand2 = staque.extract();
            staque.push(itos(calculate(operand2, s, operand1)));
        }
    }
    fout << stoi(staque.extract());
    return 0;
}