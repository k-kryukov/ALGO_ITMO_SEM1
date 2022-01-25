#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void Heapify(vector<int> &a, int i, int size) { // siftDown
	int curEl = a[i];
	if (2 * i > size) { // нет детей
		return;
	}
	else if (2 * i + 1 > size) { // единственный ребенок
		if (a[i] < a[2 * i]) {
			swap(a[i], a[2 * i]);
		}
		return;
	}
	int left = a[2 * i], right = a[2 * i + 1];
	if (curEl < max(left, right)) { // есть смысл что-то менять
		if (curEl < left && curEl < right) { // проблема с обеих сторон
			if (left > right) { // левый больше => меняем с ним
				swap(a[i], a[2 * i]);
				Heapify(a, 2 * i, size);
			}
			else {
				swap(a[i], a[2 * i + 1]);
				Heapify(a, 2 * i + 1, size);
			}
		}
		else if (curEl < right) { // проблема только справа
			swap(a[i], a[2 * i + 1]);
			Heapify(a, 2 * i + 1, size);
		}
		else { // проблема только слева
			swap(a[i], a[2 * i]);
			Heapify(a, 2 * i, size);
		}
	}
}

void BuildHeap(vector<int> &a, int n) { // последний индекс = n
	for (int i = n / 2; i >= 1; --i) {
		Heapify(a, i, n);
	}
}

void HeapSort(vector<int>& a, int n) {
	vector<int> res(n + 1);
	int last = n;
	BuildHeap(a, n);
	for (int i = 1; i < n; ++i) {
		swap(a[1], a[last]);
		res[last] = a[last];
		last--;
		Heapify(a, 1, last);
	}
	for (int i = 2; i <= n; ++i)
		a[i] = res[i];
	a.clear();
}

int main() {
	ifstream fin("sort.in");
	ofstream fout("sort.out");
	int n;
	fin >> n;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++)
		fin >> a[i];
	HeapSort(a, n);
	for (int i = 1; i <= n; i++)
		fout << a[i] << " " << (i == n ? "\n" : "");
	a.clear();
	fin.close();
	fout.close();
	return 0;
}