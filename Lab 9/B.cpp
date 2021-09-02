#include <vector>
#include <set>
#include <queue>
#include <fstream>

/*Поиск цикла*/

using namespace std;

queue <int> answer;
int k = 0;

void visit(vector <set <int>> &data, vector <int> &colors, int x) {
    if (colors[x] != -1) {
        colors[x] = 1;
    }
    for (auto i : data[x]) {
        if (colors[i] == -1) {
            k = 2;
        }
        if (colors[i] == 1 && k == 0) {
            colors[i] = -1;
            k = 1;
        }
        if (colors[i] == 0) {
            visit(data, colors, i);
        }
        if ((colors[i] == 1 || colors[i] == -1) && k == 1) {
            answer.push(i + 1);
            visit(data, colors, i);
        }
        if (k == 2) {
            return;
        }
    }
    colors[x] = 2;
}

void dfs(vector <set <int>> &data, vector <int> &colors) {
    for (int i = 0; i < colors.size(); ++i) {
        if (colors[i] == 0) {
            visit(data, colors, i);
        }
    }
}

int main() {
    ifstream fin("cycle.in");
    ofstream fout("cycle.out");

    int n, m;
    fin >> n >> m;

    vector <int> colors(n, 0);
    vector <set <int>> data(n);

    for (int i = 0; i < m; ++i) {
        int x, y;
        fin >> x >> y;
        data[x - 1].insert(y - 1);
    }

    dfs(data, colors);

    if (answer.empty()) {
        fout << "NO";
        return 0;
    }

    fout << "YES\n";

    while (!answer.empty()) {
        fout << answer.front() << " ";
        answer.pop();
    }

    fin.close();
    fout.close();
    return 0;
}