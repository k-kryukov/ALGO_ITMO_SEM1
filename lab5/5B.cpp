#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <map>
#include <string>

using namespace std;

struct List {
	string key;
	string value;
	List* next;

	List(string key, string value, List* next) {
		this->key = key;
		this->value = value;
		this->next = next;
	}
};

class Map {
	List** a;
	size_t size;

	size_t h(string s) {
		size_t res = 0;
		for (int i = 0; i < s.size(); ++i)
			res += (i + 1) * s[i];

		return res % size;
	}

public:
	Map(size_t size) {
		a = new List* [size];
		for (int i = 0; i < size; ++i)
			a[i] = NULL;

		this->size = size;
	}

	void insert(string key, string value) {
		size_t hash = h(key);
		List* cur = a[hash];
		List* temp = cur;

		if (!cur) {
			a[hash] = new List(key, value, 0);
			return;
		}
		else if (cur->key == key) {
			cur->value = value;
			return;
		}

		while (cur->next != NULL) {
			if (cur->next->key == key) {
				cur->next->value = value;
				return;
			}
			cur = cur->next;
		}

		cur->next = new List(key, value, 0);
		a[hash] = temp;
	}

	string get(string key) {
		size_t hash = h(key);
		List* cur = a[hash];

		while (cur != NULL) {
			if (cur->key == key)
				return cur->value;
			cur = cur->next;
		}

		return "";
	}
	void delete_key(string key) {
		size_t hash = h(key);
		List* cur = a[hash];
		List* temp = cur;

		if (!cur)
			return;
		else if (cur->key == key) {
			a[hash] = cur->next;
			delete cur;
			return;
		}
		else {
			while (cur->next != NULL) {
				if (cur->next->key == key) {
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
	ifstream fin("map.in");
	ofstream fout("map.out");
	ofstream out("sample_result.out");
	if (!fin) {
		cerr << "ERROR!";
		return -1;
	}

	Map m(1000);
	string str;

	while (fin >> str) {
		string arg1;
		fin >> arg1;

		if (str == "put") {
			string arg2;
			fin >> arg2;
			m.insert(arg1, arg2);
		}
		else if (str == "get") {
			string res = m.get(arg1);
			if (res == "")
				res = "none";
			fout << res << '\n';
		}
		else if (str == "delete") {
			m.delete_key(arg1);
		}
	}

	return 0;
}