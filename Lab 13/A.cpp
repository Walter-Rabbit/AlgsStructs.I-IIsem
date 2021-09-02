#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/* Наивный поиск подстроки в строке */
int main() {
    ifstream fin("search1.in");
    ofstream fout("search1.out");

    string sub_line, line;
    fin >> sub_line >> line;

    vector<int> ans;
    int n = (int) line.length();

    reverse(sub_line.begin(), sub_line.end());
    line += "#" + sub_line;


    for (int i = 0; i < n; ++i) {
        int current_length = (int) line.length();

        for (int j = 0; j < current_length; ++j) {
            if (line[j] != line[current_length - j - 1] || line[j] == '#') {
                if (line[current_length - j - 1] == '#') {
                    ans.push_back(i + 1);
                }
                break;
            }
        }

        line.erase(line.begin());
    }

    fout << ans.size() << "\n";
    for (auto i : ans) {
        fout << i << " ";
    }

    fin.close();
    fout.close();
    return 0;
}