#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <map>
#include <string>

//class MultiMap {
//	List** a;
//	size_t size;
//
//	size_t h(string s) {
//		size_t res = 0;
//		for (int i = 0; i < s.size(); ++i)
//			res += s[i] * s[i];
//		return res % size;
//	}
//public:
//	MultiMap(size_t size) {
//		a = new List * [size];
//		for (int i = 0; i < size; ++i)
//			a[i] = NULL;
//		this->size = size;
//	}
//
//	void insert(string key, string value) {
//		size_t hash = h(key);
//		List* cur = a[hash];
//		List* temp = cur;
//		if (!cur) {
//			a[hash] = new List(key, value, 0);
//			return;
//		}
//		else if (cur->key == key && cur->value == value) {
//			return;
//		}
//
//		while (cur->next != NULL) {
//			if (cur->next->key == key && cur->next->value == value) {
//				return;
//			}
//
//			cur = cur->next;
//		}
//
//		cur->next = new List(key, value, 0);
//		a[hash] = temp;
//	}
//
//	void get(string key, ofstream& fout) {
//		size_t hash = h(key);
//		List* cur = a[hash];
//		vector<string> values;
//		while (cur != NULL) {
//			if (cur->key == key)
//				values.push_back(cur->value);
//
//			cur = cur->next;
//		}
//		fout << values.size() << " ";
//		for (auto x : values)
//			fout << x << " ";
//		fout << '\n';
//	}
//	void delete_el(string key, string value) {
//		size_t hash = h(key);
//		List* cur = a[hash];
//		List* temp = cur;
//
//		if (!cur)
//			return;
//		else if (cur->key == key && cur->value == value) {
//			a[hash] = cur->next;
//			delete cur;
//			return;
//		}
//		else {
//			while (cur->next != NULL) {
//				if (cur->next->key == key && cur->next->value == value) {
//					List* successor_of_delet = cur->next->next;
//					delete cur->next;
//					cur->next = successor_of_delet;
//					return;
//				}
//				cur = cur->next;
//			}
//		}
//		a[hash] = temp;
//	}
//	void delete_all(string key) {
//		size_t hash = h(key);
//
//		List* cur = a[hash];
//		if (!cur)
//			return;
//		while (cur != NULL && cur->key == key) {
//			List* temporary = cur->next;
//			delete cur;
//			cur = temporary;
//		}		
//		if (!cur) {
//			a[hash] = NULL;
//			return;
//		}
//
//		List* tempHead = cur;
//		while (cur->next != NULL) {
//			List* temporary = cur->next->next;
//			delete cur->next;
//
//			cur->next = temporary;
//
//			cur = cur->next;
//		}
//		a[hash] = tempHead;
//	}
//};

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

class Set {
	List** a;
	size_t size;
	size_t amount;

	size_t h(string s) {
		size_t res = 0;
		for (int i = 0; i < s.size(); ++i)
			res += (i + 1) * s[i];
		return res % size;
	}
public:
	Set() {
		this->amount = 0;
		this->size = 1000;
		a = new List*[size];
		for (int i = 0; i < size; ++i)
			a[i] = NULL;
	}
	Set(size_t size) {
		this->amount = 0;
		a = new List* [size];
		for (int i = 0; i < size; ++i)
			a[i] = NULL;
		this->size = size;
	}

	void insert(string key, string value) {
		int hash = h(key);
		List* cur = a[hash];
		List* temp = cur;
		if (!cur) {
			++amount;
			a[hash] = new List(key, value, 0);
			return;
		}

		else if (cur->value == value && cur->key == key)
			return;
		while (cur->next != NULL) {
			if (cur->next->value == value && cur->next->key == key)
				return;
			cur = cur->next;
		}
		cur->next = new List(key, value, 0);
		a[hash] = temp;
		++amount;
	}

	void delete_el(string key, string value) {
		int hash = h(key);
		List* cur = a[hash];
		List* temp = cur;

		if (!cur)
			return;
		else if (cur->value == value && cur->key == key) {
			a[hash] = cur->next;
			delete cur;
			return;
		}
		else {
			while (cur->next != NULL) {
				if (cur->next->value == value && cur->next->key == key) {
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
	void get(string key, ofstream& fout) {
		size_t hash = h(key);
		List* cur = a[hash];
		vector<string> counter;
		while (cur != NULL) {
			if (cur->key == key) {
				counter.push_back(cur->value);
			}

			cur = cur->next;
		}
		//if (counter.size() == 2) {
		//	cout << "HERE IS PROB!\n";
		//}
		fout << counter.size() << ' ';
		for (auto x : counter)
			fout << x << ' ';
		fout << '\n';
	}
	void delete_all(string key) {
		size_t hash = h(key);
		
		List* cur = a[hash];
		if (!cur)
			return;
		while (cur != NULL && cur->key == key) {
			List* temporary = cur->next;
			delete cur;
			cur = temporary;
		}		
		if (!cur) {
			a[hash] = NULL;
			return;
		}
		
		List* tempHead = cur;
		while (cur->next != NULL) {
			List* temporary = cur->next->next;
			delete cur->next;
		
			cur->next = temporary;
		
			cur = cur->next;
		}
		a[hash] = tempHead;
	}
};
 
class MultiMap {
	Set* a;
	size_t size;

	size_t h(string s) {
		size_t res = 0;
		for (int i = 0; i < s.size(); ++i)
			res += (i + 1) * s[i];
		return res % size;
	}
public:
	MultiMap(size_t size) {
		a = new Set[size];
		for (int i = 0; i < size; ++i)
			a[i] = Set();
		this->size = size;
	}

	void insert(string key, string value) {
		size_t hash = h(key);
		a[hash].insert(key, value);
	}

	void get(string key, ofstream& fout) {
		size_t hash = h(key);
		a[hash].get(key, fout);
	}
	void delete_key(string key, string value) {
		size_t hash = h(key);
		a[hash].delete_el(key, value);
	}
	void delete_all(string key) {
		size_t hash = h(key);
		a[hash].delete_all(key);
	}
};


int main() {
	ifstream fin("multimap.in");
	ofstream fout("multimap.out");
	ofstream out("sample_result.out");

	MultiMap m(1000);
	int num = 1;
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
			//if (arg1 == "accd") {
			//	cout << "PROBLEM!\n";
			//}
			m.get(arg1, fout);
		}
		else if (str == "delete") {
			string arg2;
			fin >> arg2;
			m.delete_key(arg1, arg2);
		}
		else if (str == "deleteall") {
			m.delete_all(arg1);
		}
		++num;
		//if (num % 1000 == 0)
		//	cout << (double)num / 100000 * 100 << "%" << endl;
		//if (num == 152) {
		//	cout << "There is some problems!";
		//}
	}

	return 0;
}