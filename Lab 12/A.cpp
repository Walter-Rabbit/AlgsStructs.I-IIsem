#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/* Наибольшая возрастающая подпоследовательность */
int main() {
    vector<int> a;
    int n;

    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        a.push_back(x);
    }

    vector<int> prev(n);
    vector<int> d(n);

    for (int i = 0; i < n; ++i) {
        d[i] = 1;
        prev[i] = -1;
        for (int j = 0; j < i; ++j) {
            if (a[j] < a[i] && d[j] + 1 > d[i]) {
                d[i] = d[j] + 1;
                prev[i] = j;
            }
        }
    }

    int max_pos = 0;
    int max = d[0];
    for (int i = 0; i < n; ++i) {
        if (d[i] > max) {
            max_pos = i;
            max = d[i];
        }
    }

    vector<int> ans;
    int pos = max_pos;
    while (pos != -1) {
        ans.push_back(a[pos]);
        pos = prev[pos];
    }

    reverse(ans.begin(), ans.end());

    cout << ans.size() << "\n";
    for (auto i : ans) {
        cout << i << " ";
    }
    return 0;
}