#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int INF = 1e9;

class PQueue { // организуем на мин-куче
	vector<pair<int, int>> a; // пара: номер и элемент
	void SiftUp(int index) {
		if (index == 1)
			return;
		if (a[index / 2].second > a[index].second) { // если родитель больше ребенка => куча сломана
			swap(a[index / 2], a[index]);
			SiftUp(index / 2);
		}
	}
	void SiftDown(int index) {
		int size = a.size() - 1;
		int curEl = a[index].second;
		if (2 * index > size) {
			return;
		}
		else if (2 * index+ 1 > size) {
			if (a[index].second > a[2 * index].second) {
				swap(a[index], a[2 * index]);
			}
			return;
		}
		int left = a[2 * index].second, right = a[2 * index + 1].second;
		if (curEl > min(left, right)) {
			if (curEl > left && curEl > right) {
				if (left < right) {
					swap(a[index], a[2 * index]);
					SiftDown(2 * index);
				}
				else {
					swap(a[index], a[2 * index + 1]);
					SiftDown(2 * index + 1);
				}
			}
			else if (curEl > right) {
				swap(a[index], a[2 * index + 1]);
				SiftDown(2 * index + 1);
			}
			else {
				swap(a[index], a[2 * index]);
				SiftDown(2 * index);
			}
		}
	}
	int getIndex(int num) {
		for (int i = 1; i < a.size(); ++i) {
			if (a[i].first == num)
				return i;
		}
		return -1;
	}
public:
	PQueue() {
		a.resize(1);
	}
	void push(pair<int,int> x) { // номер, число
		a.push_back(x);
		SiftUp(a.size() - 1);
	}
	void print() {
		for (int i = 1; i < a.size(); ++i) {
			cout << a[i].second << " ";
		}
		cout << endl;
	}
	void decrease_key(int num, int new_value) {
		int index = getIndex(num);
		if (index == -1) {
			cerr << "ERROR!!!";
			return;
		}
		a[index].second = new_value;
		SiftUp(index);
	}
	int extract_min() {
		if (a.size() == 2) {
			int res = a[1].second;
			a.pop_back();
			return res;
		}
		pair<int,int> tmp = a[1];
		swap(a[1], a[a.size() - 1]);
		a.pop_back();
		SiftDown(1);
		return tmp.second;
	}
	PQueue(vector<int> const& a) {
		this->a.resize(1);
		int cnt = 1;
		for (auto x : a) {
			this->push({x, cnt});
			cnt++;
		}
	}
	size_t const size() {
		return a.size();
	}
};

int main() {

	ifstream fin("priorityqueue.in");
	ofstream fout("priorityqueue.out");
	PQueue q;
	string s;
	int cnt = 1;
	while (fin >> s) {
		if (s.find("push") != string::npos) {
			int x;
			fin >> x;
			q.push({cnt, x});
		}
		else if (s.find("extract-min") != string::npos) {
			if (q.size() == 1) {
				fout << '*' << endl;
				++cnt;
				continue;
			}
			int x = q.extract_min();
			fout << x << endl;
		}
		else { // decrease-key
			int num, new_value;
			fin >> num >> new_value;
			q.decrease_key(num, new_value);
		}
		++cnt;
	}
	return 0;
}