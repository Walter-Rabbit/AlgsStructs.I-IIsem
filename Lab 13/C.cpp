#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<int> Prefix(string& str) {
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

int main() {
    ifstream fin("prefix.in");
    ofstream fout("prefix.out");

    string line;
    fin >> line;

    vector<int> ans = Prefix(line);

    for (auto i : ans) {
        fout << i << " ";
    }

    fin.close();
    fout.close();
    return 0;
}