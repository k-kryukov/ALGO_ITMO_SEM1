#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void qSort(vector<int>& a, int l, int r) {
	int i, j, key, buf;
	key = a[(l + r) / 2];
	i = l;
	j = r;
	do {
		while (a[i] < key) {
			i++;
		}
		while (a[j] > key)
			j--;
		if (i <= j) {
			buf = a[i];
			a[i] = a[j];
			a[j] = buf;
			i++;
			j--;
		}
	} while (i > j);
	if (l < j) {
		qSort(a, l, j);
	}
	if (i < r)
		qSort(a, i, r);
}

void swap(int& a, int& b) {
	int t = a;
	a = b;
	b = t;
	return;
}

int main() {
	ifstream fin("antiqs.in");
	ofstream fout("antiqs.out");
	int n;
	fin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		a[i] = i+1;
	for (int i = 2; i < n; i++) {
		swap(a[i], a[i / 2]);
	}
	for (int i = 0; i < n; i++)
		fout << a[i] << ((i == n - 1) ? '\n' : ' ');
	a.clear();
	fin.close();
	fout.close();
	return 0;
}