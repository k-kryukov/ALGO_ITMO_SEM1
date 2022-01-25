#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;

void swap(int& a, int& b) {
	int t = a;
	a = b;
	b = t;
	return;
}

int Partition(int l, int r, int* a) {
	int random_el = rand() % (r-l) + l;
	swap(a[random_el], a[l]);
	int x = a[l];
	int j = l;
	for (int i = l + 1; i < r; i++) {
		if (a[i] <= x) {
			j++;
			swap(a[i], a[j]);
		}
	}
	swap(a[l], a[j]);
	return j;
}

void QuickSort(int* a, int l, int r) { // [l,r)
	if (r - l <= 1)
		return;
	int m = Partition(l, r, a);
	QuickSort(a, l, m);
	QuickSort(a, m + 1, r);
	return;
}

int main() {
	ifstream fin("sort.in");
	ofstream fout("sort.out");
	int n;
	fin >> n;
	int* a = new int[n];
	for (int i = 0; i < n; i++)
		fin >> a[i];
	QuickSort(a, 0, n);
	for (int i = 0; i < n; i++)
		fout << a[i] << " ";
	delete[] a;
	fin.close();
	fout.close();
	return 0;
}