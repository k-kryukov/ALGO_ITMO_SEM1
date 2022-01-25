#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void countSort(vector<string>& vs, int index) {
	vector<int> positions(26, 0); // a = 0, z = 25
	for (auto s : vs) {
		positions[s[index] - 'a']++;
	}
	vector<string> res(vs.size());
	for (int i = 1; i < 26; ++i)
		positions[i] += positions[i - 1];
	for (int i = vs.size() - 1; i >= 0; --i) {
		res[--positions[vs[i][index] - 'a']] = vs[i];
	}
	for (int i = 0; i < vs.size(); ++i)
		vs[i] = res[i];
	res.clear();
	positions.clear();
}

void radixSort(vector<string> &vs, int k, int size) {
	for (int i = 0; i < k; ++i)
		countSort(vs, size - 1 - i);
}

int main() {
	ifstream fin("radixsort.in");
	ofstream fout("radixsort.out");

	int n, m, k;
	fin >> n;
	fin >> m >> k;
	vector<string> a(n);
	for (int i = 0; i < n; ++i) {
		fin >> a[i];
	}
	radixSort(a, k, m);
	for (auto x : a) {
		fout << x << endl;
	}
	fin.close();
	fout.close();
	a.clear();
	return 0;
}