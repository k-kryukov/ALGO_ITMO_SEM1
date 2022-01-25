#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int min_index_of_element(vector<int> const& a, int key) {
	int r = a.size(); // [0, n)
	int l = 0;

	while (r - l > 2) {
		int m = (r + l) / 2;
		if (key > a[m]) {
			l = m;
		}
		else {
			r = m + 1;
		}
	}
	if (a[l] == key)
		return l;
	else if (a[r - 1] == key)
		return r - 1;
	else
		return -1;
}

int max_index_of_element(vector<int> const& a, int key) {
	int r = a.size(); // [0, n)
	int l = 0;

	while (r - l > 2) {
		int m = (r + l) / 2;
		if (key >= a[m]) {
			l = m;
		}
		else {
			r = m + 1;
		}
	}
	if (a[r - 1] == key)
		return r - 1;
	else if (a[l] == key)
		return l;
	else
		return -1;
}

int main() {
	ifstream fin("binsearch.in");
	ofstream fout("binsearch.out");
	if (!fin) {
		cerr << "ERROR!";
		return -1;
	}

	int n;
	fin >> n;
	vector<int> a(n);
	int m;
	for (int i = 0; i < n; ++i) {
		fin >> a[i];
	}
	fin >> m;

	for (int i = 0; i < m; ++i) {
		int key;
		fin >> key;
		int min_index = min_index_of_element(a, key);
		int max_index = max_index_of_element(a, key);
		cout << (min_index == -1 ? -1 : min_index + 1) << " ";
		cout << (max_index == -1 ? -1 : max_index + 1) << '\n';
	}

	return 0;
}