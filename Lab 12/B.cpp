#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/* Наибольшая возрастающая подпоследовательность 2 */
int main() {
    vector<int> a;
    int n;

    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        a.push_back(x);
    }

    int inf = 1e9;
    vector<int> prev(n + 1);
    vector<int> pos(n + 1);
    vector<int> d(n + 1, inf);

    pos[0] = -1;
    d[0] = -inf;
    int len = 0;

    for (int i = 0; i < n; ++i) {
        auto j = lower_bound(d.begin(), d.end(), a[i]);
        int k = j - d.begin();
        if (d[k - 1] < a[i] && a[i] < d[k]) {
            d[k] = a[i];
            pos[k] = i;
            prev[i] = pos[k - 1];
            if (len < k) {
                len = k;
            }
        }
    }

    vector<int> ans;
    int x = pos[len];
    while (x != -1) {
        ans.push_back(a[x]);
        x = prev[x];
    }

    reverse(ans.begin(), ans.end());

    cout << ans.size() << "\n";
    for (auto i : ans) {
        cout << i << " ";
    }
    return 0;
}