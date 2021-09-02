#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

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

/* Быстрый поиск подстроки в строке */
int main() {
    ifstream fin("search2.in");
    ofstream fout("search2.out");

    string sub_line, line;
    fin >> sub_line >> line;

    line = sub_line + "#" + line;

    vector<int> prefix = Prefix(line);

    vector<int> ans;
    for (int i = (int) sub_line.size() + 1; i < prefix.size(); ++i) {
        if (prefix[i] == sub_line.length()) {
            ans.push_back(i - 2 * (int) sub_line.length() + 1);
        }
    }

    fout << ans.size() << "\n";
    for (auto i : ans) {
        fout << i << " ";
    }

    fin.close();
    fout.close();
    return 0;
}
