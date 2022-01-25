#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct List {
	int value;
	List* next;

	List(int value, List* next) {
		this->value = value;
		this->next = next;
	}
};

class Set {
	List** a;
	size_t size;

	size_t h(size_t index) {
		return index % size;
	}

public:
	Set(size_t size) {
		a = new List*[size];
		for (int i = 0; i < size; ++i)
			a[i] = NULL;

		this->size = size;
	}

	void insert(int key) {
		int hash = h(abs(key));
		List* cur = a[hash];
		List* temp = cur;

		if (!cur) {
			a[hash] = new List(key, 0);
			return;
		}
		else if (cur->value != key) {
			while (cur->next != NULL) {
				if (cur->next->value == key)
					return;

				cur = cur->next;
			}

			cur->next = new List(key, 0);
			a[hash] = temp;
		}
		else
			return;
	}

	bool exists(int key) {
		int hash = h(abs(key));
		List* cur = a[hash];

		while (cur != NULL) {
			if (cur->value == key)
				return true;
			cur = cur->next;
		}

		return false;
	}

	void delete_key(int key) {
		int hash = h(abs(key));
		List* cur = a[hash];
		List* temp = cur;

		if (!cur)
			return;
		else if (cur->value == key) {
			a[hash] = cur->next;
			delete cur;
			return;
		}
		else {
			while (cur->next != NULL) {
				if (cur->next->value == key) {
					List* successor_of_delet = cur->next->next;
					delete cur->next;
					cur->next = successor_of_delet;
					return;
				}

				cur = cur->next;
			}
		}

		a[hash] = temp;
	}
};

int main() {
	ifstream fin("set.in");
	ofstream fout("set.out");
	if (!fin) {
		cerr << "ERROR!";
		return -1;
	}

	Set s(10000);
	string str;

	while (fin >> str) {
		int x;
		fin >> x;

		if (str == "insert") {
			s.insert(x);
		}
		else if (str == "exists") {
			fout << (s.exists(x) ? "true\n" : "false\n");
		}
		else if (str == "delete") {
			s.delete_key(x);
		}
	}

	return 0;
}