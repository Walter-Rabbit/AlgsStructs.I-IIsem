#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool comp(pair<int, int> x, pair<int, int> y) {
    return x.second - x.first < y.second - y.first;
}

int main() {
    int n;
    cin >> n;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<vector<long long>> d(n, vector<long long>(n));
    vector<pair<int, int>> pairs;

    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            d[i][j] = 1;
            if (i != j) {
                pairs.emplace_back(i, j);
            }
        }
    }

    sort(pairs.begin(), pairs.end(), comp);
    long long max = 1e9;

    for (auto i : pairs) {
        if (a[i.first] == a[i.second]) {
            d[i.first][i.second] = (d[i.first + 1][i.second] + d[i.first][i.second - 1] + 1) % max;
        }
        else if (d[i.first + 1][i.second] + d[i.first][i.second - 1] - d[i.first + 1][i.second - 1] < 0) {
            d[i.first][i.second] = d[i.first + 1][i.second] + d[i.first][i.second - 1] - d[i.first + 1][i.second - 1] + max;
        }
        else {
            d[i.first][i.second] = (d[i.first + 1][i.second] + d[i.first][i.second - 1] - d[i.first + 1][i.second - 1]) % max;
        }
    }

    cout << d[0][n - 1];
    return 0;
}