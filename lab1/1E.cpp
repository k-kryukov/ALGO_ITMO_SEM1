#include <string>
#include <set>
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

void swap(pair<int,double>& a, pair<int,double>& b) {
	pair<int,double> t = a;
	a = b;
	b = t;
	return;
}

void sort(vector<pair<int,double>>& a) {
	int n = a.size();
	for (int i = 0; i < n-1; i++) {
		for (int j = 0; j < n-1; j++) {
			if (a[j].second > a[j + 1].second)
				swap(a[j], a[j + 1]);
		}
	}
}

int main() {
	int n;
	ifstream fin("sortland.in");
	ofstream fout("sortland.out");
	
	fin >> n;
	vector<pair<int,double>> m(n);
	for (int i = 0; i < n; i++) {
		double t;
		fin >> t;
		m[i] = pair<int,double>{ i + 1, t };
	}
	sort(m);
	fout << m[0].first << " " << m[n/2].first << " " << m[n - 1].first;
	return 0;
}