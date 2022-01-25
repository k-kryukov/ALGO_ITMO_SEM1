#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main() {
	ifstream fin("isheap.in");
	ofstream fout("isheap.out");
	
	int n;
	fin >> n;
	bool answer = true; // YES
	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		fin >> a[i];
	}
	for (int i = 1; i < n / 2; ++i) {
		if (a[i] > a[2 * i] || a[i] > a[2 * i + 1]) {
			answer = false;
		}
	}
	if (n % 2 == 0) {
		if (a[n / 2] > a[n])
			answer = false;
	}
	if (answer)
		fout << "YES";
	else
		fout << "NO";
	a.clear();
	fin.close();
	fout.close();
	return 0;
}