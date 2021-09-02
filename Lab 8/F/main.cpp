#include <fstream>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

int a[100][100];
int n, m;

void bfs(int startI, int startJ) {
    queue<pair<int, int>> q;

    q.push({startI, startJ});
    while (!q.empty()) {
        pair<int, int> t = q.front();
        q.pop();

        int from = a[t.first][t.second];
        int to;
        if (t.first != 0 && !(t.first - 1 == startI && t.second == startJ)) {
            to = a[t.first - 1][t.second];
            if (to != -5 && (to == 0 || from + 1 < to)) {
                a[t.first - 1][t.second] = from + 1;
                q.push({t.first - 1,t.second});
            }
        }

        if (t.second != 0 && !(t.first == startI && t.second - 1 == startJ)) {
            to = a[t.first][t.second - 1];
            if (to != -5 && (to == 0 || from + 1 < to)) {
                a[t.first][t.second - 1] = from + 1;
                q.push({t.first, t.second - 1});
            }
        }

        if (t.first != n - 1 && !(t.first + 1 == startI && t.second == startJ)) {
            to = a[t.first + 1][t.second];
            if (to != -5 && (to == 0 || from + 1 < to)) {
                a[t.first + 1][t.second] = from + 1;
                q.push({t.first + 1, t.second});
            }
        }

        if (t.second != m - 1 && !(t.first == startI && t.second + 1 == startJ)) {
            to = a[t.first][t.second + 1];
            if (to != -5 && (to == 0 || from + 1 < to)) {
                a[t.first][t.second + 1] = from + 1;
                q.push({t.first, t.second + 1});
            }
        }

    }
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    fin >> n >> m;

    int startI, startJ, finishI, finishJ;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c;
            fin >> c;
            if (c == '.') {
                a[i][j] = 0;
                continue;
            }
            if (c == '#') {
                a[i][j] = -5;
                continue;
            }
            if (c == 'S') {
                startI = i;
                startJ = j;
                continue;
            }
            if (c == 'T') {
                finishI = i;
                finishJ = j;
                continue;
            }
        }
    }

    bfs(startI, startJ);

    string path;
    int i = finishI, j = finishJ;
    while (i != startI || j != startJ) {
        if (i != 0 && a[i - 1][j] == a[i][j] - 1) {
            path += 'D';
            i--;
            continue;
        }
        if (j != 0 && a[i][j - 1] == a[i][j] - 1) {
            path += 'R';
            j--;
            continue;
        }
        if (i != n - 1 && a[i + 1][j] == a[i][j] - 1) {
            path += 'U';
            i++;
            continue;
        }
        if (j != m - 1 && a[i][j + 1] == a[i][j] - 1) {
            path += 'L';
            j++;
            continue;
        }
        fout << -1;
        return 0;
    }

    reverse(path.begin(), path.end());

    fout << path.length() << "\n";
    fout << path;

    fin.close();
    fout.close();
    return 0;
}
