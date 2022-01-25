#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct List {
    uint16_t value;
    List* next;

    List(uint16_t x, List* next) {
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

    void push(uint16_t x) {
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

    uint16_t get() {
        if (size <= 0) {
            cerr << "ERROR!";
        }
        uint16_t res = begin->value;
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

    void print() {
        List* begin = this->begin;
        while (begin != NULL) {
            cout << begin->value << " ";
            begin = begin->next;
        }
        cout << endl;
    }
};

int main() {
    ifstream fin("quack.in");
    ofstream fout("quack.out");
    if (!fin) {
        cerr << "ERROR!";
        return -1;
    }

    vector<string> commands;
    map<string, int> labels_number;
    string cur_command;
    int counter = 0;

    while (fin >> cur_command) {
        commands.push_back(cur_command);
        if (cur_command[0] == ':') {
            labels_number[cur_command.substr(1, cur_command.size() - 1)] = counter;
        }
        ++counter;
    }
    int prog_size = commands.size();

    Queue q;
    vector<uint16_t> registers(26, 0);
    int cc = 0; // command counter

    cur_command = commands[cc];
    while (cc < prog_size && cur_command != "Q") {
        cur_command = commands[cc];
        bool normal_commands_order = true;

        if (cur_command[0] == '+') {
            uint16_t x = q.get();
            uint16_t y = q.get();
            q.push(x + y);
        }
        else if (cur_command[0] == '-') {
            uint16_t x = q.get();
            uint16_t y = q.get();
            q.push(x - y);
        }
        else if (cur_command[0] == '*') {
            uint16_t x = q.get();
            uint16_t y = q.get();
            q.push(x * y);
        }
        else if (cur_command[0] == '/') {
            uint16_t x = q.get();
            uint16_t y = q.get();
            if (y == 0)
                q.push(0);
            else
                q.push(x / y);
        }
        else if (cur_command[0] == '%') {
            uint16_t x = q.get();
            uint16_t y = q.get();
            if (y == 0)
                q.push(0);
            else
                q.push(x % y);
        }
        else if (cur_command[0] == '>') {
            uint16_t value = q.get();
            registers[cur_command[1] - 'a'] = value;
        }
        else if (cur_command[0] == '<') {
            uint16_t value = registers[cur_command[1] - 'a'];
            q.push(value);
        }
        else if (cur_command[0] == 'P') {
            if (cur_command.size() == 1) { // P
                uint16_t value = q.get();
                fout << value << '\n';
            }
            else { // P[register]
                fout << registers[cur_command[1] - 'a'] << '\n';
            }
        }
        else if (cur_command[0] == 'C') {
            if (cur_command.size() == 1) { // P
                uint16_t value = q.get();
                fout << (char)(value % 256);
            }
            else { // P[register]
                fout << (char)(registers[cur_command[1] - 'a'] % 256);
            }
        }
        else if (cur_command[0] == 'J') {
            string label = cur_command.substr(1, cur_command.size() - 1);
            cc = labels_number[label];
            normal_commands_order = false;
        }
        else if (cur_command[0] == 'Z') {
            char cur_register = cur_command[1];
            string label = cur_command.substr(2, cur_command.size() - 2);
            if (registers[cur_register - 'a'] == 0) {
                cc = labels_number[label];
                normal_commands_order = false;
            }
        }
        else if (cur_command[0] == 'E') {
            char first_register = cur_command[1];
            char second_register = cur_command[2];

            string label = cur_command.substr(3, cur_command.size() - 3);
            if (registers[first_register - 'a'] == registers[second_register - 'a']) {
                cc = labels_number[label];
                normal_commands_order = false;
            }
        }
        else if (cur_command[0] == 'G') {
            char first_register = cur_command[1];
            char second_register = cur_command[2];

            string label = cur_command.substr(3, cur_command.size() - 3);
            if (registers[first_register - 'a'] > registers[second_register - 'a']) {
                cc = labels_number[label];
                normal_commands_order = false;
            }
        }
        else if (cur_command[0] == 'Q') {
            break;
        }
        else if (cur_command[0] >= '0' && cur_command[0] <= '9') {
            uint16_t value = stoi(cur_command);
            q.push(value);
        }

        if (normal_commands_order)
            ++cc;
    }

	return 0;
}