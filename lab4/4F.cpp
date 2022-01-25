#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

const double EPS = 0.000001;

enum {
    GREATER,
    EQUAL,
    LOWER
};

unsigned char compare(double a, double b) {
    if (a - b > EPS) {
        return GREATER;
    }
    else if (fabs(a - b) < EPS) {
        return EQUAL;
    }
    return LOWER;
}

int main() {
    ifstream fin("garland.in");
    ofstream fout("garland.out");
    if (!fin) {
        cerr << "ERROR!";
        return -1;
    }

    double a;
    int n;
    cin >> n >> a;
    vector<double> lamps(n);
    lamps[0] = a;
    double max_ans = a;
    double min_ans = 0;

    while (max_ans - min_ans >= 0.00001) {
        bool should_be_lower = true;
        lamps[1] = (max_ans + min_ans) / 2;
        for (int i = 2; i < n; ++i) {
            double cur_height = (2 * lamps[i - 1] + 2 - lamps[i - 2]);
            if (compare(cur_height, 0) == LOWER) {
                should_be_lower = false;
                break;
            }
            lamps[i] = cur_height;
        }
        if (should_be_lower) {
            max_ans = lamps[1];
        }
        else {
            min_ans = lamps[1];
        }
    }
    lamps[1] = (max_ans + min_ans) / 2;
    for (int i = 2; i < n; ++i) {
        lamps[i] = (2 * lamps[i - 1] + 2 - lamps[i - 2]);
    }
    double temp = round(100.0 * lamps[n - 1]) / 100.0;
    cout.precision(2);
    cout << fixed << temp;
    return 0;
}