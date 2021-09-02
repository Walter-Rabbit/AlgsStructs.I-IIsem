#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> get_prefix(string& str) {
    int n = (int) str.length();
    vector<int> ans(n, 0);

    for (int i = 1; i < n; ++i) {
        int j = ans[i - 1];

        while (j > 0 && str[i] != str[j]) {
            j = ans[j - 1];
        }

        if (str[i] == str[j]) {
            j++;
        }
        ans[i] = j;
    }

    return ans;
}

int to_int(char x) {
    return x + 'a';
}

* Автомат
int main() {
    int n, m;
    string str;

    cin >> n >> str;
    str += "#";
    m = (int) str.length();

    vector<int> prefix = get_prefix(str);
    vector<vector<int>> kmp(m, vector<int>(n));

    for (int q = 0; q < m; ++q) {
        for (char a = 0; (int) a < n; ++a) {
            if (q > 0 && to_int(a) != str[q]) {
                kmp[q][a] = kmp[prefix[q - 1]][a];
            }
            else if (to_int(a) == str[q]) {
                kmp[q][a] = q + 1;
            }
            else {
                kmp[q][a] = q;
            }
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << kmp[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}