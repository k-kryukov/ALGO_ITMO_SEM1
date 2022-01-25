#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;

int64_t cnt = 0;

vector<int> Merge(vector<int> &a, vector<int> &b, int s1, int s2) {
    vector<int>res(s1 + s2);
    int i = 0, j = 0;
    while (i < s1 && j < s2) {
        if (a[i] <= b[j]) {
            res[i + j] = a[i];
            i++;
        }
        else {
            cnt += (s1 - i);
            res[i + j] = b[j];
            j++;
        }
    }
    while (i < s1) {
        res[i + j] = a[i];
        i++;
    }
    while (j < s2) {
        res[i + j] = b[j];
        j++;
    }
    a.clear();
    b.clear();
    return res;
}

vector<int>MergeSort(vector<int> const& a, int l, int r) {
    int m = (l + r) / 2;
    if (r - l <= 1) {
        vector<int> tmp = { a[l] };
        return tmp;
    }
    vector<int> fir = MergeSort(a, l, m);
    vector<int> sec = MergeSort(a, m, r);
    vector<int> res = Merge(fir, sec, m - l, r - m);
    fir.clear();
    sec.clear();
    return res;
}

int main() {
    ifstream fin("inversions.in");
    ofstream fout("inversions.out");
    int n;
    fin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        fin >> a[i];
    vector<int> temp = MergeSort(a, 0, n);
    fout << cnt;
    a.clear();
    temp.clear();
    fin.close();
    fout.close();
    return 0;
}