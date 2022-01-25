#include <iostream>
#include <vector>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <fstream>

using namespace std;

int ok(pair<int, int> a, int h, int w, vector<vector<int>> f) {
	if (0 <= a.first && a.first < h && 0 <= a.second && a.second < w) {
		return f[a.first][a.second];
	}
	return 0;
}

int main() {
	ifstream fin("turtle.in");
	ofstream fout("turtle.out");
	if (!fin) {
		return -1;
	}
	int w, h;
	fin >> h >> w;
	vector<vector<int>> field(h, vector<int>(w, 0));
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			fin >> field[i][j];
		}
	}

	vector<vector<int>> dp(h, vector<int>(w, 0));
	for (int i = h - 1; i >= 0; --i) {
		for (int j = 0; j < w; ++j) {
			dp[i][j] = field[i][j] + max(ok({ i+1,j }, h, w, dp), ok({ i,j-1 }, h, w, dp));
		}
	}
	fout << dp[0][w - 1];
	return 0;
}