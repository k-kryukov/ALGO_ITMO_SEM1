#include <string>
#include <set>
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

void swap(int& a, int& b) {
	int t = a;
	a = b;
	b = t;
	return;
}

void random(vector<int>& a, int mx) {
	for (auto& x : a) {
		x = rand() % mx;
	}
	return;
}

void sort(vector<int>& a) {
	int n = a.size();
	for (int i = 0; i < n-1; i++) {
		for (int j = 0; j < n-1; j++) {
			if (a[j] > a[j + 1]) {
				swap(a[j], a[j + 1]);
			}
		}
	}
	return;
}



int main() {
	ifstream fin("smallsort.in");
	ofstream fout("smallsort.out");
	int n;
	fin >> n;
	//n = rand() % 30;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		fin >> a[i];
	//random(a, 50);
	sort(a);
	for (int i = 0; i < n; i++)
		fout << a[i] << " ";
	return 0;
}