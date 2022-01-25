#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void swap(pair<string,string>& a, pair<string,string>& b) {
	pair<string,string> t = a;
	a = b;
	b = t;
	return;
}

vector<pair<string, string>> Merge(vector<pair<string, string>> & a, vector<pair<string, string>> & b) {
	int n = a.size(), m = b.size();
	vector<pair<string, string>> res(n + m);
	int i = 0, j = 0;
	while (i < n && j < m) {
		if (a[i].first <= b[j].first) {
			res[i + j] = a[i];
			i++;
		}
		else {
			res[i + j] = b[j];
			j++;
		}
	}
	while (i < n) {
		res[i + j] = a[i];
		i++;
	}
	while (j < m) {
		res[i + j] = b[j];
		j++;
	}
	a.clear();
	b.clear();
	return res;
}

vector<pair<string, string>> MergeSort(vector<pair<string,string>> const& a, int l,int r) {
	if (r - l <= 1) {
		return { a[l] };
	}
	int m = (r + l) / 2;
	vector<pair<string, string>> m1 = MergeSort(a, l, m);
	vector<pair<string, string>> m2 = MergeSort(a, m, r);
	vector<pair<string,string>> res = Merge(m1, m2);
	m1.clear();
	m2.clear();
	return res;
}

int main() {
	ifstream fin("race.in");
	ofstream fout("race.out");
	int n;
	fin >> n;
	vector<pair<string, string>> a(n);
	for (int i = 0; i < n; i++) {
		string s1, s2;
		fin >> s1 >> s2;
		a[i] = { s1,s2 };
	}
	vector<pair<string, string>> res1 = MergeSort(a,0,n); 
	int i = 0;
	while (i < n) {
		string s = res1[i].first;
		fout << "=== " << s << " ===" << '\n';
		while (i < n && res1[i].first == s) {
			fout << res1[i].second << '\n';
			i++;
		}
	}
	a.clear();
	res1.clear();
	fin.close();
	fout.close();
	return 0;
}