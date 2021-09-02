#include <fstream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

/* Рюкзак */
int main() {
    ifstream fin("knapsack.in");
    ofstream fout("knapsack.out");

    int s, n;
    fin >> s >> n;

    vector<int> d(s + 1, 0);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        fin >> a[i];
    }
    sort(a.begin(), a.end());

    d[0] = 1;
    for (int i = 0; i < n; ++i) {
        set<int> consists;
        for (int j = 0; j < s; ++j) {
            if (d[j] == 1 && j + a[i] <= s && consists.count(j) == 0 && d[j + a[i]] == 0) {
                d[j + a[i]] = 1;
                consists.insert(j + a[i]);
            }
        }
    }

    for (int i = s; i >= 0; --i) {
        if (d[i] != 0) {
            fout << i;
            break;
        }
    }

    fin.close();
    fout.close();
    return 0;
}